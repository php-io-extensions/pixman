<?php

/** @generate-class-entries */

/** struct pixman_color: 16-bit channels. */
final class pixman_color
{
    public int $red = 0;
    public int $green = 0;
    public int $blue = 0;
    public int $alpha = 0;

    public function __construct(int $red = 0, int $green = 0, int $blue = 0, int $alpha = 0) {}
}

/** struct pixman_point_fixed: 16.16 fixed-point coordinates. */
final class pixman_point_fixed
{
    public int $x = 0;
    public int $y = 0;

    public function __construct(int $x = 0, int $y = 0) {}
}

/** struct pixman_line_fixed */
final class pixman_line_fixed
{
    public pixman_point_fixed $p1;
    public pixman_point_fixed $p2;

    public function __construct(?pixman_point_fixed $p1 = null, ?pixman_point_fixed $p2 = null) {}
}

/** struct pixman_vector: pixman_fixed_t vector[3]. */
final class pixman_vector
{
    public array $vector = [];

    public function __construct(?array $vector = null) {}
}

/** struct pixman_transform: pixman_fixed_t matrix[3][3]. */
final class pixman_transform
{
    public array $matrix = [];

    public function __construct(?array $matrix = null) {}
}

/** struct pixman_f_vector: double v[3]. */
final class pixman_f_vector
{
    public array $v = [];

    public function __construct(?array $v = null) {}
}

/** struct pixman_f_transform: double m[3][3]. */
final class pixman_f_transform
{
    public array $m = [];

    public function __construct(?array $m = null) {}
}

/** struct pixman_box16 */
final class pixman_box16
{
    public int $x1 = 0;
    public int $y1 = 0;
    public int $x2 = 0;
    public int $y2 = 0;

    public function __construct(int $x1 = 0, int $y1 = 0, int $x2 = 0, int $y2 = 0) {}
}

/** struct pixman_box32 */
final class pixman_box32
{
    public int $x1 = 0;
    public int $y1 = 0;
    public int $x2 = 0;
    public int $y2 = 0;

    public function __construct(int $x1 = 0, int $y1 = 0, int $x2 = 0, int $y2 = 0) {}
}

/** struct pixman_box64f */
final class pixman_box64f
{
    public float $x1 = 0.0;
    public float $y1 = 0.0;
    public float $x2 = 0.0;
    public float $y2 = 0.0;

    public function __construct(float $x1 = 0.0, float $y1 = 0.0, float $x2 = 0.0, float $y2 = 0.0) {}
}

/** struct pixman_rectangle16 */
final class pixman_rectangle16
{
    public int $x = 0;
    public int $y = 0;
    public int $width = 0;
    public int $height = 0;

    public function __construct(int $x = 0, int $y = 0, int $width = 0, int $height = 0) {}
}

/** struct pixman_gradient_stop */
final class pixman_gradient_stop
{
    public int $x = 0;
    public pixman_color $color;

    public function __construct(int $x = 0, ?pixman_color $color = null) {}
}

/** struct pixman_indexed: rgba holds 256 entries, ent is 32768 bytes. */
final class pixman_indexed
{
    public bool $color = false;
    public array $rgba = [];
    public string $ent = "";

    public function __construct(bool $color = false, ?array $rgba = null, ?string $ent = null) {}
}

/** pixman_glyph_t: $glyph is a handle from pixman_glyph_cache_lookup / _insert. */
final class pixman_glyph
{
    public int $x = 0;
    public int $y = 0;
    public int $glyph = 0;

    public function __construct(int $x = 0, int $y = 0, int $glyph = 0) {}
}

/** struct pixman_edge */
final class pixman_edge
{
    public int $x = 0;
    public int $e = 0;
    public int $stepx = 0;
    public int $signdx = 0;
    public int $dy = 0;
    public int $dx = 0;
    public int $stepx_small = 0;
    public int $stepx_big = 0;
    public int $dx_small = 0;
    public int $dx_big = 0;

    public function __construct(int $x = 0, int $e = 0, int $stepx = 0, int $signdx = 0, int $dy = 0, int $dx = 0, int $stepx_small = 0, int $stepx_big = 0, int $dx_small = 0, int $dx_big = 0) {}
}

/** struct pixman_trapezoid */
final class pixman_trapezoid
{
    public int $top = 0;
    public int $bottom = 0;
    public pixman_line_fixed $left;
    public pixman_line_fixed $right;

    public function __construct(int $top = 0, int $bottom = 0, ?pixman_line_fixed $left = null, ?pixman_line_fixed $right = null) {}
}

/** struct pixman_triangle */
final class pixman_triangle
{
    public pixman_point_fixed $p1;
    public pixman_point_fixed $p2;
    public pixman_point_fixed $p3;

    public function __construct(?pixman_point_fixed $p1 = null, ?pixman_point_fixed $p2 = null, ?pixman_point_fixed $p3 = null) {}
}

/** struct pixman_span_fix */
final class pixman_span_fix
{
    public int $l = 0;
    public int $r = 0;
    public int $y = 0;

    public function __construct(int $l = 0, int $r = 0, int $y = 0) {}
}

/** struct pixman_trap */
final class pixman_trap
{
    public pixman_span_fix $top;
    public pixman_span_fix $bot;

    public function __construct(?pixman_span_fix $top = null, ?pixman_span_fix $bot = null) {}
}

/**
 * pixman_image_t: from the pixman_image_create_* functions. Holds one pixman reference.
 * @strict-properties
 * @not-serializable
 */
final class pixman_image
{
}

/**
 * pixman_region16_t: `new` is uninitialised storage; a pixman_region_init* function initialises it.
 * @strict-properties
 * @not-serializable
 */
final class pixman_region16
{
}

/**
 * pixman_region32_t: `new` is uninitialised storage; a pixman_region32_init* function initialises it.
 * @strict-properties
 * @not-serializable
 */
final class pixman_region32
{
}

/**
 * pixman_region64f_t: `new` is uninitialised storage; a pixman_region64f_init* function initialises it.
 * @strict-properties
 * @not-serializable
 */
final class pixman_region64f
{
}

/**
 * pixman_glyph_cache_t: from pixman_glyph_cache_create().
 * @strict-properties
 * @not-serializable
 */
final class pixman_glyph_cache
{
}
