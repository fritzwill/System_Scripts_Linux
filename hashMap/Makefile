CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	freq

all:		$(TARGETS)

#-------------------------------------------------------------------------------

# Add rules for test_entry, test_fnv, test_map, freq, measure
freq.o: freq.c
	@echo Compiling freq.o...
	@$(CC) $(CFLAGS) -o freq.o -c freq.c

entry.o: entry.c
	@echo Compiling entry.o...
	@$(CC) $(CFLAGS) -o entry.o -c entry.c

fnv.o: fnv.c
	@echo Compiling fnv.o...
	@$(CC) $(CFLAGS) -o fnv.o -c fnv.c

map.o: map.c
	@echo Compiling map.o...
	@$(CC) $(CFLAGS) -o map.o -c map.c

libmap.a: entry.o fnv.o map.o
	@echo Linking libmap.a...
	@$(AR) $(ARFLAGS) libmap.a entry.o fnv.o map.o

test_entry.o: test_entry.c
	@echo Compiling test_entry.o...
	@$(CC) $(CFLAGS) -o test_entry.o -c test_entry.c

test_entry: test_entry.o libmap.a
	@echo Linking test_entry...
	@$(LD) $(LDFLAGS) -o test_entry test_entry.o libmap.a

test_fnv.o: test_fnv.c
	@echo Compiling test_fnv.o...
	@$(CC) $(CFLAGS) -o test_fnv.o -c test_fnv.c

test_fnv: test_fnv.o libmap.a
	@echo Linking test_fnv...
	@$(LD) $(LDFLAGS) -o test_fnv test_fnv.o libmap.a

test_map.o: test_map.c
	@echo Compiling test_map.o...
	@$(CC) $(CFLAGS) -o test_map.o -c test_map.c

test_map: test_map.o libmap.a
	@echo Linking test_map...
	@$(LD) $(LDFLAGS) -o test_map test_map.o libmap.a

measure: measure.c
	@echo Compiling measure...
	@$(CC) $(CFLAGS) -o measure measure.c

freq: freq.o libmap.a
	@echo Linking freq...
	@$(LD) $(LDFLAGS) -o freq freq.o libmap.a

#-------------------------------------------------------------------------------

test:		test-entry test-fnv test-map test-freq

test-entry:	test_entry
	@echo Testing entry...
	@[ `valgrind --leak-check=full ./test_entry 2>&1 | tee test_entry.log | grep ERROR | awk '{print $$4}'` = 0 ] && ! grep -q 'failed' test_entry.log || cat test_entry.log

test-fnv:	test_fnv
	@echo Testing fnv...
	@[ `valgrind --leak-check=full ./test_fnv 2>&1 | tee test_fnv.log | grep ERROR | awk '{print $$4}'` = 0 ] && ! grep -q 'failed' test_fnv.log || cat test_fnv.log

test-map:	test_map
	@echo "Testing map..."
	@[ `valgrind --leak-check=full ./test_map 2>&1 | tee test_map.log | grep ERROR | awk '{print $$4}'` = 0 ] && ! grep -q 'failed' test_map.log || cat test_map.log

test-freq:	test_freq.sh freq
	@echo "Testing freq..."
	@./test_freq.sh 2>&1 | tee test_freq.log
	@[ `valgrind --leak-check=full ./freq < map.h 2>&1 | tee test_freq.log | grep ERROR | awk '{print $$4}'` = 0 ] && ! grep -q 'failed' test_freq.log || cat test_freq.log

benchmark:	measure freq benchmark.py
	@echo Benchmarking
	@./benchmark.py

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) test_entry test_fnv test_map measure *.a *.o *.log *.input

.PHONY:		all test benchmark clean
