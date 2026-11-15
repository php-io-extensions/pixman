<?php

declare(strict_types=1);

if (! extension_loaded('pixman')) {
    throw new RuntimeException('The pixman extension is not loaded; run ./install-macos.sh or ./install-debian-trixie.sh');
}

/** The 32-bit pixels of a 32 bpp bits image, row by row (stride is width × 4 for images pixman allocates). */
function px_pixels(pixman_image $image): array
{
    return array_values(unpack('V*', pixman_image_get_data($image, copy: true)));
}

function px_argb(int $w, int $h): pixman_image
{
    return pixman_image_create_bits(PIXMAN_a8r8g8b8, $w, $h, null, 0);
}

function px_solid(int $argb): pixman_image
{
    $c = fn (int $shift): int => (($argb >> $shift) & 0xff) * 0x101;

    return pixman_image_create_solid_fill(new pixman_color($c(16), $c(8), $c(0), $c(24)));
}
