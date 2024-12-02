CC=gcc
CFLAGS=-I. -w -g
DEPS= shell.h
OBJ = shell.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
shell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)