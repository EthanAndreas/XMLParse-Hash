#ifndef ADD_FUNC
#define ADD_FUNC

#include "include.h"
#include <signal.h>
#include <stdio.h>
#include <time.h>

struct counter_sig {
    volatile sig_atomic_t ctrl_c;
} counter_sig;

void print_option(void);

void print_file(char *file);

FILE *opening_files(char *file_to_open, char *mode);

void remove_win_newline(char *str);

void progress(char *name, int location, int total);

void handler_c(int sig);

void show_time(clock_t begin, clock_t end);

#endif