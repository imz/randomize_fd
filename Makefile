all: randomize_fd_open.so

clean::
	rm -f randomize_fd_open.so

CFLAGS ?= -fPIC -Wall -Werror -O3

randomize_fd_%.so: randomize_fd_%.c randomize_fd.o
	$(CC) $(CFLAGS) -shared $^ -ldl -o $@

clean::
	rm -f randomize_fd.o
