# Log

## 2026-11-13

* **Built**: pixman 0.46.4 vendored (SSE2 / A64 NEON), 178 functions + `pixman_image_get_data_address`. Suite green on Homebrew PHP 8.4.27 NTS and ZTS.
* **Found by tests**: system libpixman interposing (exports now `get_module` only); `pixman_rasterize_edges` unbounded loop off the sample grid; edge stepping division by zero.

* **2026-11-14**: pointer returns default to the address. `pixman_image_get_data($image, bool $copy = false)` returns the address, or a string copy with `copy: true`; `pixman_image_get_data_address()` removed. `pixman_image_create_bits(_no_clear)` take `string|int|null`: an int is a trusted address pixman draws in, never freed by the binding.

* **2026-11-19**: the trap, trapezoid and triangle arrays of `pixman_add_traps`, `pixman_add_trapezoids`, `pixman_add_triangles`, `pixman_composite_trapezoids` and `pixman_composite_triangles` take `array|string`: a string of the C structs is read in place, so geometry made in C (ext-comrec's lowering) reaches pixman without a PHP object a piece. Building those objects was 7.8 ms of a 1280x840 particle frame whose pixman call was 1.8 ms. One test in `tests/TrapTest.php`, worked by hand for each of the five against the object form; it fails when the string is read one int32 off. 46 passed on Homebrew PHP 8.4.27 NTS and ZTS.
