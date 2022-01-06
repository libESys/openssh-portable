/*!
 * \file sysc/autolink_msvc.h
 * \brief
 *
 * \cond
 * __legal_b__
 *
 * __legal_e__
 * \endcond
 *
 */

//#pragma once

/*
Before including this header you must define one or more of define the following macros:

ESYS_LIB_NAME:           Required: A string containing the basename of the library,
                         for example boost_regex.
ESYS_LIB_TOOLSET:        Optional: the base name of the toolset.
ESYS_DYN_LINK:           Optional: when set link to dll rather than static library.
ESYS_LIB_DIAGNOSTIC:     Optional: when set the header will print out the name
                         of the library selected (useful for debugging).
*/

/*
Libraries for Microsoft compilers are automatically
selected here, the name of the lib is selected according to the following
formula :

ESYS_LIB_PREFIX
+ ESYS_LIB_NAME
+ "_"
+ ESYS_LIB_TOOLSET
+ ESYS_LIB_RT_OPT
+ ESYS_LIB_ARCH
"-"
+ ESYS_LIB_VERSION

These are defined as :
    ESYS_LIB_PREFIX  : "lib" for static libraries otherwise "".
    ESYS_LIB_NAME    : The base name of the lib(for example boost_regex).
    ESYS_LIB_TOOLSET : The compiler toolset name(vc6, vc7, bcb5 etc).
    ESYS_LIB_RT_OPT  : A suffix that indicates the runtime library used,
                       contains one or more of the following letters after a hyphen :
                       g      debug / diagnostic runtime(release if not present).
                       d      debug build(release if not present).

    ESYS_LIB_ARCH    : The architecture and address model
                                 (-x32 or -x64 for x86 / 32 and x86 / 64 respectively)

    ESYS_LIB_VERSION : The Boost version, in the form x_y, for Boost version x.y.


*/

#define ESYS_STRINGIZE(X) ESYS_DO_STRINGIZE(X)
#define ESYS_DO_STRINGIZE(X) #X

#ifdef _MSC_VER

#ifndef ESYS_LIB_TOOLSET
#if _MSC_VER < 1200
// Note: no compilers before 1200 are supported
#elif _MSC_VER < 1300

#elif _MSC_VER < 1310
// vc7:
#define ESYS_LIB_TOOLSET "vc7"

#elif _MSC_VER < 1400
// vc71:
#define ESYS_LIB_TOOLSET "vc71"

#elif _MSC_VER < 1500
// vc80:
#define ESYS_LIB_TOOLSET "vc80"

#elif _MSC_VER < 1600
// vc90:
#define ESYS_LIB_TOOLSET "vc90"

#elif _MSC_VER < 1700
// vc10:
#define ESYS_LIB_TOOLSET "vc100"

#elif _MSC_VER < 1800
// vc11:
#define ESYS_LIB_TOOLSET "vc110"

#elif _MSC_VER < 1900
// vc12:
#define ESYS_LIB_TOOLSET "vc120"

#elif _MSC_VER < 1910
// vc14:
#define ESYS_LIB_TOOLSET "vc140"

#elif _MSC_VER < 1920
// vc14.1:
#define ESYS_LIB_TOOLSET "vc141"

#else
// vc14.2:
#define ESYS_LIB_TOOLSET "vc142"
#endif

#endif

#if defined(_M_IX86)
#define ESYS_LIB_ARCH "-x32"
#elif defined(_M_X64)
#define ESYS_LIB_ARCH "-x64"
#elif defined(_M_ARM)
#define ESYS_LIB_ARCH "-a32"
#elif defined(_M_ARM64)
#define ESYS_LIB_ARCH "-a64"
#endif

#if defined(_DEBUG)
#define ESYS_LIB_RT_OPT "-gd"
#else
#define ESYS_LIB_RT_OPT
#endif

#if defined(_DLL) && (defined(ESYS_DYN_LINK) || !defined(ESYS_STATIC_LINK))
#define ESYS_LIB_PREFIX
#elif defined(ESYS_DYN_LINK)
#error "Mixing a dll boost library with a static runtime is a really bad idea..."
#else
#define ESYS_LIB_PREFIX "lib"
#endif

#if defined(ESYS_LIB_NAME) && defined(ESYS_LIB_PREFIX) && defined(ESYS_LIB_TOOLSET) && defined(ESYS_LIB_RT_OPT) \
    && defined(ESYS_LIB_ARCH) && defined(ESYS_LIB_VERSION)
#else
#ifndef ESYS_LIB_NAME
#pragma message("ESYS_LIB_NAME not defined")
#endif

#ifndef ESYS_LIB_PREFIX
#pragma message("ESYS_LIB_PREFIX not defined")
#endif

#ifndef ESYS_LIB_TOOLSET
#pragma message("ESYS_LIB_TOOLSET not defined")
#endif

#ifndef ESYS_LIB_RT_OPT
#pragma message("ESYS_LIB_RT_OPT not defined")
#endif

#ifndef ESYS_LIB_ARCH
#pragma message("ESYS_LIB_ARCH not defined")
#endif

#ifndef ESYS_LIB_VERSION
#pragma message("ESYS_LIB_VERSION not defined")
#endif

#error "some required macros where not defined (internal logic error)."
#endif

#pragma comment(lib, ESYS_LIB_PREFIX ESYS_STRINGIZE(ESYS_LIB_NAME) "-" ESYS_LIB_TOOLSET ESYS_LIB_RT_OPT ESYS_LIB_ARCH \
                     "-" ESYS_LIB_VERSION ".lib")
#ifdef ESYS_LIB_DIAGNOSTIC
#pragma message("Linking to lib file: " ESYS_LIB_PREFIX ESYS_STRINGIZE( \
    ESYS_LIB_NAME) "-" ESYS_LIB_TOOLSET ESYS_LIB_RT_OPT ESYS_LIB_ARCH "-" ESYS_LIB_VERSION ".lib")
#endif

#ifdef ESYS_LIB_PREFIX
#undef ESYS_LIB_PREFIX
#endif

#ifdef ESYS_LIB_TOOLSET
#undef ESYS_LIB_TOOLSET
#endif

#ifdef ESYS_LIB_ARCH
#undef ESYS_LIB_ARCH
#endif

#ifdef ESYS_LIB_RT_OPT
#undef ESYS_LIB_RT_OPT
#endif

#ifdef ESYS_LIB_VERSION
#undef ESYS_LIB_VERSION
#endif

#ifdef ESYS_LIB_NAME
#undef ESYS_LIB_NAME
#endif

#endif
