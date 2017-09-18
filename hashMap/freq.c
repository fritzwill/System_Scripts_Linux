/* freq.c */

#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Globals */

char * PROGRAM_NAME = NULL;
DumpMode mode = VALUE_KEY;
double load_factor = DEFAULT_LOAD_FACTOR;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s\n", PROGRAM_NAME);
    fprintf(stderr, "    -f FORMAT        Output format (KEY, KEY_VALUE, VALUE, VALUE_KEY)\n");
    fprintf(stderr, "    -l LOAD_FACTOR   Load factor for hash table\n");
    exit(status);
}

void freq_stream(FILE *stream, double load_factor, DumpMode mode) {
    char word[BUFSIZ];
    Map * m = map_create(DEFAULT_CAPACITY, load_factor);
    Entry * ent;
    while(fscanf(stream, "%s\n", word) != EOF){
        ent = map_search(m, word);
        if (ent == NULL){
            map_insert(m, word, (Value)(int64_t)1, NUMBER);
        }
        else {
            map_insert(m, word, (Value)(int64_t)(ent->value.number + 1), NUMBER);
        }
    }
    map_dump(m, stdout, mode);
    map_delete(m);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* Parse command line arguments */
    
    int argind = 1;
    while (argind < argc && argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-'){
        char * arg = argv[argind++];
        switch(arg[1]){
            case 'h':
                usage(0);
                break;
            case 'f':
                if (strcmp(argv[argind], "VALUE") == 0) mode = VALUE;
                else if (strcmp(argv[argind], "KEY") == 0) mode = KEY;
                else if (strcmp(argv[argind],"KEY_VALUE")==0)mode=KEY_VALUE;
                else if (strcmp(argv[argind],"VALUE_KEY")==0)mode=VALUE_KEY;
                else mode = KEY;
                argind++;
                break;
            case 'l':
                load_factor = atof(argv[argind]);
                argind++;
                break;
            default:
                usage(1);
        }
    }
    freq_stream(stdin, load_factor, mode);
           
    /* Compute frequencies of data from stdin */
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
