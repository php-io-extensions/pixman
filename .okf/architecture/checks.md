---
type: Architecture
title: Safety checks
description: Inputs pixman trusts that the binding refuses, and why each one crashes otherwise.
resource: src/
tags: [pixman, safety]
status: draft
generated: { by: claude-opus/5.5, at: 2026-11-13T00:00:00Z }
---

# Safety checks

- **Symbols.** pixman marks its API `visibility("default")`; PHP links extensions flat-namespace on macOS and ELF interposes, so a Homebrew/system libpixman loaded by another extension (cairo) captured calls mid-image and crashed. `config.m4` exports `get_module` only (`-exported_symbol` / `src/pixman.map`).
- **Operators** in `pixman_op_t`'s gaps reach a NULL combiner. **Formats** unknown to pixman have no fetcher.
- **Filters.** `CONVOLUTION` never checks `n_params` against width × height; `SEPARABLE_CONVOLUTION` reads `params[0..3]` before its own count check. Both checked, phase bits 0..16.
- **Rasteriser.** `pixman_rasterize_edges` loops until `y == b` exactly, unbounded: t and b must be sample-grid values (`pixman_sample_ceil_y(v) == v`; floor is strictly below), t ≥ 0, t ≤ b, b's row inside the image. bpp must be 1, 4 or 8 (`N_Y_FRAC(0)` divides by zero).
- **Edges.** `pixman_edge_step` divides by `dy`; `pixman_edge_init` steps a zero-height edge upwards into that division, and `-dx / dy` traps for `INT32_MIN / -1`. Those inputs are refused.
- **Raw strings.** `pixman_fill` / `pixman_blt` (strides in uint32 units) check every touched row against the string, rounding a row's end up to a whole word as the 1 bpp path writes.
- **Memory.** Caller bits are copied into `malloc` memory the image's destroy function frees; indexed palettes likewise; accessors always install both trampolines (pixman calls a NULL one); frozen glyph caches are thawed before destroy.
