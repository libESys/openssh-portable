/* $OpenBSD: misc.h,v 1.95 2021/04/03 06:18:40 djm Exp $ */

/*
 * Author: Tatu Ylonen <ylo@cs.hut.fi>
 * Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 *                    All rights reserved
 *
 * As far as I am concerned, the code I have written for this software
 * can be used freely for any purpose.  Any derived versions of this
 * software must be clearly marked as such, and if the derived work is
 * incompatible with the protocol description in the RFC file, it must be
 * called by a name other than "ssh" or "Secure Shell".
 */

#ifndef _MISC_H
#define _MISC_H

#include "libopenssh_defs.h"

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

/* Data structure for representing a forwarding request. */
struct Forward {
	char	 *listen_host;		/* Host (address) to listen on. */
	int	  listen_port;		/* Port to forward. */
	char	 *listen_path;		/* Path to bind domain socket. */
	char	 *connect_host;		/* Host to connect. */
	int	  connect_port;		/* Port to connect on connect_host. */
	char	 *connect_path;		/* Path to connect domain socket. */
	int	  allocated_port;	/* Dynamically allocated listen port */
	int	  handle;		/* Handle for dynamic listen ports */
};

LIBOPENSSH_API int forward_equals(const struct Forward *, const struct Forward *);
LIBOPENSSH_API int daemonized(void);

/* Common server and client forwarding options. */
struct ForwardOptions {
	int	 gateway_ports; /* Allow remote connects to forwarded ports. */
	mode_t	 streamlocal_bind_mask; /* umask for streamlocal binds */
	int	 streamlocal_bind_unlink; /* unlink socket before bind */
};

/* misc.c */

LIBOPENSSH_API char	*chop(char *);
LIBOPENSSH_API void	skip_space(char **);
LIBOPENSSH_API char	*strdelim(char **);
LIBOPENSSH_API char	*strdelimw(char **);
LIBOPENSSH_API int	 set_nonblock(int);
LIBOPENSSH_API int	 unset_nonblock(int);
LIBOPENSSH_API void	 set_nodelay(int);
LIBOPENSSH_API int	 set_reuseaddr(int);
LIBOPENSSH_API char	*get_rdomain(int);
LIBOPENSSH_API int	 set_rdomain(int, const char *);
LIBOPENSSH_API int	 get_sock_af(int);
LIBOPENSSH_API void	 set_sock_tos(int, int);
LIBOPENSSH_API int	 waitrfd(int, int *);
LIBOPENSSH_API int	 timeout_connect(int, const struct sockaddr *, socklen_t, int *);
LIBOPENSSH_API int	 a2port(const char *);
LIBOPENSSH_API int	 a2tun(const char *, int *);
LIBOPENSSH_API char	*put_host_port(const char *, u_short);
LIBOPENSSH_API char	*hpdelim2(char **, char *);
LIBOPENSSH_API char	*hpdelim(char **);
LIBOPENSSH_API char	*cleanhostname(char *);
LIBOPENSSH_API char	*colon(char *);
LIBOPENSSH_API int	 parse_user_host_path(const char *, char **, char **, char **);
LIBOPENSSH_API int	 parse_user_host_port(const char *, char **, char **, int *);
LIBOPENSSH_API int	 parse_uri(const char *, const char *, char **, char **, int *, char **);
LIBOPENSSH_API int	 convtime(const char *);
LIBOPENSSH_API const char *fmt_timeframe(time_t t);
LIBOPENSSH_API char	*tilde_expand_filename(const char *, uid_t);

LIBOPENSSH_API char	*dollar_expand(int *, const char *string, ...);
LIBOPENSSH_API char	*percent_expand(const char *, ...) __attribute__((__sentinel__));
LIBOPENSSH_API char	*percent_dollar_expand(const char *, ...) __attribute__((__sentinel__));
LIBOPENSSH_API char	*tohex(const void *, size_t);
LIBOPENSSH_API void	 xextendf(char **s, const char *sep, const char *fmt, ...)
    __attribute__((__format__ (printf, 3, 4))) __attribute__((__nonnull__ (3)));
LIBOPENSSH_API void	 sanitise_stdfd(void);
LIBOPENSSH_API void	 ms_subtract_diff(struct timeval *, int *);
LIBOPENSSH_API void	 ms_to_timeval(struct timeval *, int);
LIBOPENSSH_API void	 monotime_ts(struct timespec *);
LIBOPENSSH_API void	 monotime_tv(struct timeval *);
LIBOPENSSH_API time_t	 monotime(void);
LIBOPENSSH_API double	 monotime_double(void);
LIBOPENSSH_API void	 lowercase(char *s);
LIBOPENSSH_API int	 unix_listener(const char *, int, int);
LIBOPENSSH_API int	 valid_domain(char *, int, const char **);
LIBOPENSSH_API int	 valid_env_name(const char *);
LIBOPENSSH_API const char *atoi_err(const char *, int *);
LIBOPENSSH_API int	 parse_absolute_time(const char *, uint64_t *);
LIBOPENSSH_API void	 format_absolute_time(uint64_t, char *, size_t);
LIBOPENSSH_API int	 path_absolute(const char *);
LIBOPENSSH_API int	 stdfd_devnull(int, int, int);

LIBOPENSSH_API void	 sock_set_v6only(int);

LIBOPENSSH_API struct passwd *pwcopy(struct passwd *);
LIBOPENSSH_API const char *ssh_gai_strerror(int);

typedef void privdrop_fn(struct passwd *);
typedef void privrestore_fn(void);
#define	SSH_SUBPROCESS_STDOUT_DISCARD	(1)     /* Discard stdout */
#define	SSH_SUBPROCESS_STDOUT_CAPTURE	(1<<1)  /* Redirect stdout */
#define	SSH_SUBPROCESS_STDERR_DISCARD	(1<<2)  /* Discard stderr */
#define	SSH_SUBPROCESS_UNSAFE_PATH	(1<<3)	/* Don't check for safe cmd */
#define	SSH_SUBPROCESS_PRESERVE_ENV	(1<<4)	/* Keep parent environment */
LIBOPENSSH_API pid_t subprocess(const char *, const char *, int, char **, FILE **, u_int,
    struct passwd *, privdrop_fn *, privrestore_fn *);

typedef struct arglist arglist;
struct arglist {
	char    **list;
	u_int   num;
	u_int   nalloc;
};
LIBOPENSSH_API void	 addargs(arglist *, char *, ...)
	    __attribute__((format(printf, 2, 3)));
LIBOPENSSH_API void	 replacearg(arglist *, u_int, char *, ...)
	    __attribute__((format(printf, 3, 4)));
LIBOPENSSH_API void	 freeargs(arglist *);

LIBOPENSSH_API int	 tun_open(int, int, char **);

/* Common definitions for ssh tunnel device forwarding */
#define SSH_TUNMODE_NO		0x00
#define SSH_TUNMODE_POINTOPOINT	0x01
#define SSH_TUNMODE_ETHERNET	0x02
#define SSH_TUNMODE_DEFAULT	SSH_TUNMODE_POINTOPOINT
#define SSH_TUNMODE_YES		(SSH_TUNMODE_POINTOPOINT|SSH_TUNMODE_ETHERNET)

#define SSH_TUNID_ANY		0x7fffffff
#define SSH_TUNID_ERR		(SSH_TUNID_ANY - 1)
#define SSH_TUNID_MAX		(SSH_TUNID_ANY - 2)

/* Fake port to indicate that host field is really a path. */
#define PORT_STREAMLOCAL	-2

/* Functions to extract or store big-endian words of various sizes */
LIBOPENSSH_API u_int64_t	get_u64(const void *)
    __attribute__((__bounded__( __minbytes__, 1, 8)));
LIBOPENSSH_API u_int32_t	get_u32(const void *)
    __attribute__((__bounded__( __minbytes__, 1, 4)));
LIBOPENSSH_API u_int16_t	get_u16(const void *)
    __attribute__((__bounded__( __minbytes__, 1, 2)));
LIBOPENSSH_API void		put_u64(void *, u_int64_t)
    __attribute__((__bounded__( __minbytes__, 1, 8)));
LIBOPENSSH_API void		put_u32(void *, u_int32_t)
    __attribute__((__bounded__( __minbytes__, 1, 4)));
LIBOPENSSH_API void		put_u16(void *, u_int16_t)
    __attribute__((__bounded__( __minbytes__, 1, 2)));

/* Little-endian store/load, used by umac.c */
LIBOPENSSH_API u_int32_t	get_u32_le(const void *)
    __attribute__((__bounded__(__minbytes__, 1, 4)));
LIBOPENSSH_API void		put_u32_le(void *, u_int32_t)
    __attribute__((__bounded__(__minbytes__, 1, 4)));

struct bwlimit {
	size_t buflen;
	u_int64_t rate;		/* desired rate in kbit/s */
	u_int64_t thresh;	/* threshold after which we'll check timers */
	u_int64_t lamt;		/* amount written in last timer interval */
	struct timeval bwstart, bwend;
};

LIBOPENSSH_API void bandwidth_limit_init(struct bwlimit *, u_int64_t, size_t);
LIBOPENSSH_API void bandwidth_limit(struct bwlimit *, size_t);

LIBOPENSSH_API int parse_ipqos(const char *);
LIBOPENSSH_API const char *iptos2str(int);
LIBOPENSSH_API void mktemp_proto(char *, size_t);

LIBOPENSSH_API void	 child_set_env(char ***envp, u_int *envsizep, const char *name,
	    const char *value);

LIBOPENSSH_API int	 argv_split(const char *, int *, char ***);
LIBOPENSSH_API char	*argv_assemble(int, char **argv);
LIBOPENSSH_API int	 exited_cleanly(pid_t, const char *, const char *, int);

struct stat;
LIBOPENSSH_API int	 safe_path(const char *, struct stat *, const char *, uid_t,
	    char *, size_t);
LIBOPENSSH_API int	 safe_path_fd(int, const char *, struct passwd *,
	    char *err, size_t errlen);

/* authorized_key-style options parsing helpers */
LIBOPENSSH_API int	opt_flag(const char *opt, int allow_negate, const char **optsp);
LIBOPENSSH_API char	*opt_dequote(const char **sp, const char **errstrp);
LIBOPENSSH_API int	opt_match(const char **opts, const char *term);

/* readconf/servconf option lists */
LIBOPENSSH_API void	opt_array_append(const char *file, const int line,
	    const char *directive, char ***array, u_int *lp, const char *s);
LIBOPENSSH_API void	opt_array_append2(const char *file, const int line,
	    const char *directive, char ***array, int **iarray, u_int *lp,
	    const char *s, int i);

/* readpass.c */

#define RP_ECHO			0x0001
#define RP_ALLOW_STDIN		0x0002
#define RP_ALLOW_EOF		0x0004
#define RP_USE_ASKPASS		0x0008

struct notifier_ctx;

LIBOPENSSH_API char	*read_passphrase(const char *, int);
LIBOPENSSH_API int	 ask_permission(const char *, ...) __attribute__((format(printf, 1, 2)));
LIBOPENSSH_API struct notifier_ctx *notify_start(int, const char *, ...)
	__attribute__((format(printf, 2, 3)));
LIBOPENSSH_API void	notify_complete(struct notifier_ctx *, const char *, ...)
	__attribute__((format(printf, 2, 3)));

#define MINIMUM(a, b)	(((a) < (b)) ? (a) : (b))
#define MAXIMUM(a, b)	(((a) > (b)) ? (a) : (b))
#define ROUNDUP(x, y)   ((((x)+((y)-1))/(y))*(y))

typedef void (*sshsig_t)(int);
LIBOPENSSH_API sshsig_t ssh_signal(int, sshsig_t);

#endif /* _MISC_H */
