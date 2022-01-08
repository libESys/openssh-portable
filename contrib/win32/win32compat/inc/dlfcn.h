#pragma once

#include "libopenssh_defs.h"

#include <Windows.h>
#define RTLD_NOW 0

LIBOPENSSH_API HMODULE dlopen(const char *filename, int flags);

LIBOPENSSH_API int dlclose(HMODULE handle);
LIBOPENSSH_API void * dlsym(HMODULE handle, const char *symbol);
LIBOPENSSH_API char * dlerror();
