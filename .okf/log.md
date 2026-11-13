# Log

## 2026-11-13

* **Built**: pixman 0.46.4 vendored (SSE2 / A64 NEON), 178 functions + `pixman_image_get_data_address`. Suite green on Homebrew PHP 8.4.27 NTS and ZTS.
* **Found by tests**: system libpixman interposing (exports now `get_module` only); `pixman_rasterize_edges` unbounded loop off the sample grid; edge stepping division by zero.
