/*
* Author: Manoj Ampalam <manoj.ampalam@microsoft.com>
*
* Compatibility header to give us pwd-like functionality on Win32
* A lot of passwd fields are not applicable in Windows, neither are some API calls based on this structure
* Ideally, usage of this structure needs to be replaced in core SSH code to an ssh_user interface,
* that each platform can extend and implement.
*/

#ifndef COMPAT_PWD_H
#define COMPAT_PWD_H 1

#include "libopenssh_defs.h"

#include "sys\types.h"

struct passwd {
	char	*pw_name;	/* user's login name */
	char	*pw_passwd;	/* password? */
	char	*pw_gecos;	/* ??? */
	uid_t	pw_uid;		/* numerical user ID */
	gid_t	pw_gid;		/* numerical group ID */
	char	*pw_dir;	/* initial working directory */
	char	*pw_shell;	/* path to shell */
};

/*start - declarations not applicable in Windows */
LIBOPENSSH_API uid_t w32_getuid(void);
LIBOPENSSH_API gid_t getgid(void);
LIBOPENSSH_API uid_t geteuid(void);
LIBOPENSSH_API gid_t getegid(void);
LIBOPENSSH_API int setuid(uid_t uid);
LIBOPENSSH_API int setgid(gid_t gid);
LIBOPENSSH_API int seteuid(uid_t uid);
LIBOPENSSH_API int setegid(gid_t gid);
LIBOPENSSH_API char *user_from_uid(uid_t uid, int nouser);
LIBOPENSSH_API struct passwd *getpwent(void);
LIBOPENSSH_API void setpwent(void);

/*end - declarations not applicable in Windows */

LIBOPENSSH_API struct passwd *w32_getpwuid(uid_t uid);
LIBOPENSSH_API struct passwd *w32_getpwnam(const char *username);
LIBOPENSSH_API struct passwd *getpwent(void);
LIBOPENSSH_API void endpwent(void);

#define getpwuid w32_getpwuid
#define getpwnam w32_getpwnam
#define getuid w32_getuid

#endif
