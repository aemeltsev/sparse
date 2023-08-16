#ifndef SPARSE_COMMON_H
#define SPARSE_COMMON_H

#if defined(_MSC_VER)
#  ifdef SPARSE_STATIC
#    define SPARSE_EXPORT
#  elif defined(SPARSE_EXPORTS)
#    define SPARSE_EXPORT __declspec(dllexport)
#  else
#    define SPARSE_EXPORT __declspec(dllimport)
#  endif
#  define SPARSE_INLINE __forceinline
#else
#  define SPARSE_EXPORT __attribute__((visibility("default")))
#  define SPARSE_INLINE static inline __attribute((always_inline))
#endif

#endif
