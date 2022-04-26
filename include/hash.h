#ifndef HASH
#define HASH

#define LINE_NUMBER 8746621
#define M_EOF -255

#include "include.h"

pair_t *init_pair(size_t size_init);

size_t h1(unsigned char *str);
size_t h2(size_t ind);

size_t getBucketIndex(char *str, hash_t **tab, size_t size);

size_t getBucketIndex2(char *str, hash_t **tab, size_t size);

hash_t **put(char *str, hash_t **tab, pair_t *pair, int line);

hash_t **re_push(char *str, hash_t **tab, int *list, pair_t *pair);

size_t contain_key(char *str, hash_t **tab, size_t size);

hash_t **size_controller(hash_t **tab, pair_t *pair);

hash_t **hash(char *input, pair_t *pair);

#endif