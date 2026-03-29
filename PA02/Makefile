CFLAGS = -g -O0 -std=c99 -Wall -Wshadow -Wvla -pedantic
GCC = gcc 
SRCS = readin.c writeout.c stack.c pa2.c
OBJS = $(SRCS:%.c=%.o)

all: expr pa2

pa2: $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) -o pa2

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

test1: pa2
	./pa2 examples/3.pr 3.po 3.dim 3.pck
	diff 3.po examples/3.po
	diff 3.dim examples/3.dim
	diff 3.pck examples/3.pck

test2: pa2
	./pa2 examples/8.pr 8.po 8.dim 8.pck
	diff 8.po examples/8.po
	diff 8.dim examples/8.dim
	diff 8.pck examples/8.pck


testtime: pa2
	time ./pa2 examples/3.pr examples/3.po examples/3.dim examples/3.pck
	time ./pa2 examples/8.pr examples/8.po examples/8.dim examples/8.pck
	time ./pa2 examples/100.pr examples/100.po examples/100.dim examples/100.pck
	time ./pa2 examples/500.pr examples/500.po examples/500.dim examples/500.pck
	time ./pa2 examples/1K.pr examples/1K.po examples/1K.dim examples/1K.pck


memory: pa2
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pa2 examples/100.pr 100.po 100.dim 100.pck
	
maxmem: pa2
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pa2 examples/1K.pr 1K.po 1K.dim 1K.pck

clean:
	rm -f expr pa2 $(OBJS) output* *.bak *~

.PHONY: all testall memory clean
