<?php

/*
 * Crash sweep: calls every pixman_* function with argument sets built from its
 * signature, each call in its own child process. A PHP exception is a pass; a
 * signal (segfault, SIGFPE, abort) or a hang is a failure. Run after any change
 * to argument checks:  php -d memory_limit=256M tools/sweep.php
 */

declare(strict_types=1);

if ($argc > 2 && $argv[1] === '--one') {
    [$name, $variant] = explode(':', $argv[2]);
    $f = new ReflectionFunction($name);
    $args = [];
    foreach ($f->getParameters() as $p) {
        $args[] = sweep_value($p, (int) $variant);
    }
    try {
        $f->invokeArgs($args);
    } catch (Throwable) {
    }
    exit(0);
}

function sweep_value(ReflectionParameter $p, int $v): mixed
{
    $type = $p->getType();
    $name = $type instanceof ReflectionNamedType ? $type->getName() : 'mixed';
    $int = [0, -1, 1 << 20, PHP_INT_MAX, 7][$v];
    return match ($name) {
        'int' => $int,
        'float' => [0.0, -1.0, 1e9, INF, NAN][$v],
        'bool' => $v % 2 === 1,
        'string' => ['', "\xff", str_repeat("\x01", 64), str_repeat("\0", 4096), 'abcd'][$v],
        'array' => [[], [0], [1, 2, 3], array_fill(0, 9, 1 << 16), [new pixman_point_fixed()]][$v],
        'callable' => fn (...$a) => 0,
        'mixed' => null,
        'pixman_image' => [
            pixman_image_create_bits(PIXMAN_a8r8g8b8, 2, 2, null, 0),
            pixman_image_create_bits(PIXMAN_a8, 4, 4, null, 0),
            pixman_image_create_solid_fill(new pixman_color()),
            pixman_image_create_bits(PIXMAN_a1, 33, 3, null, 0),
            pixman_image_create_bits(PIXMAN_r5g6b5, 3, 1, null, 0),
        ][$v],
        'pixman_region16', 'pixman_region32', 'pixman_region64f' => sweep_region($name, $v),
        'pixman_glyph_cache' => pixman_glyph_cache_create(),
        default => class_exists($name) ? sweep_struct($name, $v) : null,
    };
}

function sweep_region(string $class, int $v): object
{
    $r = new $class();
    if ($v === 1) {
        return $r; // uninitialised
    }
    $init = ['pixman_region16' => 'pixman_region_init_rect', 'pixman_region32' => 'pixman_region32_init_rect', 'pixman_region64f' => 'pixman_region64f_init_rect'][$class];
    $init($r, 0, 0, $v === 2 ? 1000 : 3, 3);

    return $r;
}

function sweep_struct(string $class, int $v): object
{
    $o = new $class();
    if ($v === 0) {
        return $o;
    }
    foreach ((new ReflectionClass($o))->getProperties() as $prop) {
        $t = $prop->getType()?->getName();
        if ($t === 'int') {
            $prop->setValue($o, [0, -1, 1 << 20, 0x7fffffff, 3][$v]);
        } elseif ($t === 'float') {
            $prop->setValue($o, [0.0, -1.0, 1e9, INF, NAN][$v]);
        }
    }

    return $o;
}

$fails = [];
$functions = get_extension_funcs('pixman');
sort($functions);
foreach ($functions as $fn) {
    for ($variant = 0; $variant < 5; $variant++) {
        $p = proc_open([PHP_BINARY, '-d', 'memory_limit=256M', __FILE__, '--one', "$fn:$variant"], [1 => ['file', '/dev/null', 'w'], 2 => ['file', '/dev/null', 'w']], $pipes);
        $start = microtime(true);
        while (($s = proc_get_status($p))['running'] && microtime(true) - $start < 10) {
            usleep(2000);
        }
        if ($s['running']) {
            proc_terminate($p, 9);
            $fails[] = "$fn:$variant hang";
        } elseif ($s['signaled'] || $s['exitcode'] !== 0) {
            $fails[] = "$fn:$variant " . ($s['signaled'] ? 'signal ' . $s['termsig'] : 'exit ' . $s['exitcode']);
        }
        proc_close($p);
    }
}
echo count($functions) * 5, ' calls, ', count($fails), " failures\n", implode("\n", $fails), "\n";
exit($fails === [] ? 0 : 1);
