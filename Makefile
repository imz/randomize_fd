all: randomize_fd_open.so

clean::
	rm -f randomize_fd_open.so

C_FLAGS ?= -Wall -Werror -O3

%.so: %.c Makefile
	$(CC) $(C_FLAGS) -shared -fPIC $< -ldl -o $@
