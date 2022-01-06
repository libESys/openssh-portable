/*
* Author: Manoj Ampalam <manoj.ampalam@microsoft.com>
*
* UTF-16 <--> UTF-8 definitions
*/
#pragma once
#ifndef UTF_H
#define UTF_H 1

#include "libopenssh_defs.h"

LIBOPENSSH_API wchar_t* utf8_to_utf16(const char *);
LIBOPENSSH_API char* utf16_to_utf8(const wchar_t*);

#endif