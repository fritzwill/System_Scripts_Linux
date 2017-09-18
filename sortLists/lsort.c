/* lsort.c */

#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s\n", PROGRAM_NAME);
    fprintf(stderr, "  -n   Numerical sort\n");
    fprintf(stderr, "  -q   Quick sort\n");
    exit(status);
}

void lsort(FILE *stream, bool numeric, bool quicksort) {
    // creates list
    struct list * myList = list_create();
    if (stream != NULL){
        char line[BUFSIZ];
        while (fgets(line, BUFSIZ, stream)){
            list_push_front(myList, line);
        }
    }
    if (quicksort){
        if (numeric) list_qsort(myList, &node_compare_number);
        else list_qsort(myList, &node_compare_string);
    }
    else {
        if (numeric) list_msort(myList, &node_compare_number);
        else list_msort(myList, &node_compare_string);
    }
    // prints the list
    struct node * ptr = myList->head;
    while (ptr != NULL){
        printf("%s", ptr->string);
        ptr = ptr->next;
    }
    list_delete(myList);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    bool quicksort = false;
    bool numeric = false;
    /* Parse command line arguments */
    int argind = 1;
    while (argind < argc && argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-'){
        char *arg = argv[argind++];
        switch(arg[1]){
            case 'h':
                usage(0);
                break;
            case 'n':
                numeric = true;
                break;
            case 'q':
                quicksort = true;
                break;
            default:
                usage(1);
                break;
        }
    }
    /* Sort using list */
    lsort(stdin, numeric, quicksort);
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
