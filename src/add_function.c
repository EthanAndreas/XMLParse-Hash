#include "../include/add_function.h"

/**
 * @brief Print usages of command line
 *
 */
void print_option(void) {

    fprintf(
        stdout, GREY
        "\n"
        "Options:\n"
        "\t-i FILE         type in the reading's file\n"
        "\t-o FILE         type in the writing's file\n\n"
        "\t-p              parse the file\n"
        "\t-p -t           show the time of the parsing\n"
        "\t-g              build the hash table with the file "
        "parsed (the graph)\n"
        "\t-g -t           show the time of the building of the "
        "hash table\n\n"
        "\t-l WORD         show authors which include the word\n"
        "\t-a AUTHOR       show the articles of an author\n"
        "\t-a AUTHOR -n N  show the co-authors from a distance of "
        "N of the author\n\n"
        "\t-r              show the number of the authors of the "
        "file parsed\n"
        "\t-r -g           hash the file parsed and show the number "
        "of unique authors\n"
        "\t-s              show the number of the articles of the "
        "file parsed\n"
        "\nExamples :\n"
        "./launch.sh -i assets/dblp.xml -p -o "
        "assets/dblp_parsed.xml\n"
        "\nComment :\n"
        "when you write the name of the author in the command line : "
        "put '\' before a space\n\n" RESET);
}

/**
 * @brief Print the file in the terminal
 *
 * @param[in] file
 */
void print_file(char *file) {

    FILE *file_to_print = opening_files(file, "r");

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, file_to_print))
        fprintf(stdout, "%s\n", buffer);
}

/**
 * @brief Open the file given in parameter with path format
 * and check any problems in the file opening
 *
 * @param[in] file_to_open
 * @param[in] mode
 * @return FILE*
 */
FILE *opening_files(char *file_to_open, char *mode) {

    // files opening
    FILE *file = fopen(file_to_open, mode);

    // check the opening of files
    if (file == NULL) {

        fprintf(stderr, RED "\nError" GREY
                            " : on the openning of the file\n" RESET);
        exit(1);
    }

    return (file);
}

/**
 * @brief Remove '\r' from windows file to convert
 * to linux format
 *
 * @param[in] str
 */
void remove_win_newline(char *str) {

    if (strstr(str, "\r")) {

        int n = strlen(str) - 2;

        while (str[n] != '\r' && n > 0)
            n--;

        str[n] = '\n';
        str[n + 1] = '\0';
    }
}

/**
 * @brief Display the progression of a function with counting of the
 * progress in the function itself
 *
 * @param[in] location
 * @param[in] total
 */
void progress(char *name, int location, int total) {

    double percentage = ((double)location / (double)total) * 100;

    static int state = 0;
    static int i = 1;
    static char bar[24];

    if (percentage == 100) {

        i = 1;
        return;
    }

    bar[0] = '[';
    bar[21] = ']';
    for (int j = 1; j < 21; j++)
        bar[j] = '.';

    state++;

    if (state < (total / 10000))
        return;

    if (percentage - (5 * i) > -0.01)
        i++;

    if (percentage > 99.9)
        percentage = 100;

    for (int j = 1; j < i; j++)
        bar[j] = '#';

    fprintf(stdout,
            RESET "\rProgression of %s function : %s " BLUE
                  "%.2f %%" BLACK,
            name, bar, percentage);
    fflush(stdout);

    state = 0;
}

/**
 * @brief For each ctrl c, it increases by 1 a counter,
 * when the counter is 2, it stops the programm
 *
 */
void handler_c(int sig) {

    (void)sig;

    counter_sig.ctrl_c++;
    fprintf(stdout, "\n" GREY "SIGINT n°%i detected" RESET "\n",
            counter_sig.ctrl_c);

    if (counter_sig.ctrl_c == 2) {
        fprintf(stdout, "\n" RED "Interruption"
                        "\n");
        exit(0);
    }
}

void show_time(clock_t begin, clock_t end) {

    unsigned long ms =
        (double)((end - begin) * 1000) / (double)CLOCKS_PER_SEC;

    unsigned long msec = ms % 1000;
    unsigned long sec = (ms - msec) / 1000;

    fprintf(stdout,
            RESET "Time for graph building : " MAGENTA "%li,%li" RESET
                  " secondes" RESET "\n",
            sec, msec);
}