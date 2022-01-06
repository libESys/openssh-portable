#ifndef _PAL_DOEXEC_H
#define _PAL_DOEXEC_H

#include "libopenssh_defs.h"

#include "session.h"

LIBOPENSSH_API int	do_exec_pty(struct ssh *, Session *, const char *);
LIBOPENSSH_API int	do_exec_no_pty(struct ssh *, Session *, const char *);
#endif /* _PAL_DOEXEC_H */