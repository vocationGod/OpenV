#pragma once

#define OPENV_VERSION_MAJOR 0
#define OPENV_VERSION_MINOR 0
#define OPENV_VERSION_PATCH 1

#if defined(_WIN32) || defined(__CYGWIN__)
    #if defined(OPENV_BUILD)
        #define OPENV_API __declspec(dllexport)
    #else
        #define OPENV_API __declspec(dllimport)
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define OPENV_API __attribute__((visibility("default")))
#else
    #define OPENV_API
#endif

#define OPENV_DISABLE_COPY(A) \
    A (const A&) = delete; \
    A& operator= (const A&) = delete;

#define OPENV_DECLARE_PRIVATE(A) \
    protected: \
    A ## Private* d_func() { return reinterpret_cast<A ## Private*>(dptr.get()); } \
    const A ## Private* d_func() const { return reinterpret_cast<const A ## Private*>(dptr.get()); } \
    friend class A ## Private;

#define OPENV_DECLARE_PUBLIC(A) \
    friend class A;

#define OPENV_D(A) A ## Private * const d = d_func()

#define OPENV_ALIGN(x, align)  (((x) + (align) - 1) & ~((align) - 1))

#include <cstdint>
#include <cstddef>
