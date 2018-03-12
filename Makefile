all: randomize_fd_open.so

%.so: %.c
	gcc -shared -fPIC $< -o $@
