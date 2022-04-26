#include "../include/author.h"

/**
 * @brief Collect only block plenty in the hash table
 *
 * @param[in] hash_tab
 * @param[in] pair
 * @return author_t**
 */
author_t **hash_author(hash_t **hash_tab, pair_t *pair) {

    // creation of the graph with author
    size_t size_of_graph = pair->count;
    author_t **graph = calloc(size_of_graph, sizeof(author_t *));

    // only plenty block in the hash table is taken
    int j = 0;
    for (size_t i = 0; i < pair->size; i++) {

        if (hash_tab[i] != NULL) {

            graph[j] = malloc(sizeof(author_t));
            graph[j]->author = hash_tab[i]->author;
            graph[j]->article = hash_tab[i]->article;
            j++;
        }
    }

    return graph;
}
