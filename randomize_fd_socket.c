#include "randomize_fd.h"
#include <dlfcn.h>
#include <assert.h>

#include <sys/socket.h> /* socket -- to check for conflicting types */

typedef int (*orig_socket_f_type)(int domain, int type, int protocol);

static orig_socket_f_type orig_socket = 0;
int socket (int domain, int type, int protocol)
{
  if (!orig_socket)
    orig_socket = (orig_socket_f_type) dlsym (RTLD_NEXT, "socket");
  assert (orig_socket);
  return randomize_fd (orig_socket (domain, type, protocol));
}
