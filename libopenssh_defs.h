/*!
 * \file libopenssh_defs.h
 * \brief Definitions needed for libopenssh
 *
 * \cond
 * __legal_b__
 *
 * __legal_e__
 * \endcond
 *
 */

#pragma once

#ifdef LIBOPENSSH_EXPORTS
#define LIBOPENSSH_API __declspec(dllexport)
#elif LIBOPENSSH_USE
#define LIBOPENSSH_API __declspec(dllimport)
#else
#define LIBOPENSSH_API
#endif

#ifdef WIN32
#include "openssh_autolink.h"
#endif