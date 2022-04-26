#ifndef MACRO
#define MACRO

#include "color_set.h"

// Global variables
char *__current_test_name;
struct timeval begin, end;

/**
 * @brief Check the return of a primitive system
 *
 */
#define CHECK(ret)                                             \
    do {                                                       \
        __current_test_name = #ret;                            \
        if ((ret) == -1) {                                     \
            fprintf(stderr,                                    \
                    RED "Error" GREY                           \
                        " : on primitive system - %s\n" RESET, \
                    __current_test_name);                      \
            exit(1);                                           \
        }                                                      \
    } while (0)

/**
 * @brief Launch the function in parameter and check
 * its return
 */
#define LAUNCH_TEST(func, number)                            \
    do {                                                     \
        __current_test_name = #func;                         \
        int d = func();                                      \
        if (d == 0) {                                        \
            fprintf(stdout,                                  \
                    RESET "Test %s"                          \
                          " : " RESET GREEN "OK" RESET "\n", \
                    number);                                 \
        }                                                    \
        if (d == 1) {                                        \
            fprintf(stdout,                                  \
                    RESET "Test %s"                          \
                          " : " RED "ERROR" RESET "\n",      \
                    number);                                 \
        }                                                    \
    } while (0)

/**
 * @brief Check the time of a function and authorize only less than 30
 * seconds execution
 */
#define CHECK_TIME(func)                                         \
    do {                                                         \
        __current_test_name = #func;                             \
        int d1 = gettimeofday(&begin, NULL);                     \
        func();                                                  \
        int d2 = gettimeofday(&end, NULL);                       \
        if (d1 == -1 || d2 == -1) {                              \
            fprintf(stderr, RED "Error :" GREY                   \
                                " of primitive in LAUNCH_TEST"); \
            exit(1);                                             \
        }                                                        \
        double sec =                                             \
            (double)(end.tv_usec - begin.tv_usec) / 1000000 +    \
            (double)(end.tv_sec - begin.tv_sec);                 \
        if (sec > 30000) {                                       \
            fprintf(stderr,                                      \
                    RED "Error :" GREY                           \
                        " Time for %s is too long (%s)\n" RESET, \
                    __current_test_name, sec);                   \
            exit(1);                                             \
        }                                                        \
    } while (0)

#endif