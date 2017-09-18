/* test_entry.c */

#include "map.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static char *KEY0 = "123";
static char *KEY1 = "wake me up inside";

int main(int argc, char *argv[]) {
    puts("Test entry creation...");
    Entry *e0 = entry_create(KEY0, (Value)strtol(KEY0, NULL, 10), NULL, NUMBER);
    assert(strcmp(e0->key, KEY0) == 0);
    assert(e0->value.number == strtol(KEY0, NULL, 10));
    assert(e0->next == NULL);
    assert(e0->type == NUMBER);

    Entry *e1 = entry_create(KEY1, (Value)KEY1, e0, STRING);
    assert(strcmp(e1->key, KEY1) == 0);
    assert(strcmp(e1->value.string, KEY1) == 0);
    assert(e1->next == e0);
    assert(e1->type == STRING);
    
    puts("Test entry update...");
    entry_update(e0, (Value)KEY1, STRING);
    assert(strcmp(e0->value.string, KEY1) == 0);
    entry_update(e1, (Value)strtol(KEY0, NULL, 10), NUMBER);
    assert(e1->value.number == strtol(KEY0, NULL, 10));

    puts("Test entry deletion...");
    e1 = entry_delete(e1, true);
    assert(e1 == NULL);

    e0 = entry_create(KEY0, (Value)strtol(KEY0, NULL, 10), NULL, NUMBER);
    e1 = entry_create(KEY1, (Value)KEY1, e0, STRING);

    e0 = entry_delete(e0, false);
    assert(e0 == NULL);

    e1 = entry_delete(e1, false);
    assert(e1 == NULL);

    return 0;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
