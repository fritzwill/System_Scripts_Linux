/* test_fnv.c */

#include "map.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *	key;
    uint64_t	hash;
} Pair;

static Pair TESTS[] = {
    {"wake me up inside", 9048950985493973590UL},
    {"123", 5003431119771845851UL},
    {"deadool", 9030128678874230203UL},
    {"wolverine", 9749463647854691528UL},
    {NULL, 0},
};

int main(int argc, char *argv[]) {
    for (size_t i = 0; TESTS[i].key; i++) {
    	uint64_t hash = fnv_hash(TESTS[i].key, strlen(TESTS[i].key));
    	printf("%20s = 0x%lx\n", TESTS[i].key, hash);
    	assert(TESTS[i].hash == hash);
    }
    return 0;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
