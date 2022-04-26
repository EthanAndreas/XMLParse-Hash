#include "../include/option.h"

void init_usage(usage_t *usage) {

    usage->parsing = 0;
    usage->hash = 0;
    usage->time = 0;
    usage->author_counting = 0;
    usage->line_counting = 0;
    usage->word = NULL;
    usage->author = NULL;
    usage->distance = NULL;
    usage->input = NULL;
    usage->output = NULL;
}

int option(int argc, char **argv, usage_t *usage) {

    char c;

    while ((c = getopt(argc, argv, "hi:pgtrsl:a:n:o:")) != -1) {

        switch (c) {

        case 'h':
            print_option();
            return 1;

        case 'p':
            usage->parsing = 1;
            break;

        case 'g':
            usage->hash = 1;
            break;

        case 't':
            usage->time = 1;
            break;

        case 'r':
            usage->author_counting = 1;
            break;

        case 's':
            usage->line_counting = 1;
            break;

        case 'l':
            usage->word = optarg;
            break;

        case 'a':
            usage->author = optarg;
            break;

        case 'n':
            usage->distance = optarg;
            break;

        case 'i':
            usage->input = optarg;
            break;

        case 'o':
            usage->output = optarg;
            break;

        case '?':
            if (optopt == 'i') {

                fprintf(stderr,
                        RED
                        "\nError" GREY
                        " : Option -%c requires an argument\n" RESET,
                        optopt);
                exit(1);
            } else if (optopt == 'o') {

                fprintf(stderr,
                        RED
                        "\nError" GREY
                        " : Option -%c requires an argument\n" RESET,
                        optopt);
                exit(1);
            } else if (optopt == 'a') {

                fprintf(stderr,
                        RED
                        "\nError" GREY
                        " : Option -%c requires an argument\n" RESET,
                        optopt);
                exit(1);
            } else if (optopt == 'l') {

                fprintf(stderr,
                        RED
                        "\nError" GREY
                        " : Option -%c requires an argument\n" RESET,
                        optopt);
                exit(1);
            } else if (optopt == 'n') {

                fprintf(stderr,
                        RED
                        "\nError" GREY
                        " : Option -%c requires an argument\n" RESET,
                        optopt);
                exit(1);
            } else if (isprint(optopt))
                fprintf(stderr,
                        RED "\nError" GREY
                            " : Unknown option '-%c'->\n",
                        optopt);
            else
                fprintf(stderr,
                        RED
                        "\nError" GREY
                        " : Unknown option character '%x'\n" RESET,
                        optopt);

            print_option();
            exit(1);
        }
    }

    if (usage->input == NULL && usage->parsing == 1) {

        fprintf(stderr,
                RED "\nError" GREY " : Must have '-i' before '-p' if "
                    "you want to parse\n" RESET);
        print_option();
        exit(1);
    }

    if (usage->parsing == 0 && usage->hash == 0 && usage->time == 1) {

        fprintf(stderr,
                RED "\nError" GREY " : Must have '-p' or '-g' "
                    "before '-t' if you want to "
                    "get the time of parsing\n" RESET);
        print_option();
        exit(1);
    }

    if (usage->output == NULL) {
        fprintf(stderr, RED "\nError" GREY " : Missing option '-o' "
                            "indicating parsed file\n" RESET);
        print_option();
        exit(1);
    }

    if (usage->author == NULL && usage->distance != NULL) {

        fprintf(stderr, RED
                "\nError" GREY
                " : Must have '-a' before the option '-n'\n" RESET);
        exit(1);
    }

    return 0;
}
