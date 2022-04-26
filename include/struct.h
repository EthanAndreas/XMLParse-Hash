#ifndef STRUCT
#define STRUCT

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct hash_t {
    char *author;
    int *article;
} hash_t;

typedef struct pair_t {
    size_t count;
    size_t size;
} pair_t;

/**
 * @brief only use for the collect of
 * plenty block in the hash table
 *
 */
typedef struct author_t {
    char *author;
    int *article;
} author_t;

typedef struct article_t {
    int article;
    int *author; // number of author in the hash table
} article_t;

#endif