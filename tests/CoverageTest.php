<?php

declare(strict_types=1);

it('binds every PIXMAN_API function in pixman.h but the one the spec excludes', function (): void {
    $header = file_get_contents(__DIR__.'/../lib/pixman/pixman/pixman.h');
    preg_match_all('/PIXMAN_API\s+[^;(]*?\b(pixman_\w+)\s*\(/s', $header, $m);
    $declared = array_unique($m[1]);
    $excluded = ['pixman_region_set_static_pointers'];

    expect(count($declared))->toBe(179)
        ->and(array_values(array_diff($declared, $excluded, get_extension_funcs('pixman'))))->toBe([])
        ->and(array_values(array_diff(get_extension_funcs('pixman'), $declared, ['pixman_image_get_data_address'])))->toBe([]);
});
