#ifndef OPTION
#define OPTION

#include "include.h"

typedef struct usage_t {
    int parsing;
    int hash;
    int time;
    int author_counting;
    int line_counting;
    char *word;
    char *author;
    char *distance;
    char *input;
    char *output;
} usage_t;

void init_usage(usage_t *usage);

int option(int argc, char **argv, usage_t *usage);

#endif