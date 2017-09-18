/* test_node.c */

#include "node.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static char *STRING0 = "wake me up inside";
static char *STRING1 = "123";

int main(int argc, char *argv[]) {
    struct node *n0 = node_create(STRING0, NULL);
    assert(strcmp(n0->string, STRING0) == 0);
    assert(n0->number == 0);
    assert(n0->next == NULL);

    struct node *n1 = node_create(STRING1, n0);
    assert(strcmp(n1->string, STRING1) == 0);
    assert(n1->number == 123);
    assert(n1->next == n0);

    assert(node_compare_number(&n0, &n1) < 0);
    assert(node_compare_number(&n1, &n0) > 0);
    assert(node_compare_number(&n0, &n0) == 0);
    assert(node_compare_number(&n1, &n1) == 0);
    
    assert(node_compare_string(&n0, &n1) > 0);
    assert(node_compare_string(&n1, &n0) < 0);
    assert(node_compare_string(&n0, &n0) == 0);
    assert(node_compare_string(&n1, &n1) == 0);

    n1 = node_delete(n1, true);
    assert(n1 == NULL);

    n0 = node_create(STRING0, NULL);
    n1 = node_create(STRING1, n0);

    n0 = node_delete(n0, false);
    assert(n0 == NULL);
    n1 = node_delete(n1, false);
    assert(n1 == NULL);

    return 0;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
