---
type: API
title: Bindings
description: What ext-pixman binds from pixman.h, the translations from C, the one addition and the one exclusion.
resource: stubs/
tags: [pixman, api]
status: draft
generated: { by: claude-opus/5.5, at: 2026-11-13T00:00:00Z }
sources:
  - id: stubs
    resource: stubs/
    title: one stub per area (core, constants, structs, transform, region16/32/64f, image, glyph, trap)
  - id: spec
    resource: docs/superpowers/specs/2026-11-13-pixman-design.md
    title: design spec, Names and translations
---

# Bindings

Every `PIXMAN_API` function in `pixman.h` (179) under its C name except `pixman_region_set_static_pointers`, which swaps process-global region sentinels. No additions. `pixman_image_get_data()` returns the address by default (`copy: true` for a string), and `pixman_image_create_bits(_no_clear)` take a string (copied) or an int address (trusted, borrowed). `tests/CoverageTest.php` checks the set against the header.

Classes are the C type without `_t`. Value structs share one table-driven converter (`src/runtime.c`, `px_struct`); handles are `pixman_image` (one reference per object), `pixman_region16/32/64f` (C storage, init/fini), `pixman_glyph_cache` (freezes counted so destroy always succeeds). Each `ZEND_FUNCTION` is written out; region16 and region64f were derived from region32 by name substitution and then given their extra functions.
