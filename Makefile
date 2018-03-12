all: randomize_fd_open.so randomize_fd_socket.so

.PHONY: all clean

clean::
	rm -f randomize_fd_open.so randomize_fd_socket.so

CFLAGS ?= -fPIC -Wall -Werror -O3

randomize_fd_%.so: randomize_fd_%.c randomize_fd.o
	$(CC) $(CFLAGS) -shared $^ -ldl -o $@

clean::
	rm -f randomize_fd.o
