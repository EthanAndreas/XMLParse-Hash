#include "../include/parser.h"

// Definition of xml file's beacons

static const char begin_these[] = "<phdthesis",
                  end_these[] = "</phdthesis>";

static const char begin_master[] = "<mastersthesis",
                  end_master[] = "</mastersthesis>";

static const char begin_article[] = "<article",
                  end_article[] = "</article>";

static const char begin_web[] = "<www", end_web[] = "</www>";

static const char begin_book[] = "<book", end_book[] = "</book>";

static const char begin_inpro[] = "<inproceedings",
                  end_inpro[] = "</inproceedings>";

static const char begin_proceed[] = "<proceedings",
                  end_proceed[] = "</proceedings>";

static const char begin_inco[] = "<incollection",
                  end_inco[] = "</incollection>";

static const char begin_author[] = "<author",
                  end_author[] = "</author>";

/*
one article / thesis / masterthesis per line
all the author of the article on the same line
if the article has no author : empty line
*/

/**
 * @brief The function take in input a file to parse
 * and a file empty where the file parsed is write
 *
 * @param[in] input : the file to parse
 * @param[in] output : the file to write the result
 * @return int
 */
int parser_opti(char *input, char *output) {

    int ret = 0;
    double line_read = 0;

    if (strcmp(output, "assets/dblp_parsed.txt") == 0)
        ret = 1;
    else {
        (void)line_read;
    }

    FILE *file_to_parse = opening_files(input, "r");
    FILE *file_parsed = opening_files(output, "w");

    // buffer creation
    char buffer[BUFFER_SIZE];

    // detector of begin's and end's beacons
    char *ret0_start, *ret0_end, *ret1_start, *ret1_end, *ret2_start,
        *ret2_end, *ret3_start, *ret3_end, *ret4_start, *ret4_end,
        *ret5_start, *ret5_end, *ret6_start, *ret6_end, *ret7_start,
        *ret7_end, *ret_author_start, *ret_author_end;

    // taille de la balise author
    size_t size_author = strlen(begin_author);

    // integer indicating if a "begin_beacon" is in the buffer
    int ret_able = 0;
    // integer indicating if a "begin_author" is in the buffer
    int ret2_able = 0;

    if (ret == 1) {
        progress("parse", line_read, (double)LINE_XML_NUMBER);
    }

    // browse the entire file to parse
    while (fgets(buffer, BUFFER_SIZE, file_to_parse) != NULL) {

        // Detection of the end of beacons
        ret0_end = strstr(buffer, end_these);
        ret1_end = strstr(buffer, end_master);
        ret2_end = strstr(buffer, end_article);
        ret3_end = strstr(buffer, end_web);
        ret4_end = strstr(buffer, end_book);
        ret5_end = strstr(buffer, end_inpro);
        ret6_end = strstr(buffer, end_proceed);
        ret7_end = strstr(buffer, end_inco);

        if (ret0_end != NULL || ret1_end != NULL ||
            ret2_end != NULL || ret3_end != NULL ||
            ret4_end != NULL || ret5_end != NULL ||
            ret6_end != NULL || ret7_end != NULL) {

            ret_able = 0;
            fprintf(file_parsed, "%s", "\n");
        }

        // Detection of the beginnig of beacons
        ret0_start = strstr(buffer, begin_these);
        ret1_start = strstr(buffer, begin_master);
        ret2_start = strstr(buffer, begin_article);
        ret3_start = strstr(buffer, begin_web);
        ret4_start = strstr(buffer, begin_book);
        ret5_start = strstr(buffer, begin_inpro);
        ret6_start = strstr(buffer, begin_proceed);
        ret7_start = strstr(buffer, begin_inco);

        if (ret0_start != NULL || ret1_start != NULL ||
            ret2_start != NULL || ret3_start != NULL ||
            ret4_start != NULL || ret5_start != NULL ||
            ret6_start != NULL || ret7_start != NULL)

            ret_able = 1;

        // if there is a new article, get the author
        if (ret_able == 1) {

            ret_author_start = strstr(buffer, begin_author);

            if (ret_author_start != NULL) {

                ret2_able = 1;
            }

            if (ret2_able == 1) {

                int i = size_author;

                while (buffer[i] != '>')
                    i++;

                // we remove '>'
                i++;

                while (buffer[i] != '<') {

                    fprintf(file_parsed, "%c", buffer[i]);
                    i++;
                }
            }

            // check if the author ends
            ret_author_end = strstr(buffer, end_author);

            if (ret_author_end != NULL) {

                ret2_able = 0;

                // '|' separator betwin co-author
                fprintf(file_parsed, "%s", "|");
            }
        }

        if (ret == 1) {
            line_read++;
            progress("parse", line_read, (double)LINE_XML_NUMBER);
        }
    }

    fclose(file_to_parse);
    fclose(file_parsed);
    return 0;
}
