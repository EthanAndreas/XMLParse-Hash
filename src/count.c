#include "../include/count.h"
#define buffer_size 2048

/**
 * @brief Take a file in input and
 * count the number of lines of the file
 *
 * @param[in] input
 * @return size_t
 */
size_t count_lines(char *input) {

    FILE *file = opening_files(input, "r");

    char buffer[buffer_size];

    size_t lines = 0;

    while (fgets(buffer, buffer_size, file) != NULL)
        lines++;

    fclose(file);
    return lines;
}

/**
 * @brief Take a file and a string and
 * count the number of lines of the file
 * that include the string
 *
 * @param[in] input
 * @param[in] str
 * @return size_t
 */
size_t count_lines_with_str(char *input, char *str) {

    FILE *file = opening_files(input, "r");

    char buffer[buffer_size];

    size_t lines = 0;

    while (fgets(buffer, buffer_size, file) != NULL) {

        if (strstr(buffer, str) != NULL)
            lines++;
    }

    fclose(file);
    return lines;
}

/**
 * @brief Take a file parsed in input
 * and count the number of author in this
 * file (-> the number of delimiter '|')
 *
 * @param[in] input
 * @return size_t
 */
size_t count_author(char *input) {

    FILE *file = opening_files(input, "r");

    char c = fgetc(file);

    size_t authors = 0;

    while (c != EOF) {

        if (c == '|')
            authors++;

        c = fgetc(file);
    }

    fclose(file);
    return authors;
}