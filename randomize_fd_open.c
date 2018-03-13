#include "randomize_fd.h"
#include <dlfcn.h>
#include <assert.h>

#include <fcntl.h> /* open -- to check for conflicting types */

typedef int (*orig_open_f_type)(const char *pathname, int flags);

static orig_open_f_type orig_open = 0;
int open (const char *pathname, int flags, ...)
{
  if (!orig_open)
    orig_open = (orig_open_f_type) dlsym (RTLD_NEXT, "open");
  assert (orig_open);
  return randomize_fd (orig_open (pathname, flags));
}
