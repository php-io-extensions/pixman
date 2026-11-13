# Agent guidance — php-io-extensions/pixman

1. **Read the design spec first:** [`docs/superpowers/specs/2026-11-13-pixman-design.md`](docs/superpowers/specs/2026-11-13-pixman-design.md). Its "Names and translations" lists every translation; there are no others.
2. **Bindings are 1:1 at pixman 0.46.4** (tag `pixman-0.46.4`, commit `9cc163c9da0fb4da430641715313d95a6ec466d9`): every `PIXMAN_API` function in `pixman.h` but `pixman_region_set_static_pointers`. Function, struct, enum and constant names are the C names (classes drop `_t`). No defaults, no composites.
3. **Upstream is copied unchanged** into `lib/pixman/` (`pixman/`, `COPYING`, `README`, `AUTHORS`). Never edit it. `config.m4` compiles exactly `pixman_files` from `pixman/meson.build` plus the SIMD set meson enables. `src/pixman-config.h` and `src/pixman-version.h` replace meson's generated headers. A new pixman only from a new upstream tag: replace `lib/pixman/`, diff `pixman.h`, update the bindings, tests, `PHP_PIXMAN_UPSTREAM_COMMIT` and the version.
4. **The stub is the declaration.** Every `ZEND_FUNCTION` is written out by hand, never made by a macro; shared parsing goes through static helpers.
5. **Pixel memory crosses as strings**, copied in and out. pixman never sees PHP string memory it could keep.
6. **Build.** `./install-macos.sh` into Homebrew `php@8.4` and `php@8.4-zts` (`zhp`). Pest: `php -d memory_limit=128M vendor/bin/pest` on both builds. Gate a commit on the suite's exit code.
7. **Version** is `PHP_PIXMAN_VERSION` in `php_pixman.h`: 0.11.0, venusian/framework's 0.x line. `os-families`: linux, darwin.
