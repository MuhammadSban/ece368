CFLAGS = -g -O0 -std=c99 -Wall -Wshadow -Wvla -pedantic 
GCC = gcc 
SRCS = sequence.c shell_array.c shell_list.c pa1.c
OBJS = $(SRCS:%.c=%.o)

all: expr pa1

expr: $(OBJS) 
	$(GCC) $(CFLAGS) $(OBJS) -o expr

pa1: $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) -o pa1

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

test1: expr
	./expr -1 examples/15.b 15sa.b
	diff 15sa.b examples/15sl.b

test2: expr
	./expr -1 examples/1K.b 1Ksa.b
	diff 1Ksa.b examples/1Ksl.b

test3: expr
	./expr -1 examples/1M.b 1Msa.b

testtime: expr
	time ./expr -1 examples/1K.b 1Ksa.b
	time ./expr -1 examples/10K.b 10Ksa.b
	time ./expr -1 examples/100K.b 100Ksa.b
	time ./expr -1 examples/1M.b 1Msa.b

memory: expr
	valgrind --leak-check=full --show-leak-kinds=all ./expr -1 examples/1K.b 1Ksa.b

memory2: expr
	valgrind --leak-check=full --show-leak-kinds=all ./expr -a examples/1K.b 1Ksa.b
	
memory3: expr
	valgrind --leak-check=full --show-leak-kinds=all ./expr -a examples/10K.b 10Ksa.b

memory4: expr
	valgrind --leak-check=full --show-leak-kinds=all ./expr -a examples/100K.b 100Ksa.b

memory5: expr
	valgrind --leak-check=full --show-leak-kinds=all ./expr -a examples/1M.b 1Msa.b

clean:
	rm -f expr pa1 $(OBJS) output* *.bak *~

.PHONY: all testall memory clean
