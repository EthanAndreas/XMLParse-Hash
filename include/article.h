#ifndef ARTICLE
#define ARTICLE

#include "include.h"
#include "struct.h"

article_t **hash_article(char *input, hash_t **hash_tab, pair_t *pair,
                         size_t *size);

#endif