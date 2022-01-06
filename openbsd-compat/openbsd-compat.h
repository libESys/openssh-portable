/*
 * Copyright (c) 1999-2003 Damien Miller.  All rights reserved.
 * Copyright (c) 2003 Ben Lindstrom. All rights reserved.
 * Copyright (c) 2002 Tim Rice.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _OPENBSD_COMPAT_H
#define _OPENBSD_COMPAT_H

#include "libopenssh_defs.h"

#include "includes.h"

#include <sys/types.h>
#include <pwd.h>

#include <sys/socket.h>

#include <stddef.h>  /* for wchar_t */

/* OpenBSD function replacements */
#include "base64.h"
#include "sigact.h"
#include "readpassphrase.h"
#include "vis.h"
#include "getrrsetbyname.h"
#include "sha1.h"
#include "sha2.h"
#include "md5.h"
#include "blf.h"
#include "fnmatch.h"

#if defined(HAVE_LOGIN_CAP) && !defined(HAVE_LOGIN_GETPWCLASS)
# define login_getpwclass(pw) login_getclass(pw->pw_class)
#endif

#ifndef HAVE_BASENAME
LIBOPENSSH_API char *basename(const char *path);
#endif

#ifndef HAVE_BINDRESVPORT_SA
LIBOPENSSH_API int bindresvport_sa(int sd, struct sockaddr *sa);
#endif

#ifndef HAVE_CLOSEFROM
LIBOPENSSH_API void closefrom(int);
#endif

#ifndef HAVE_GETLINE
#include <stdio.h>
LIBOPENSSH_API ssize_t getline(char **, size_t *, FILE *);
#endif

#ifndef HAVE_GETPAGESIZE
LIBOPENSSH_API int getpagesize(void);
#endif

#ifndef HAVE_GETCWD
LIBOPENSSH_API char *getcwd(char *pt, size_t size);
#endif

#if defined(HAVE_DECL_MEMMEM) && HAVE_DECL_MEMMEM == 0
LIBOPENSSH_API void *memmem(const void *, size_t, const void *, size_t);
#endif

#ifndef HAVE_REALLOCARRAY
LIBOPENSSH_API void *reallocarray(void *, size_t, size_t);
#endif

#ifndef HAVE_RECALLOCARRAY
LIBOPENSSH_API void *recallocarray(void *, size_t, size_t, size_t);
#endif

#ifndef HAVE_RRESVPORT_AF
LIBOPENSSH_API int rresvport_af(int *alport, sa_family_t af);
#endif

#ifndef HAVE_STRLCPY
LIBOPENSSH_API size_t strlcpy(char *dst, const char *src, size_t siz);
#endif

#ifndef HAVE_STRLCAT
LIBOPENSSH_API size_t strlcat(char *dst, const char *src, size_t siz);
#endif

#ifndef HAVE_STRCASESTR
LIBOPENSSH_API char *strcasestr(const char *, const char *);
#endif

#ifndef HAVE_STRNLEN
LIBOPENSSH_API size_t strnlen(const char *, size_t);
#endif

#ifndef HAVE_STRNDUP
LIBOPENSSH_API char *strndup(const char *s, size_t n);
#endif

#ifndef HAVE_SETENV
LIBOPENSSH_API int setenv(register const char *name, register const char *value, int rewrite);
#endif

#ifndef HAVE_STRMODE
LIBOPENSSH_API void strmode(int mode, char *p);
#endif

#ifndef HAVE_STRPTIME
#include  <time.h>
LIBOPENSSH_API char *strptime(const char *buf, const char *fmt, struct tm *tm);
#endif

#if !defined(HAVE_MKDTEMP)
LIBOPENSSH_API int mkstemps(char *path, int slen);
LIBOPENSSH_API int mkstemp(char *path);
LIBOPENSSH_API char *mkdtemp(char *path);
#endif

#ifndef HAVE_DAEMON
LIBOPENSSH_API int daemon(int nochdir, int noclose);
#endif

#ifndef HAVE_DIRNAME
LIBOPENSSH_API char *dirname(const char *path);
#endif

#ifndef HAVE_FMT_SCALED
#define	FMT_SCALED_STRSIZE	7
LIBOPENSSH_API int	fmt_scaled(long long number, char *result);
#endif

#ifndef HAVE_SCAN_SCALED
LIBOPENSSH_API int	scan_scaled(char *, long long *);
#endif

#if defined(BROKEN_INET_NTOA) || !defined(HAVE_INET_NTOA)
LIBOPENSSH_API char *inet_ntoa(struct in_addr in);
#endif

#ifndef HAVE_INET_NTOP
LIBOPENSSH_API const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
#endif

#ifndef HAVE_INET_ATON
LIBOPENSSH_API int inet_aton(const char *cp, struct in_addr *addr);
#endif

#ifndef HAVE_STRSEP
LIBOPENSSH_API char *strsep(char **stringp, const char *delim);
#endif

#ifndef HAVE_SETPROCTITLE
LIBOPENSSH_API void setproctitle(const char *fmt, ...);
LIBOPENSSH_API void compat_init_setproctitle(int argc, char *argv[]);
#endif

#ifndef HAVE_GETGROUPLIST
LIBOPENSSH_API int getgrouplist(const char *, gid_t, gid_t *, int *);
#endif

#if !defined(HAVE_GETOPT) || !defined(HAVE_GETOPT_OPTRESET)
LIBOPENSSH_API int BSDgetopt(int argc, char * const *argv, const char *opts);
#include "openbsd-compat/getopt.h"
#endif

#if ((defined(HAVE_DECL_READV) && HAVE_DECL_READV == 0) || \
    (defined(HAVE_DECL_WRITEV) && HAVE_DECL_WRITEV == 0))
# include <sys/types.h>
# include <sys/uio.h>

# if defined(HAVE_DECL_READV) && HAVE_DECL_READV == 0
LIBOPENSSH_API int readv(int, struct iovec *, int);
# endif

# if defined(HAVE_DECL_WRITEV) && HAVE_DECL_WRITEV == 0
LIBOPENSSH_API int writev(int, struct iovec *, int);
# endif
#endif

/* Home grown routines */
#include "bsd-misc.h"
#include "bsd-setres_id.h"
#include "bsd-signal.h"
#include "bsd-statvfs.h"
#include "bsd-waitpid.h"
#include "bsd-poll.h"

#if defined(HAVE_DECL_GETPEEREID) && HAVE_DECL_GETPEEREID == 0
LIBOPENSSH_API int getpeereid(int , uid_t *, gid_t *);
#endif

#ifdef HAVE_ARC4RANDOM
# ifndef HAVE_ARC4RANDOM_STIR
#  define arc4random_stir()
# endif
#else
LIBOPENSSH_API unsigned int arc4random(void);
LIBOPENSSH_API void arc4random_stir(void);
#endif /* !HAVE_ARC4RANDOM */

#ifndef HAVE_ARC4RANDOM_BUF
LIBOPENSSH_API void arc4random_buf(void *, size_t);
#endif

#ifndef HAVE_ARC4RANDOM_UNIFORM
LIBOPENSSH_API u_int32_t arc4random_uniform(u_int32_t);
#endif

#ifndef HAVE_ASPRINTF
LIBOPENSSH_API int asprintf(char **, const char *, ...);
#endif

#ifndef HAVE_OPENPTY
# include <sys/ioctl.h>	/* for struct winsize */
LIBOPENSSH_API int openpty(int *, int *, char *, struct termios *, struct winsize *);
#endif /* HAVE_OPENPTY */

#ifndef HAVE_SNPRINTF
LIBOPENSSH_API int snprintf(char *, size_t, SNPRINTF_CONST char *, ...);
#endif

#ifndef HAVE_STRTOLL
LIBOPENSSH_API long long strtoll(const char *, char **, int);
#endif

#ifndef HAVE_STRTOUL
LIBOPENSSH_API unsigned long strtoul(const char *, char **, int);
#endif

#ifndef HAVE_STRTOULL
LIBOPENSSH_API unsigned long long strtoull(const char *, char **, int);
#endif

#ifndef HAVE_STRTONUM
LIBOPENSSH_API long long strtonum(const char *, long long, long long, const char **);
#endif

/* multibyte character support */
#ifndef HAVE_MBLEN
# define mblen(x, y)	(1)
#endif

#ifndef HAVE_WCWIDTH
# define wcwidth(x)	(((x) >= 0x20 && (x) <= 0x7e) ? 1 : -1)
/* force our no-op nl_langinfo and mbtowc */
# undef HAVE_NL_LANGINFO
#ifndef WINDOWS
/* Windows does not have wcwidth but does have mbtowc*/
# undef HAVE_MBTOWC
#endif  /* WINDOWS */
# undef HAVE_LANGINFO_H
#endif

#ifndef HAVE_NL_LANGINFO
# define nl_langinfo(x)	""
#endif

#ifndef HAVE_MBTOWC
LIBOPENSSH_API int mbtowc(wchar_t *, const char*, size_t);
#endif

#if !defined(HAVE_VASPRINTF) || !defined(HAVE_VSNPRINTF)
# include <stdarg.h>
#endif

/*
 * Some platforms unconditionally undefine va_copy() so we define VA_COPY()
 * instead.  This is known to be the case on at least some configurations of
 * AIX with the xlc compiler.
 */
#ifndef VA_COPY
# ifdef HAVE_VA_COPY
#  define VA_COPY(dest, src) va_copy(dest, src)
# else
#  ifdef HAVE___VA_COPY
#   define VA_COPY(dest, src) __va_copy(dest, src)
#  else
#   define VA_COPY(dest, src) (dest) = (src)
#  endif
# endif
#endif

#ifndef HAVE_VASPRINTF
LIBOPENSSH_API int vasprintf(char **, const char *, va_list);
#endif

#ifndef HAVE_VSNPRINTF
LIBOPENSSH_API int vsnprintf(char *, size_t, const char *, va_list);
#endif

#ifndef HAVE_USER_FROM_UID
LIBOPENSSH_API char *user_from_uid(uid_t, int);
#endif

#ifndef HAVE_GROUP_FROM_GID
LIBOPENSSH_API char *group_from_gid(gid_t, int);
#endif

#ifndef HAVE_TIMINGSAFE_BCMP
LIBOPENSSH_API int timingsafe_bcmp(const void *, const void *, size_t);
#endif

#ifndef HAVE_BCRYPT_PBKDF
LIBOPENSSH_API int	bcrypt_pbkdf(const char *, size_t, const u_int8_t *, size_t,
    u_int8_t *, size_t, unsigned int);
#endif

#ifndef HAVE_EXPLICIT_BZERO
LIBOPENSSH_API void explicit_bzero(void *p, size_t n);
#endif

#ifndef HAVE_FREEZERO
LIBOPENSSH_API void freezero(void *, size_t);
#endif

#ifndef HAVE_LOCALTIME_R
LIBOPENSSH_API struct tm *localtime_r(const time_t *, struct tm *);
#endif

LIBOPENSSH_API char *xcrypt(const char *password, const char *salt);
LIBOPENSSH_API char *shadow_pw(struct passwd *pw);

/* rfc2553 socket API replacements */
#include "fake-rfc2553.h"

/* Routines for a single OS platform */
#include "bsd-cygwin_util.h"

#include "port-aix.h"
#include "port-irix.h"
#include "port-linux.h"
#include "port-solaris.h"
#include "port-net.h"
#include "port-uw.h"

/* _FORTIFY_SOURCE breaks FD_ISSET(n)/FD_SET(n) for n > FD_SETSIZE. Avoid. */
#if defined(HAVE_FEATURES_H) && defined(_FORTIFY_SOURCE)
# include <features.h>
# if defined(__GNU_LIBRARY__) && defined(__GLIBC_PREREQ)
#  if __GLIBC_PREREQ(2, 15) && (_FORTIFY_SOURCE > 0)
#   include <sys/socket.h>  /* Ensure include guard is defined */
#   undef FD_SET
#   undef FD_ISSET
#   define FD_SET(n, set)	kludge_FD_SET(n, set)
#   define FD_ISSET(n, set)	kludge_FD_ISSET(n, set)
LIBOPENSSH_API void kludge_FD_SET(int, fd_set *);
LIBOPENSSH_API int kludge_FD_ISSET(int, fd_set *);
#  endif /* __GLIBC_PREREQ(2, 15) && (_FORTIFY_SOURCE > 0) */
# endif /* __GNU_LIBRARY__ && __GLIBC_PREREQ */
#endif /* HAVE_FEATURES_H && _FORTIFY_SOURCE */

#endif /* _OPENBSD_COMPAT_H */
