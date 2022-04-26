#include "../include/include.h"

int main(int argc, char **argv) {

    // Signal

    if (signal(SIGINT, handler_c) == SIG_ERR) {

        fprintf(stderr,
                RED "Error on system call : signal" RESET "\n");
        exit(1);
    }

    // Context

    clock_t begin, end;

    usage_t *usage = malloc(sizeof(usage_t));
    init_usage(usage);

    // Check options

    if (option(argc, argv, usage) == 1)
        return 1;

    // Launch of programms

    if (usage->parsing == 1) {

        begin = clock();
        parser_opti(usage->input, usage->output);
        end = clock();

        if (usage->time == 1)
            show_time(begin, end);
    }

    if (usage->hash == 1) {

        int display = 0;
        if (strstr(usage->output, "parsed") == NULL) {

            display = 1;
            fprintf(stdout,
                    RED "If you want the hash table of the file, "
                        "please send the file parsed\n" RESET);
            free(usage);
            return 1;
        }

        begin = clock();

        pair_t *pair = init_pair(2000);
        hash_t **hash_tab = hash(usage->output, pair);

        if (display == 1)
            fprintf(stdout, "\n");

        size_t *size_article = malloc(sizeof(size_t));
        article_t **graph_article =
            hash_article(usage->output, hash_tab, pair, size_article);

        end = clock();

        (void)graph_article;

        if (usage->author_counting == 1)
            fprintf(stdout,
                    RESET "The file parsed has " MAGENTA "%li" RESET
                          " unique's authors\n",
                    pair->count);

        if (usage->time == 1)
            show_time(begin, end);

        fprintf(stdout,
                RESET "Free of author's graph and article's graph\n");

        // remove the hash table
        free_tab(hash_tab, pair->size);
        free(pair);

        // remove the article's graph
        free_article(graph_article, *size_article);
        free(size_article);
    }

    if (usage->author_counting == 1 && usage->hash == 0) {

        if (strstr(usage->output, "parsed") == NULL) {

            fprintf(stdout,
                    RED "If you want the number of authors, "
                        "please send the file parsed\n" RESET);
            free(usage);
            return 1;
        }

        size_t authors = count_author(usage->output);
        fprintf(stdout,
                RESET "The file parsed has " MAGENTA "%li" RESET
                      " authors with duplicates\n",
                authors);
    }

    if (usage->line_counting == 1) {

        if (strstr(usage->output, "parsed") == NULL) {

            fprintf(stdout,
                    RED "If you want the number of articles, "
                        "please send the file parsed\n" RESET);
            free(usage);
            return 1;
        }

        size_t lines = count_lines(usage->output);

        fprintf(stdout,
                RESET "The file parsed has " MAGENTA "%li" RESET
                      " articles\n",
                lines);
    }

    if (usage->author != NULL && usage->distance == NULL) {

        if (strstr(usage->output, "parsed") == NULL) {

            fprintf(stdout, RED
                    "If you want the list of article of an author, "
                    "please send the file parsed\n" RESET);
            free(usage);
            return 1;
        }

        pair_t *pair = init_pair(500);
        hash_t **hash_tab = hash(usage->output, pair);

        int index =
            getBucketIndex2(usage->author, hash_tab, pair->size);

        fprintf(stdout, RESET "Number of article of %s : %i\n",
                usage->author, (hash_tab[index]->article)[0]);

        fprintf(stdout,
                RESET "List of article of %s : ", usage->author);

        for (int i = 1; i <= (hash_tab[index]->article)[0]; i++)
            fprintf(stdout, RESET "%i ",
                    (hash_tab[index]->article)[i]);

        fprintf(stdout, "\n");

        fprintf(stdout,
                RESET "Free of author's graph and article's graph\n");

        // remove the hash table
        free_tab(hash_tab, pair->size);
        free(pair);

        return 0;
    }

    if (usage->author != NULL && usage->distance != NULL) {

        int display = 0;
        if (strstr(usage->output, "parsed") == NULL) {

            display = 1;
            fprintf(stdout,
                    RED "If you want the co_author of a N distance, "
                        "please send the file parsed\n" RESET);
            free(usage);
            return 1;
        }

        if (atoi(usage->distance) == 0) {

            fprintf(stdout, "None authors of a distance 0\n");
            free(usage);
            return 0;
        }

        begin = clock();

        pair_t *pair = init_pair(500);
        hash_t **hash_tab = hash(usage->output, pair);

        if (display == 1)
            fprintf(stdout, "\n");

        size_t *size_article = malloc(sizeof(size_t));
        article_t **graph_article =
            hash_article(usage->output, hash_tab, pair, size_article);

        int *neighbors = dist_n(atoi(usage->distance), usage->author,
                                graph_article, hash_tab, pair);

        fprintf(stdout,
                RESET "List of co authors of %s of a distance %s :\n",
                usage->author, usage->distance);

        for (int i = 1; i <= neighbors[0]; i++) {

            fprintf(stdout, "%s ", hash_tab[neighbors[i]]->author);

            if (i != neighbors[0])
                fprintf(stdout, "/ ");
        }

        fprintf(stdout, RESET "\n");

        end = clock();

        if (usage->time == 1)
            show_time(begin, end);

        fprintf(stdout,
                RESET "Free of author's graph and article's graph\n");

        // remove the hash table
        free_tab(hash_tab, pair->size);
        free(pair);

        // remove the article's graph
        free_article(graph_article, *size_article);
        free(size_article);

        // remove the neighbors' list
        free(neighbors);

        return 0;
    }

    free(usage);

    return 0;
}