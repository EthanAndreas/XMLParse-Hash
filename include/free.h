#ifndef FREE
#define FREE

#include "struct.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void free_tab(hash_t **tab, size_t size);

void free_author(author_t **tab, size_t size);

void free_article(article_t **tab, size_t size);

#endif