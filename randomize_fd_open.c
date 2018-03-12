#define _GNU_SOURCE

#include <fcntl.h> /* open -- to check for conflicting types */

#include <dlfcn.h>
#include <assert.h>
#include "randomize_fd.h"

typedef int (*orig_open_f_type)(const char *pathname, int flags);

static orig_open_f_type orig_open = 0;
int open (const char *pathname, int flags, ...)
{
  if (!orig_open)
    orig_open = (orig_open_f_type) dlsym (RTLD_NEXT, "open");
  assert (orig_open);
  return randomize_fd (orig_open (pathname, flags));
}
