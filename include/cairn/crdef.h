#ifndef CR_DEF_H
#define CR_DEF_H

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#    define CR_NORETURN _Noreturn
#elif defined(__GNUC__) || defined(__clang__)
#    define CR_NORETURN __attribute__((__noreturn__))
#elif defined(_MSC_VER)
#    define CR_NORETURN __declspec(noreturn)
#else
#    define CR_NORETURN
#endif

#endif
