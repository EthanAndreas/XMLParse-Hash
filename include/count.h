#ifndef COUNT
#define COUNT

#include "add_function.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_lines(char *input);

size_t count_lines_with_str(char *input, char *str);

size_t count_author(char *input);

#endif