CFLAGS = -g -O0 -std=c99 -Wall -Wshadow -Wvla -pedantic
GCC = gcc 
SRCS = input.c wrout.c pa4.c evaluate.c
OBJS = $(SRCS:%.c=%.o)

all: expr pa4

pa4: $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) -o pa4

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

test1: pa4
	./pa4 -b examples/ops0.b tree0.b
	diff tree0.b examples/tree0.b

test2: pa4
	./pa4 -b examples/ops1.b tree1.b
	diff tree1.b examples/tree1.b

testinv: pa4
	./pa4 -e examples/invalidtree0.b 

meminv: pa4
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pa4 -e examples/invalidtree0.b

testtime: pa4
	time ./pa4 examples/3.po 3lr.pr 3rl.pr 3.rdim 3.opt
	time ./pa4 examples/8.po 8lr.pr 8rl.pr 8.rdim 8.opt
	time ./pa4 examples/100.po 100lr.pr 100rl.pr 100.rdim 100.opt
	time ./pa4 examples/500.po 500lr.pr 500rl.pr 500.rdim 500.opt
	time ./pa4 examples/1K.po 1Klr.pr 1Krl.pr 1K.rdim 1K.opt


memory: pa4
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pa4 -b examples/ops0.b tree0.b
	diff tree0.b examples/tree0.b

memory1: pa4
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pa4 -b examples/ops1.b tree1.b
	diff tree1.b examples/tree1.b

memory2: pa4
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pa4 -b examples/ops2.b tree2.b
	diff tree2.b examples/tree2.b

memory3: pa4
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pa4 -b examples/ops3.b tree3.b
	diff tree3.b examples/tree3.b


maxmem: pa4
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pa4 examples/1K.po 1Klr.pr 1Krl.pr 1K.rdim 1K.opt

clean:
	rm -f expr pa4 $(OBJS) output* *.bak *~

.PHONY: all testall memory clean
