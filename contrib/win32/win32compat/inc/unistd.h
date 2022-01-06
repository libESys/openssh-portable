/*
* Author: Manoj Ampalam <manoj.ampalam@microsoft.com>
*
* POSIX header and needed function definitions
*/
#pragma once

#include "libopenssh_defs.h"

#include <stddef.h>
#include "sys\types.h"
#include "fcntl.h"
#include "spawn.h"

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define SFTP_SERVER_LOG_FD STDERR_FILENO+1

LIBOPENSSH_API int w32_ftruncate(int, off_t);
#define ftruncate(a, b) w32_ftruncate((a), (b))

#define pipe w32_pipe
LIBOPENSSH_API int w32_pipe(int *pfds);

#define read w32_read
LIBOPENSSH_API int w32_read(int fd, void *dst, size_t max);

#define write w32_write
LIBOPENSSH_API int w32_write(int fd, const void *buf, size_t max);

#define writev w32_writev
LIBOPENSSH_API int w32_writev(int fd, const struct iovec *iov, int iovcnt);

LIBOPENSSH_API int w32_isatty(int fd);
/* can't do this #define isatty w32_isatty
* as there is a variable in code named isatty*/
// #define isatty(a)	w32_isatty((a))

LIBOPENSSH_API int w32_close(int fd);
#define close w32_close

LIBOPENSSH_API int w32_dup(int oldfd);
#define dup w32_dup

LIBOPENSSH_API int w32_dup2(int oldfd, int newfd);
#define dup2 w32_dup2

#define sleep(sec) Sleep(1000 * sec)

LIBOPENSSH_API unsigned int w32_alarm(unsigned int seconds);
#define alarm w32_alarm

LIBOPENSSH_API long w32_lseek(int fd, unsigned __int64 offset, int origin);
#define lseek w32_lseek

#define getdtablesize() MAX_FDS

LIBOPENSSH_API int w32_gethostname(char *, size_t);
#define gethostname w32_gethostname

LIBOPENSSH_API int w32_fsync(int fd);
#define fsync(a) w32_fsync((a))

LIBOPENSSH_API int w32_symlink(const char *target, const char *linkpath);
#define symlink w32_symlink

LIBOPENSSH_API int w32_chown(const char *pathname, unsigned int owner, unsigned int group);
#define chown w32_chown

LIBOPENSSH_API int w32_fchown(int fd, unsigned int owner, unsigned int group);
#define fchown w32_fchown

LIBOPENSSH_API int w32_unlink(const char *path);
#define unlink w32_unlink

LIBOPENSSH_API int w32_rmdir(const char *pathname);
#define rmdir w32_rmdir

LIBOPENSSH_API int w32_chdir(const char *dirname);
#define chdir w32_chdir

LIBOPENSSH_API char *w32_getcwd(char *buffer, int maxlen);
#define getcwd w32_getcwd

LIBOPENSSH_API int w32_readlink(const char *path, char *link, int linklen);
#define readlink w32_readlink

LIBOPENSSH_API int w32_link(const char *oldpath, const char *newpath);
#define link w32_link

LIBOPENSSH_API int getpeereid(int, uid_t*, gid_t*);

LIBOPENSSH_API int daemon(int nochdir, int noclose);
LIBOPENSSH_API char *crypt(const char *key, const char *salt);
LIBOPENSSH_API int chroot(const char *path);

/* 
 * readpassphrase.h definitions 
 * cannot create a separate header due to the way
 * its included in openbsdcompat.h
 */

#define RPP_ECHO_OFF    0x00		/* Turn off echo (default). */
#define RPP_ECHO_ON     0x01		/* Leave echo on. */
#define RPP_REQUIRE_TTY 0x02		/* Fail if there is no tty. */
#define RPP_FORCELOWER  0x04		/* Force input to lower case. */
#define RPP_FORCEUPPER  0x08		/* Force input to upper case. */
#define RPP_SEVENBIT    0x10		/* Strip the high bit from input. */
#define RPP_STDIN       0x20		/* Read from stdin, not /dev/tty */

LIBOPENSSH_API char * readpassphrase(const char *, char *, size_t, int);