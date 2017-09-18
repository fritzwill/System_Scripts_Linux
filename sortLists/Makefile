CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	lsort

all:		$(TARGETS)

# Add rules for liblist.a, test_node, test_list, lsort, and any intermediate objects
node.o: node.c list.h node.h
	$(CC) $(CFLAGS) -o node.o -c node.c

list.o: list.c node.h list.h
	$(CC) $(CFLAGS) -o list.o -c list.c

test_node.o: test_node.c list.h node.h
	$(CC) $(CFLAGS) -o test_node.o -c test_node.c

test_list.o: node.h list.h test_list.c
	$(CC) $(CFLAGS) -o test_list.o -c test_list.c

lsort.o: lsort.c list.h node.h
	$(CC) $(CFLAGS) -o lsort.o -c lsort.c

liblist.a: node.o list.o
	$(AR) $(ARFLAGS) liblist.a node.o list.o

lsort: liblist.a lsort.o
	$(LD) $(LDFLAGS) -o lsort lsort.o -llist

test_node: liblist.a test_node.o
	$(LD) $(LDFLAGS) -o test_node test_node.o -llist

test_list: liblist.a test_list.o
	$(LD) $(LDFLAGS) -o test_list test_list.o -llist

test:		test-node test-list test-lsort

test-node:	test_node
	@echo Testing node...
	@[ `valgrind --leak-check=full ./test_node 2>&1 | tee test_node.log | grep ERROR | awk '{print $$4}'` = 0 ] || cat test_node.log

test-list:	test_list
	@echo Testing list...
	@[ `valgrind --leak-check=full ./test_list 2>&1 | tee test_list.log | grep ERROR | awk '{print $$4}'` = 0 ] || cat test_list.log

test-lsort:	lsort test_lsort.sh
	@echo Testing lsort...
	@./test_lsort.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) test_node test_list *.a *.o *.log *.input

.PHONY:		all test test-node test-list test-lsort clean
