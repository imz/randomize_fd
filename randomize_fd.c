#include "randomize_fd.h"

#include <unistd.h> /* dup */
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

int randomize_fd (const int old_result)
{
  static char phase; /* the initial value is not very important */

  if (old_result < 0)
    return 0;

  return dup_many_times_and_close (old_result, RANDOMIZE_FD_STEP * (1 + (phase++ & 0x7)));
}
