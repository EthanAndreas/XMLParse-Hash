#include "../include/hash.h"
#include "../include/macro.h"

/**
 * @brief Initialize strut pair_t which contains
 * the size of the hash table and the size of the graph
 *
 * @param[in] size_init
 * @return pair_t*
 */
pair_t *init_pair(size_t size_init) {

    pair_t *pair = malloc(sizeof(pair_t));
    pair->count = 0;
    pair->size = size_init;

    return pair;
}

/**
 * @brief hash function by Dan Bernstein
 *
 *
 * @param str
 */
size_t h1(unsigned char *str) {

    size_t key = 5381;
    int c;

    while ((c = *str++))
        key = ((key << 5) + key) + c;

    return key;
}

/**
 * @brief Second hash function with other prime numbers
 *
 * @param[in] key
 * @return size_t
 */
size_t h2(size_t key) {

    size_t a = 1, b = 192473200937;
    size_t key2 = a * key + b;

    return key2;
}

/**
 * @brief Find the index of the bucket in the bucket array
which contains the given key or an empty block
 *
 * @param[in] str
 * @param[in] tab
 * @param[in] size
 * @return int
 */
size_t getBucketIndex(char *str, hash_t **tab, size_t size) {

    // hash with the first function
    size_t key = h1((unsigned char *)str);
    size_t ind = key % size;

    // if the index obtained aims an empty block or the same str
    // return the index
    if (tab[ind] == NULL || strcmp(tab[ind]->author, str) == 0)
        return ind;

    // hash with the seconde function
    size_t key2 = h2(ind);
    size_t ind2 = key2 % size;

    // hash the index obtained at each step until to obtain an empty
    // block or the same str
    while (tab[ind2] != NULL && strcmp(tab[ind2]->author, str) != 0) {

        key2 = h2(ind2);
        ind2 = key2 % size;
    }

    return ind2;
}

size_t getBucketIndex2(char *str, hash_t **tab, size_t size) {

    // hash with the first function
    size_t key = h1((unsigned char *)str);
    size_t ind = key % size;

    if (tab[ind] == NULL)
        exit(M_EOF);

    if (strcmp(tab[ind]->author, str) == 0)
        return ind;

    // hash with the seconde function
    size_t key2 = h2(ind);
    size_t ind2 = key2 % size;

    // hash the index obtained at each step until to obtain an empty
    // block or the same str
    while (tab[ind2] != NULL && strcmp(tab[ind2]->author, str) != 0) {

        key2 = h2(ind2);
        ind2 = key2 % size;
    }

    if (tab[ind2] == NULL)
        exit(M_EOF);

    return ind2;
}

/**
 * @brief Return 0 if the bucket associated to the key contained
 * an element, 1 otherwise
 *
 * @param[in] str
 * @param[in] tab
 * @param[in] size
 * @return size_t
 */
size_t contain_key(char *str, hash_t **tab, size_t size) {

    if (tab[getBucketIndex(str, tab, size) % size] != NULL)
        return 0;

    return 1;
}

/**
 * @brief Find the good index of the str with getBucketIndex and
 * put the author and the number of the article where the author was
 * found in the hash table
 *
 * @param[in] str
 * @param[in] tab
 * @param[in] pair
 * @param[in] line the line number in the file parsed (article's ID)
 * @return hash_t**
 */
hash_t **put(char *str, hash_t **tab, pair_t *pair, int line) {

    size_t ind = getBucketIndex(str, tab, pair->size);

    // if the index obtained aims an empty block, author name is
    // pushed in the hash table
    // also create the list of article with the size of the list and
    // the first article where the author was found
    if (tab[ind] == NULL) {

        char *copy_str = malloc(strlen(str) + 1);
        strcpy(copy_str, str);
        tab[ind] = malloc(sizeof(hash_t));
        tab[ind]->author = copy_str;

        int *article = malloc(2 * sizeof(int));
        int size_article = 1;
        article[0] = size_article;
        article[size_article] = line;
        tab[ind]->article = article;

        pair->count++;
    }

    // otherwise this is that we find the author on another
    // article the size of the list is extended and the number of
    // the article is written
    else {

        int size_article = (tab[ind]->article)[0];
        size_article++;
        tab[ind]->article = realloc(tab[ind]->article,
                                    (size_article + 1) * sizeof(int));
        (tab[ind]->article)[0] = size_article;
        (tab[ind]->article)[size_article] = line;
    }

    return tab;
}

/**
 * @brief Call when the factor of size is not even more respected.
 * It pushes author and his list of article in a new table with the
 * size doubled
 *
 * @param[in] str
 * @param[in] tab
 * @param[in] list
 * @param[in] pair
 * @return hash_t**
 */
hash_t **re_push(char *str, hash_t **tab, int *list, pair_t *pair) {

    size_t ind = getBucketIndex(str, tab, pair->size);

    if (tab[ind] == NULL) {

        tab[ind] = malloc(sizeof(hash_t));
        tab[ind]->author = str;
        tab[ind]->article = list;
    }

    return tab;
}

/**
 * @brief Check after the push of an element if the factor is even
 * respected otherwise the size of the hash table is multiplied by 2
 *
 * @param[in] tab
 * @param[in] pair
 * @return pair_t*
 */
hash_t **size_controller(hash_t **tab, pair_t *pair) {

    double factor = (double)pair->count / (double)pair->size;

    if (factor > 0.85) {

        size_t old_size = pair->size;
        pair->size = 2 * pair->size;

        // creation of the table with the doubled size
        hash_t **copy_tab = calloc(pair->size, sizeof(hash_t *));

        // push of all elements in this new tab
        for (size_t i = 0; i < old_size; i++) {

            if (tab[i] != NULL) {

                copy_tab = re_push(tab[i]->author, copy_tab,
                                   tab[i]->article, pair);
            }
        }

        // remove the old tab
        free_tab(tab, old_size);

        return copy_tab;
    }

    return tab;
}

/**
 * @brief Build the hash table with every author of the
 * input file and return the author's graph with their article's
 * list
 *
 * @param[in] input
 * @param[in] pair
 * @return author_t**
 */
hash_t **hash(char *input, pair_t *pair) {

    // creation of the hash table
    hash_t **hash_tab = calloc(pair->size, sizeof(hash_t *));

    // if the file sent is the full dblp file
    // display the bar's progression
    int ret = 0;
    if (strcmp(input, "assets/dblp_parsed.txt") == 0)
        ret = 1;

    FILE *file = opening_files(input, "r");

    // counter of lines read during the opening of the file
    int line_read = 1;

    // Loop which for every author collected puts in the hash
    // table

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

        // at each new line
        // update of the bar's progression
        if (c == '\n') {

            line_read++;
            if (ret == 1)
                progress("hash (author's graph)", line_read,
                         (int)LINE_NUMBER);
        }

        // if an article has an author
        // push in the hash table
        if (author != NULL) {

            size_of_author++;
            author = realloc(author, size_of_author * sizeof(char));
            author[size_of_author - 1] = '\0';

            hash_tab = put(author, hash_tab, pair, line_read);
            hash_tab = size_controller(hash_tab, pair);

            free(author);
        }

        // windows file contains '\r' before '\n'
        if (c == '\r')
            c = fgetc(file);

        c = fgetc(file);
    }

    fclose(file);

    return hash_tab;
}