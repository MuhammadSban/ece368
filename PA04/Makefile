CFLAGS = -g -O0 -std=c99 -Wall -Wshadow -Wvla -pedantic
GCC = gcc 
SRCS = readin.c writeout.c stack.c reroot.c pa3.c
OBJS = $(SRCS:%.c=%.o)

all: expr pa3

pa3: $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) -o pa3

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

test1: pa3
	./pa3 examples/3.po 3lr.pr 3rl.pr 3.rdim 3.opt
	diff 3lr.pr examples/3lr.pr
	diff 3rl.pr examples/3rl.pr
	diff 3.rdim examples/3.rdim
	diff 3.opt examples/3.opt

test2: pa3
	./pa3 examples/8.po 8lr.pr 8rl.pr 8.rdim 8.opt
	diff 8lr.pr examples/8lr.pr
	diff 8rl.pr examples/8rl.pr
	diff 8.rdim examples/8.rdim
	diff 8.opt examples/8.opt


testtime: pa3
	time ./pa3 examples/3.po 3lr.pr 3rl.pr 3.rdim 3.opt
	time ./pa3 examples/8.po 8lr.pr 8rl.pr 8.rdim 8.opt
	time ./pa3 examples/100.po 100lr.pr 100rl.pr 100.rdim 100.opt
	time ./pa3 examples/500.po 500lr.pr 500rl.pr 500.rdim 500.opt
	time ./pa3 examples/1K.po 1Klr.pr 1Krl.pr 1K.rdim 1K.opt


memory: pa3
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pa3 examples/8.po 8lr.pr 8rl.pr 8.rdim 8.opt
	
maxmem: pa3
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pa3 examples/1K.po 1Klr.pr 1Krl.pr 1K.rdim 1K.opt

clean:
	rm -f expr pa3 $(OBJS) output* *.bak *~

.PHONY: all testall memory clean
