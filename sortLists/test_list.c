/* test_list.c */

#include "list.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static char *HEROES[] = {
    "spider-man",
    "deadpool",
    "batman",
    "wolverine",
    "superman",
    NULL
};

int main(int argc, char *argv[]) {
    struct list *l = list_create();
    assert(l->head == NULL);
    assert(l->tail == NULL);
    assert(l->size == 0);

    puts("Push front...");
    for (size_t i = 0; HEROES[i]; i++) {
    	list_push_front(l, HEROES[i]);
        assert(l->size == i + 1);
        assert(strcmp(l->head->string, HEROES[i]) == 0);
    }
    list_dump(l, stdout);
    
    struct node *n = l->head;
    for (int i = sizeof(HEROES)/sizeof(char *) - 2; i >= 0; i--, n = n->next) {
    	assert(strcmp(n->string, HEROES[i]) == 0);
    	if (n->next == NULL)
            assert(l->tail == n);
    }
    
    l = list_delete(l);
    assert(l == NULL);

    l = list_create();
    assert(l->head == NULL);
    assert(l->tail == NULL);
    assert(l->size == 0);
    
    puts("Push back...");
    for (size_t i = 0; HEROES[i]; i++) {
    	list_push_back(l, HEROES[i]);
        assert(l->size == i + 1);
        assert(strcmp(l->tail->string, HEROES[i]) == 0);
    }
    list_dump(l, stdout);
    
    n = l->head;
    for (size_t i = 0; HEROES[i]; i++, n = n->next) {
    	assert(strcmp(n->string, HEROES[i]) == 0);
    	if (n->next == NULL)
            assert(l->tail == n);
    }

    puts("QSort...");
    list_qsort(l, node_compare_string);
    list_dump(l, stdout);
    for (n = l->head; n && n->next; n = n->next) {
        assert(node_compare_string(&n, &n->next) < 0);
    }
    assert(l->tail == n);
    
    puts("Reversing...");
    list_reverse(l);
    list_dump(l, stdout);
    for (n = l->head; n && n->next; n = n->next) {
        assert(node_compare_string(&n, &n->next) > 0);
    }
    assert(l->tail == n);
    
    puts("MSort...");
    list_msort(l, node_compare_string);
    list_dump(l, stdout);
    for (n = l->head; n && n->next; n = n->next) {
        assert(node_compare_string(&n, &n->next) < 0);
    }
    assert(l->tail == n);

    l = list_delete(l);
    assert(l == NULL);

    return 0;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
