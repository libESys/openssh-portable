#include "openssh/putenv.h"

#include <stdlib.h>

LIBOPENSSH_API int
libopenssh_putenv(const char *env_var)
{
    return _putenv(env_var);
}