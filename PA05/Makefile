CFLAGS = -g -O0 -std=c99 -Wall -Wshadow -Wvla -pedantic
GCC = gcc 
SRCS = readin.c solving.c queue.c out.c stack.c pa5.c
OBJS = $(SRCS:%.c=%.o)

all: expr pa5

pa5: $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) -o pa5

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

test1: pa5
	./pa5 examples/river.in0 river.in0.out1 river.in0.out2
	diff river.in0.out1 examples/river.in0.out1
	diff river.in0.out2 examples/river.in0.out2

test2: pa5
	./pa5 examples/river.in1 river.in1.out1 river.in1.out2
	diff river.in1.out1 examples/river.in1.out1
	diff river.in1.out2 examples/river.in1.out2

test3: pa5
	./pa5 examples/river.in2 river.in2.out1 river.in2.out2
	diff river.in2.out1 examples/river.in2.out1
	diff river.in2.out2 examples/river.in2.out2

test4: pa5
	./pa5 examples/river.in3 river.in3.out1 river.in3.out2
	diff river.in3.out1 examples/river.in3.out1
	diff river.in3.out2 examples/river.in3.out2


memory1: pa5
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./pa5 examples/river.in0 river.in0.out1 river.in0.out2
	diff river.in0.out1 examples/river.in0.out1
	diff river.in0.out2 examples/river.in0.out2

memory2: pa5
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./pa5 examples/river.in1 river.in1.out1 river.in1.out2
	diff river.in1.out1 examples/river.in1.out1
	diff river.in1.out2 examples/river.in1.out2

memory3: pa5
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./pa5 examples/river.in2 river.in2.out1 river.in2.out2
	diff river.in2.out1 examples/river.in2.out1
	diff river.in2.out2 examples/river.in2.out2

memory4: pa5
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./pa5 examples/river.in3 river.in3.out1 river.in3.out2
	diff river.in3.out1 examples/river.in3.out1
	diff river.in3.out2 examples/river.in3.out2

maxmem: pa5
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pa5 examples/1K.po 1Klr.pr 1Krl.pr 1K.rdim 1K.opt

clean:
	rm -f expr pa5 $(OBJS) output* *.bak *~

.PHONY: all testall memory clean
