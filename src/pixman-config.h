/*
 * pixman-config.h: the defines pixman's meson build writes for a GCC or Clang
 * build on macOS or Linux. pixman includes it through HAVE_CONFIG_H, which
 * PHP's build defines for every file.
 *
 * SIMD: x86-64 has SSE2 as its baseline, so pixman-sse2.c builds with no extra
 * flags. AArch64 takes pixman's A64 NEON assembly (both .S files). Other
 * targets use pixman's C paths.
 */

#ifndef EXT_PIXMAN_CONFIG_H
#define EXT_PIXMAN_CONFIG_H

#define PACKAGE "pixman"
#define SIZEOF_LONG __SIZEOF_LONG__

#define HAVE_PTHREADS 1
#define TLS __thread
#define TOOLCHAIN_SUPPORTS_ATTRIBUTE_CONSTRUCTOR 1
#define TOOLCHAIN_SUPPORTS_ATTRIBUTE_DESTRUCTOR 1
#define HAVE_BUILTIN_CLZ 1
#define HAVE_GCC_VECTOR_EXTENSIONS 1

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
#endif

#if defined(__x86_64__)
#  define USE_SSE2 1
#endif

#if defined(__aarch64__)
#  define USE_ARM_A64_NEON 1
#  if defined(__APPLE__)
#    define ASM_LEADING_UNDERSCORE 1
#  else
#    define ASM_HAVE_FUNC_DIRECTIVE 1
#  endif
#endif

#endif
