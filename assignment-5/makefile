CC=gcc
CFLAGS=-I. -g -w -pthread
LDFLAGS=-lm
DEPS=solve.h
OBJ=solver.o hashset.o btree.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

solve: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)
	dsymutil $@

.PHONY: clean
clean:
	rm -rf $(OBJ) solve solve.dSYM