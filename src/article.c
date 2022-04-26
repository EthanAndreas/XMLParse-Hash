#include "../include/article.h"

article_t **hash_article(char *input, hash_t **hash_tab, pair_t *pair,
                         size_t *size) {

    FILE *file = opening_files(input, "r");

    *size = 1;
    article_t **tab = calloc((*size), sizeof(article_t *));

    // if the file sent is the full dblp file
    // display the bar's progression
    int ret = 0;
    if (strcmp(input, "assets/dblp_parsed.txt") == 0)
        ret = 1;

    // counter of lines read during the opening of the file
    int line_read = 1;

    // counter of author of each article
    int author_read = 1;

    // Loop which for every author collected puts in the hash
    // table

    tab[*size - 1] = malloc(sizeof(article_t));
    tab[*size - 1]->article = line_read;
    tab[*size - 1]->author = malloc(sizeof(int));
    (tab[*size - 1]->author)[0] = author_read;

    char c = fgetc(file);

    while (c != EOF) {

        // retrieve the author's name between separator '|'
        char *author = NULL;
        size_t size_of_author = 0;

        while (c != '|' && c != '\n' && c != '\r' && c != '\0') {

            size_of_author++;
            author = realloc(author, size_of_author * sizeof(char));
            author[size_of_author - 1] = c;

            c = fgetc(file);
        }

        // if an article has an author
        // push in the article graph
        if (author != NULL) {

            size_of_author++;
            author = realloc(author, size_of_author * sizeof(char));
            author[size_of_author - 1] = '\0';

            (tab[*size - 1]->author)[0]++;
            author_read = (tab[*size - 1]->author)[0];

            // author_read + 1 for the first element which represents
            // the size of the list
            tab[*size - 1]->author =
                realloc(tab[*size - 1]->author,
                        (author_read + 1) * sizeof(int));

            size_t ind =
                getBucketIndex2(author, hash_tab, pair->size);

            (tab[*size - 1]->author)[author_read] = ind;

            free(author);
        }

        // at each new line
        // update of the bar's progression
        if (c == '\n') {

            line_read++;
            (*size)++;
            author_read = 0;

            tab = realloc(tab, (*size) * sizeof(article_t *));

            tab[*size - 1] = malloc(sizeof(article_t));
            tab[*size - 1]->article = line_read;
            tab[*size - 1]->author = malloc(sizeof(int));
            (tab[*size - 1]->author)[0] = author_read;

            if (ret == 1)
                progress("hash (article's graph)", line_read,
                         (int)LINE_NUMBER);
        }

        // windows file contains '\r' before '\n'
        if (c == '\r')
            c = fgetc(file);

        c = fgetc(file);
    }

    fclose(file);

    return tab;
}