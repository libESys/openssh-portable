// direntry functions in Windows platform like Ubix/Linux
// opendir(), readdir(), closedir().
// 	NT_DIR * nt_opendir(char *name) ;
// 	struct nt_dirent *nt_readdir(NT_DIR *dirp);
// 	int nt_closedir(NT_DIR *dirp) ;

#ifndef __DIRENT_H__
#define __DIRENT_H__

#include "libopenssh_defs.h"

#include <direct.h>
#include <io.h>
#include <fcntl.h>
#include "..\misc_internal.h"

struct dirent {
	int            d_ino;       /* Inode number */
	char           d_name[PATH_MAX]; /* Null-terminated filename */
};

typedef struct DIR_ DIR;

LIBOPENSSH_API DIR * opendir(const char*);
LIBOPENSSH_API int closedir(DIR*);
LIBOPENSSH_API struct dirent *readdir(void*);

#endif