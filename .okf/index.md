---
okf_version: "0.2"
---

# ext-pixman

1:1 PHP bindings of pixman 0.46.4 (vendored, unchanged), the pixel-manipulation library under cairo and the X server. Version 0.11.0. Linux, macOS. PHP 8.4 NTS + ZTS.

# API

* [Bindings](api/bindings.md) — 178 functions, one addition, value-struct and handle classes, constants; what is not bound.

# Architecture

* [Safety checks](architecture/checks.md) — the inputs pixman trusts and the binding refuses, symbol export, memory ownership.

# Runbooks

* [Build, install, test](runbooks/build.md) — Mac NTS/ZTS, Debian, the crash sweep.
