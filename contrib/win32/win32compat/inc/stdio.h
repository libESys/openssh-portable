#include "libopenssh_defs.h"

#include "crtheaders.h"
#include STDIO_H

/* stdio.h overrides */
LIBOPENSSH_API FILE* w32_fopen_utf8(const char *, const char *);
#define fopen w32_fopen_utf8

LIBOPENSSH_API char* w32_fgets(char *str, int n, FILE *stream);
#define fgets w32_fgets

LIBOPENSSH_API int w32_setvbuf(FILE *stream,char *buffer, int mode, size_t size);
#define setvbuf w32_setvbuf

/* stdio.h additional definitions */
#define popen _popen
#define pclose _pclose

LIBOPENSSH_API FILE* w32_fdopen(int fd, const char *mode);
#define fdopen(a,b)	w32_fdopen((a), (b))

LIBOPENSSH_API int w32_rename(const char *old_name, const char *new_name);
#define rename w32_rename
