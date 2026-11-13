# Security Policy

## Supported versions

ext-pixman is pre-1.0. No 0.x release receives security fixes or advisories; fixes land in the
next release line. Security support starts with 1.0.

| Version | Security fixes |
|---------|----------------|
| < 1.0   | No             |

## Reporting a vulnerability

Please don't open a public issue for a security problem.

Report it privately through GitHub: the **Report a vulnerability** button on the
[php-io-extensions/pixman](https://github.com/php-io-extensions/pixman) repository's **Security** tab.
If that isn't available, email **info@projectsaturnstudios.com**.

Include what you found, the affected version, your platform and CPU, PHP build (NTS or ZTS), and
steps to reproduce (`php --ri pixman` shows the extension version and the pixman commit it carries).

A defect in pixman itself belongs with that project. Report it here as well when ext-pixman should
guard against it.

## Security model

pixman trusts its caller with raw memory and arithmetic. ext-pixman stands between PHP and pixman:

- **Memory.** Pixel bits cross as PHP strings, copied into memory each image owns and copied out
  again; pixman never holds a pointer into PHP memory. `pixman_fill` and `pixman_blt` refuse any row
  outside their strings. Palettes given to `pixman_image_set_indexed` are copied for the image's life.
- **Inputs pixman would trust.** Operators in the enum's gaps, unknown format codes, convolution
  kernels shorter than their declared size, rasteriser rows off pixman's sample grid or outside the
  image, edges whose stepping divides by zero or overflows, out-of-range C integers, wrong-length
  arrays: each is a `ValueError` before pixman runs. `tools/sweep.php` calls every function with
  zero, negative and large arguments in separate processes to keep it that way.
- **Lifetimes.** Images, regions and glyph caches are objects; a released image, an uninitialised
  region, a destroyed cache, or a glyph handle the cache no longer holds is refused.
- **Symbols.** The module exports `get_module` only, so a system libpixman loaded by another
  extension never takes over the binding's calls.
- **Callbacks.** Destroy and accessor callables run on the calling thread, synchronously. An
  exception they throw surfaces when the pixman call returns.
