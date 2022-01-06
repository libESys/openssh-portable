#include "libopenssh_defs.h"

#include "crtheaders.h"
#include STDLIB_H

#define environ _environ
LIBOPENSSH_API void freezero(void *, size_t);
LIBOPENSSH_API int setenv(const char *name, const char *value, int rewrite);
#define system w32_system
LIBOPENSSH_API int w32_system(const char *command);
LIBOPENSSH_API char* realpath(const char *pathname, char *resolved);
