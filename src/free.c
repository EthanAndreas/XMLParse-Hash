#include "../include/free.h"

/**
 * @brief Free all the element push in the hash table
 *
 * @param[in] tab
 * @param[in] size
 */
void free_tab(hash_t **tab, size_t size) {

    if (tab == NULL)
        return;

    for (size_t i = 0; i < size; i++) {

        if (tab[i] != NULL) {

            if (tab[i]->author != NULL)
                free(tab[i]->author);

            if (tab[i]->article != NULL)
                free(tab[i]->article);

            free(tab[i]);
        }
    }

    free(tab);
}

/**
 * @brief Free all the element of author's graph
 *
 * @param[in] tab
 * @param[in] size
 */
void free_author(author_t **tab, size_t size) {

    if (tab == NULL)
        return;

    for (size_t i = 0; i < size; i++) {

        if (tab[i] != NULL) {

            if (tab[i]->author != NULL)
                free(tab[i]->author);

            if (tab[i]->article != NULL)
                free(tab[i]->article);

            free(tab[i]);
        }
    }

    free(tab);
}

/**
 * @brief Free all the element of article's graph
 *
 * @param[in] tab
 * @param[in] size
 */
void free_article(article_t **tab, size_t size) {

    if (tab == NULL)
        return;

    for (size_t i = 0; i < size; i++) {

        if (tab[i] != NULL) {

            if (tab[i]->author != NULL)
                free(tab[i]->author);

            free(tab[i]);
        }
    }

    free(tab);
}