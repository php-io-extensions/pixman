PHP_ARG_ENABLE([pixman],
  [whether to enable pixman support],
  [AS_HELP_STRING([--enable-pixman], [Enable the pixman 0.46.4 bindings])],
  [no])

if test "$PHP_PIXMAN" != "no"; then
  dnl The binding's own C.
  pixman_glue=" \
    src/pixman.c src/runtime.c src/transform.c src/region16.c src/region32.c src/region64f.c \
    src/image.c src/glyph.c src/trap.c"

  dnl pixman 0.46.4 as pixman/meson.build lists it. lib/pixman is never edited;
  dnl src/pixman-config.h and src/pixman-version.h stand in for meson's generated headers.
  pixman_lib=" \
    lib/pixman/pixman/pixman.c \
    lib/pixman/pixman/pixman-access.c \
    lib/pixman/pixman/pixman-access-accessors.c \
    lib/pixman/pixman/pixman-arm.c \
    lib/pixman/pixman/pixman-bits-image.c \
    lib/pixman/pixman/pixman-combine32.c \
    lib/pixman/pixman/pixman-combine-float.c \
    lib/pixman/pixman/pixman-conical-gradient.c \
    lib/pixman/pixman/pixman-edge.c \
    lib/pixman/pixman/pixman-edge-accessors.c \
    lib/pixman/pixman/pixman-fast-path.c \
    lib/pixman/pixman/pixman-filter.c \
    lib/pixman/pixman/pixman-glyph.c \
    lib/pixman/pixman/pixman-general.c \
    lib/pixman/pixman/pixman-gradient-walker.c \
    lib/pixman/pixman/pixman-image.c \
    lib/pixman/pixman/pixman-implementation.c \
    lib/pixman/pixman/pixman-linear-gradient.c \
    lib/pixman/pixman/pixman-matrix.c \
    lib/pixman/pixman/pixman-mips.c \
    lib/pixman/pixman/pixman-noop.c \
    lib/pixman/pixman/pixman-ppc.c \
    lib/pixman/pixman/pixman-radial-gradient.c \
    lib/pixman/pixman/pixman-region16.c \
    lib/pixman/pixman/pixman-region32.c \
    lib/pixman/pixman/pixman-region64f.c \
    lib/pixman/pixman/pixman-riscv.c \
    lib/pixman/pixman/pixman-solid-fill.c \
    lib/pixman/pixman/pixman-timer.c \
    lib/pixman/pixman/pixman-trap.c \
    lib/pixman/pixman/pixman-utils.c \
    lib/pixman/pixman/pixman-x86.c \
"

  dnl SIMD as meson enables it: SSE2 is x86-64's baseline (no extra flag); AArch64
  dnl always has NEON, through pixman's A64 assembly. Anything else runs the C paths.
  case $host_cpu in
    x86_64*|amd64*)
      pixman_lib="$pixman_lib lib/pixman/pixman/pixman-sse2.c"
      ;;
    aarch64*|arm64*)
      pixman_lib="$pixman_lib lib/pixman/pixman/pixman-arm-neon.c \
        lib/pixman/pixman/pixman-arma64-neon-asm.S lib/pixman/pixman/pixman-arma64-neon-asm-bilinear.S"
      ;;
  esac

  PHP_NEW_EXTENSION([pixman],
    [$pixman_glue $pixman_lib],
    [$ext_shared],,
    [-std=gnu17 -fvisibility=hidden -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1 -I$ext_srcdir/src -I$ext_srcdir/lib/pixman/pixman])
  PHP_ADD_BUILD_DIR([$ext_builddir/src])
  PHP_ADD_BUILD_DIR([$ext_builddir/lib/pixman/pixman])

  dnl pixman marks its API visibility("default"). PHP links extensions flat-namespace on macOS
  dnl and ELF interposes by default, so another extension's system libpixman (cairo's) would
  dnl capture this binding's calls mid-image. Export get_module only; pixman stays local.
  case $host_os in
    darwin*)
      PIXMAN_SHARED_LIBADD="-Wl,-exported_symbol,_get_module"
      ;;
    *)
      PIXMAN_SHARED_LIBADD="-Wl,--version-script=$ext_srcdir/src/pixman.map"
      PHP_ADD_LIBRARY([pthread],, [PIXMAN_SHARED_LIBADD])
      PHP_ADD_LIBRARY([m],, [PIXMAN_SHARED_LIBADD])
      ;;
  esac
  PHP_SUBST([PIXMAN_SHARED_LIBADD])
fi
