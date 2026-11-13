<?php

declare(strict_types=1);

it('reports pixman 0.46.4', function (): void {
    expect(pixman_version_string())->toBe('0.46.4')
        ->and(pixman_version())->toBe(4604);
});

it('prints the extension version, the pixman version, and the upstream commit', function (): void {
    ob_start();
    phpinfo(INFO_MODULES);
    $info = ob_get_clean();

    expect($info)->toContain('0.11.0')
        ->and($info)->toContain('0.46.4')
        ->and($info)->toContain('9cc163c9da0fb4da430641715313d95a6ec466d9');
});
