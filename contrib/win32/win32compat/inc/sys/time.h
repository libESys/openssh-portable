
#pragma once

#include "libopenssh_defs.h"

#include <sys\utime.h>

#define utimbuf _utimbuf
#define utimes w32_utimes

LIBOPENSSH_API int usleep(unsigned int);
LIBOPENSSH_API int gettimeofday(struct timeval *, void *);
LIBOPENSSH_API int nanosleep(const struct timespec *, struct timespec *);
LIBOPENSSH_API int w32_utimes(const char *, struct timeval *);