# Log

## 2026-11-13

* **Built**: pixman 0.46.4 vendored (SSE2 / A64 NEON), 178 functions + `pixman_image_get_data_address`. Suite green on Homebrew PHP 8.4.27 NTS and ZTS.
* **Found by tests**: system libpixman interposing (exports now `get_module` only); `pixman_rasterize_edges` unbounded loop off the sample grid; edge stepping division by zero.

* **2026-11-14**: pointer returns default to the address. `pixman_image_get_data($image, bool $copy = false)` returns the address, or a string copy with `copy: true`; `pixman_image_get_data_address()` removed. `pixman_image_create_bits(_no_clear)` take `string|int|null`: an int is a trusted address pixman draws in, never freed by the binding.
