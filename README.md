<div align="center" id="header">

<h1>ext-pixman</h1>

<h3>pixman 0.46.4 bound 1:1 into PHP 8.4+, with the library compiled in</h3>


[![CI](https://img.shields.io/github/actions/workflow/status/php-io-extensions/pixman/ci.yml?style=flat-square&label=CI)](https://github.com/php-io-extensions/pixman/actions/workflows/ci.yml)
[![Packagist](https://img.shields.io/packagist/v/php-io-extensions/pixman?style=flat-square)](https://packagist.org/packages/php-io-extensions/pixman)
[![PHP](https://img.shields.io/packagist/dependency-v/php-io-extensions/pixman/php?style=flat-square&label=PHP)](https://packagist.org/packages/php-io-extensions/pixman)
[![License](https://img.shields.io/github/license/php-io-extensions/pixman?style=flat-square)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-linux_%7C_macos-blue?style=flat-square&logo=linux&logoColor=white)](https://gitlab.freedesktop.org/pixman/pixman)
[![PIE](https://img.shields.io/badge/PIE-installable-4f5b93?style=flat-square&logo=php&logoColor=white)](https://github.com/php/pie)

</div>

Drawing a UI or a game in software comes down to pixels: compositing one image over another with alpha, scaling and rotating it with a decent filter, filling gradients, clipping to regions, converting between 32-, 16- and 8-bit formats. Doing that per pixel in PHP is slow and easy to get subtly wrong.

<b>pixman</b> does it for cairo and the X server: Porter-Duff and blend-mode compositing over masks, affine and projective transforms with nearest, bilinear and convolution filters, linear, radial and conical gradients, regions, glyph caches, and trapezoid and triangle rasterisation, with SSE2 and NEON paths.

<b>The only problem?</b> PHP can't reach it. This extension binds every public function of `pixman.h` one to one under the C names, with pixman compiled into the module from an unchanged copy of the upstream tag, so there is nothing to install from the system. Structs are typed classes, images, regions and glyph caches are objects, pixels cross as strings, and every argument pixman would trust blindly is checked first. No defaults, no composites, no opinions: what pixman documents is what you call.

## Basic usage

```php
<?php
// A 4×2 ARGB canvas, a half-transparent red square composited over blue.
$canvas = pixman_image_create_bits(PIXMAN_a8r8g8b8, 4, 2, null, 0);
$blue = pixman_image_create_solid_fill(new pixman_color(0, 0, 0xffff, 0xffff));
$red = pixman_image_create_solid_fill(new pixman_color(0x8000, 0, 0, 0x8000)); // premultiplied
pixman_image_composite32(PIXMAN_OP_SRC, $blue, null, $canvas, 0, 0, 0, 0, 0, 0, 4, 2);
pixman_image_composite32(PIXMAN_OP_OVER, $red, null, $canvas, 0, 0, 0, 0, 1, 0, 2, 2);

printf("%08x\n", unpack('V*', pixman_image_get_data($canvas, copy: true))[2]); // ff80007f

// Regions: two overlapping rects, their union in three bands.
$a = new pixman_region32();
pixman_region32_init_rect($a, 0, 0, 10, 10);
$b = new pixman_region32();
pixman_region32_init_rect($b, 5, 5, 10, 10);
$u = new pixman_region32();
pixman_region32_init($u);
pixman_region32_union($u, $a, $b);
echo pixman_region32_n_rects($u), "\n"; // 3
```

## Requirements

- PHP 8.4 or newer, NTS or ZTS, with `phpize` and `php-config`.
- A C compiler (the AArch64 build also assembles pixman's NEON `.S` files).
- No system libraries.

```bash
# Debian, Ubuntu, Raspberry Pi OS
sudo apt install build-essential php8.4-dev

# macOS: Xcode Command Line Tools, and Homebrew's PHP ships phpize and php-config
xcode-select --install
```

## Installation

### With PHP PIE (recommended)

```bash
pie install php-io-extensions/pixman
```

### Manually (install script)

```bash
git clone https://github.com/php-io-extensions/pixman.git
cd pixman

./install-debian-trixie.sh             # Debian Trixie, Ubuntu 24.04+, Raspberry Pi OS: the php on PATH
./install-macos.sh                     # Homebrew php@8.4 and php@8.4-zts
./install-macos.sh /path/to/bin/php    # either script takes specific PHP binaries
```

### Manually (phpize)

```bash
git clone https://github.com/php-io-extensions/pixman.git
cd pixman
phpize
./configure --enable-pixman
make -j"$(nproc 2>/dev/null || sysctl -n hw.ncpu)"
sudo make install
```

Then add `extension=pixman.so` to your `php.ini`, or to a file in the scan directory `php --ini` reports.

### Verify

```console
$ php --ri pixman

pixman

pixman support => enabled
Version => 0.11.x
pixman version => 0.46.4
pixman commit => 9cc163c9da0fb4da430641715313d95a6ec466d9
```

## API

178 of pixman's 179 public functions, under their C names, plus one addition. The full rules are in the [design spec](docs/superpowers/specs/2026-11-13-pixman-design.md).

### Translations

- **Constants:** every enum value (`PIXMAN_OP_*`, formats such as `PIXMAN_a8r8g8b8`, `PIXMAN_FILTER_*`, …), `PIXMAN_TYPE_*`, `PIXMAN_VERSION*`, and the fixed-point values `pixman_fixed_1`, `pixman_fixed_e`, …. Fixed-point numbers are ints (16.16).
- **Value structs** are final classes named after the C type without `_t` (`pixman_color`, `pixman_box32`, `pixman_transform`), one typed property per field, every constructor argument optional and zero by default. Fixed arrays are arrays of their exact length. A struct pixman writes, such as a transform being initialised or a vector being mapped, is written back into the object you passed.
- **Images** (`pixman_image`) come from the `pixman_image_create_*` functions and hold one pixman reference. `pixman_image_ref()` returns a second object, and `pixman_image_unref()` releases the object you pass.
- **Regions** (`pixman_region16/32/64f`): `new` gives uninitialised storage, a `*_init*` function initialises it, and `*_fini` releases it. Region16 keeps pixman's legacy `pixman_region_*` names.
- **Glyph caches:** `pixman_glyph_cache_create()`. Keys and glyph handles are ints, and a handle the cache no longer holds is refused.
- **Pixels cross as strings.** `pixman_image_create_bits()` copies the string you give it (or pixman allocates when you pass `null`), or uses an address you pass as an int (trusted, never freed by the binding). `pixman_image_get_data()` returns the bits address by default; `copy: true` returns a string copy. `pixman_fill()` and `pixman_blt()` work on strings in place, by reference.
- **Not bound:** `pixman_region_set_static_pointers`, which only exists to preserve the X server's ABI and would let a script corrupt every region in the process.

### Callbacks

`pixman_image_set_destroy_function()` and `pixman_image_set_accessors()` take PHP callables. pixman runs them on the calling thread, during the call that triggers them. An exception thrown in one surfaces when that call returns.

### Errors

pixman reports failure through return values, which come back as `false` or `null`. Arguments pixman would trust and crash on are a `ValueError` before pixman runs: an operator in the enum's gaps, an unknown format, a short convolution kernel, a rasteriser row off the sample grid, an edge whose stepping divides by zero, a fill or blit outside its string, and a C integer out of range.

## Running the test suite

```bash
composer install
php -d memory_limit=128M vendor/bin/pest
php -d memory_limit=256M tools/sweep.php   # crash sweep: every function, five argument sets, one process each
```

## Security

See [SECURITY.md](SECURITY.md).

## License

MIT for this extension. pixman is under its own MIT-style licence, [lib/pixman/COPYING](lib/pixman/COPYING).
