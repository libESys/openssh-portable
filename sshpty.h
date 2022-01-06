/* $OpenBSD: sshpty.h,v 1.13 2016/11/29 03:54:50 dtucker Exp $ */

/*
 * Author: Tatu Ylonen <ylo@cs.hut.fi>
 * Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 *                    All rights reserved
 * Functions for allocating a pseudo-terminal and making it the controlling
 * tty.
 *
 * As far as I am concerned, the code I have written for this software
 * can be used freely for any purpose.  Any derived versions of this
 * software must be clearly marked as such, and if the derived work is
 * incompatible with the protocol description in the RFC file, it must be
 * called by a name other than "ssh" or "Secure Shell".
 */

#pragma once

#include "libopenssh_defs.h"

#include <termios.h>

LIBOPENSSH_API struct termios *get_saved_tio(void);
LIBOPENSSH_API void	 leave_raw_mode(int);
LIBOPENSSH_API void	 enter_raw_mode(int);

LIBOPENSSH_API int	 pty_allocate(int *, int *, char *, size_t);
LIBOPENSSH_API void	 pty_release(const char *);
LIBOPENSSH_API void	 pty_make_controlling_tty(int *, const char *);
LIBOPENSSH_API void	 pty_change_window_size(int, u_int, u_int, u_int, u_int);
LIBOPENSSH_API void	 pty_setowner(struct passwd *, const char *);
LIBOPENSSH_API void	 disconnect_controlling_tty(void);
