#define _GNU_SOURCE
#include <dlfcn.h>
#include <assert.h>

#include <unistd.h>
#define RANDOMIZE_FD_STEP 6

static int dup_many_times_and_close (const int old_result, const unsigned int times)
{
  if (times == 0 || old_result < 0)
    return old_result;

  const int final_result = dup_many_times_and_close (dup (old_result), times - 1);
  if (close (old_result))
    ;
  return final_result;
}

static int randomize_fd (const int old_result)
{
  static char phase; /* the initial value is not very important */

  if (old_result < 0)
    return 0;

  return dup_many_times_and_close (old_result, RANDOMIZE_FD_STEP * (1 + (phase++ & 0x7)));
}

typedef int (*orig_open_f_type)(const char *pathname, int flags);

static orig_open_f_type orig_open = NULL;
int open (const char *pathname, int flags, ...)
{
  if (!orig_open)
    orig_open = (orig_open_f_type) dlsym (RTLD_NEXT, "open");
  assert (orig_open);
  return randomize_fd (orig_open (pathname, flags));
}
