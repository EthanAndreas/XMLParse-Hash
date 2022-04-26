#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "include.h"

// Constants
#define MAX_LINE 10000
#define SIZE_BEACON 7

// Test functions

/**
 * @brief Compare the number of line wanted from
 * the file to parse and the number of line of
 * the file parsed
 */
int test_lines(char *input, char *output) {

    parser_opti(input, output);

    size_t nbr_line = count_lines(output);
    size_t nbr_article = count_lines_with_str(input, "<title");

    if ((nbr_line - 1) != nbr_article)
        return 1;

    return 0;
}

/*
Launch test is a macro with only 1 argument ->
Two functions for the two files
*/

int test_lines_1(void) {

    return (test_lines("../assets/test_dblp_1.xml",
                       "../assets/test_dblp_parsed_1.txt"));
}

int test_lines_2(void) {

    return (test_lines("../assets/test_dblp_2.xml",
                       "../assets/test_dblp_parsed_2.txt"));
}

/**
 * @brief compare the expected content from the file
 * to parse and the content of the file parsed
 * (long parsing test on the small file)
 */
int test_parsing(void) {

    parser_opti("../assets/test_dblp_1.xml",
                "../assets/test_dblp_parsed_1.txt");

    FILE *file_parsed =
        opening_files("../assets/test_dblp_parsed_1.txt", "r");
    FILE *file_test =
        opening_files("../assets/test_result_1.txt", "r");

    char buffer1[BUFFER_SIZE], buffer2[BUFFER_SIZE];

    // check read progression of the second file
    char *ret;

    while (fgets(buffer1, BUFFER_SIZE, file_test) != NULL) {

        ret = fgets(buffer2, BUFFER_SIZE, file_parsed);

        if (ret == NULL)
            return 1;

        // remove of windows type file (presence of '\r' before '\n')
        remove_win_newline(buffer1);
        remove_win_newline(buffer2);

        if (strcmp(buffer1, buffer2) != 0)
            return 1;
    }

    return 0;
}

/**
 * @brief we take a random line
 * then we take the first author and
 * we compare if this author is include
 * in the good line of the file parsed
 * (faster parsing test on bigger file)
 *
 */
int test_parsing_2(void) {

    // generation of a random number between the first line and the
    // last line of the xml file
    srand(time(NULL));
    int random_line = rand() % (MAX_LINE + 1);

    FILE *file_to_parse =
        opening_files("../assets/test_dblp_2.xml", "r");

    FILE *file_parsed =
        opening_files("../assets/test_dblp_parsed_2.txt", "r");

    // counter add by one until the good line
    int nbr_line = 0;
    int nbr_article = 0;

    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];

    // check read progression of the first file
    char *ret1;

    // check read progression of the second file
    char *ret2;

    ret1 = fgets(buffer1, BUFFER_SIZE, file_to_parse);

    while (nbr_line < random_line) {

        char *ret0_start = strstr(buffer1, "<phdthesis"),
             *ret1_start = strstr(buffer1, "<article"),
             *ret2_start = strstr(buffer1, "<mastersthesis"),
             *ret3_start = strstr(buffer1, "<www"),
             *ret4_start = strstr(buffer1, "<book"),
             *ret5_start = strstr(buffer1, "<inproceedings"),
             *ret6_start = strstr(buffer1, "<proceedings"),
             *ret7_start = strstr(buffer1, "<incollection");

        if (ret0_start != NULL || ret1_start != NULL ||
            ret2_start != NULL || ret3_start != NULL ||
            ret4_start != NULL || ret5_start != NULL ||
            ret6_start != NULL || ret7_start != NULL) {

            // count the number of article already read
            nbr_article++;
            ret2 = fgets(buffer2, BUFFER_SIZE, file_parsed);
        }

        ret1 = fgets(buffer1, BUFFER_SIZE, file_to_parse);

        // counter which respect the random line generated
        nbr_line++;
    }

    // collect of the first author of the article
    while (strstr(buffer1, "<author") == NULL) {

        ret1 = fgets(buffer1, BUFFER_SIZE, file_to_parse);
    }

    int i = SIZE_BEACON;

    while (buffer1[i] != '>')
        i++;

    // jump after '>'
    i++;

    // check of the presence of the element in the two files at the
    // good line
    if (strstr(buffer2, buffer1) != NULL) {
        return 1;
    }

    (void)ret1;
    (void)ret2;

    return 0;
}

/**
 * @brief hash a small file and check that every element is in the
 * graph return

 */
int test_hash(char *input) {

    pair_t *pair = init_pair(1);
    hash_t **hash_tab = hash(input, pair);
    author_t **graph_author = hash_author(hash_tab, pair);

    FILE *file = opening_files(input, "r");

    char c = fgetc(file);

    while (c != EOF) {

        // for each author in the file, check up of hash and
        // hash_author function
        char *author = NULL;
        size_t size_of_author = 0;

        while (c != '|' && c != '\n' && c != '\r' && c != '\0') {

            size_of_author++;
            author = realloc(author, size_of_author * sizeof(char));
            author[size_of_author - 1] = c;

            c = fgetc(file);
        }

        if (author != NULL) {

            size_of_author++;
            author = realloc(author, size_of_author * sizeof(char));
            author[size_of_author - 1] = '\0';

            // check of the presence of the element in the hash table
            // and check of the working of contain_key function
            if (contain_key(author, hash_tab, pair->size) == 1)
                return 1;

            // check of the presence of the element in the graph table
            int error = 1;

            for (int i = 0; i < pair->count; i++) {

                if (strcmp(author, graph_author[i]->author) == 0)
                    error = 0;
            }

            // return 1 if the element is not found in the graph table
            if (error == 1)
                return 1;

            free(author);
        }

        // windows file contains '\r' before '\n'
        if (c == '\r')
            c = fgetc(file);

        c = fgetc(file);
    }

    // remove allocated memory
    free_tab(hash_tab, pair->size);
    free_author(graph_author, pair->count);
    free(pair);

    fclose(file);
    return 0;
}

/*
Launch test is a macro with only 1 argument ->
Two functions for the two files
*/

int test_hash_1(void) {

    return (test_hash("../assets/test_result_1.txt"));
}

int test_hash_2(void) {

    return (test_hash("../assets/test_result_2.txt"));
}

int main(void) {

    fprintf(stdout, GREY UNDERLINE "\nLaunch of tests\n\n" RESET);

    LAUNCH_TEST(test_lines_1, "1.1");
    LAUNCH_TEST(test_lines_2, "1.2");
    fprintf(stdout, "\n");

    LAUNCH_TEST(test_parsing, "2.1");
    fprintf(stdout, "\n");

    for (int i = 1; i <= 9; i++) {

        char number[10];
        sprintf(number, "3.%d", i);
        LAUNCH_TEST(test_parsing_2, number);
    }
    fprintf(stdout, "\n");

    LAUNCH_TEST(test_hash_1, "4.1");
    LAUNCH_TEST(test_hash_1, "4.2");
    printf("\n");

    fprintf(stdout, GREY UNDERLINE "End of tests\n\n" RESET);
    return 0;
}