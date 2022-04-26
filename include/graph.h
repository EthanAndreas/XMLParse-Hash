#ifndef GRAPH
#define GRAPH

#include "add_function.h"
#include "struct.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void parcours(hash_t **E, article_t **N, int s, size_t E_size,
//                size_t N_size);

int *calc_neighbors(int s, article_t **graph_article,
                    hash_t **hash_tab, int *neighbors);

int is_in(size_t size, int *tab, int elem);

int *dist_n(int n, char *author, article_t **graph_article,
            hash_t **hash_tab, pair_t *pair);

#endif