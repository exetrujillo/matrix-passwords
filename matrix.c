#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <string.h>

#define CSI "\x1b["
#define HIDE_CURSOR CSI "?25l"
#define SHOW_CURSOR CSI "?25h"
#define CLEAR_SCREEN CSI "2J"
#define RESET CSI "0m"
#define BOLD_WHITE CSI "1;97m"
#define BRIGHT_GREEN CSI "92m"
#define DIM_GREEN CSI "2;32m"

static volatile sig_atomic_t running = 1;

static void handle_sigint(int sig) {
    (void)sig;
    running = 0;
}

static void restore_terminal(void) {
    fputs(CSI RESET SHOW_CURSOR, stdout);
    fflush(stdout);
}

static void get_term_size(int *rows, int *cols) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        *rows = 24;
        *cols = 80;
    } else {
        *rows = ws.ws_row;
        *cols = ws.ws_col;
    }
}

static inline void move_cursor(int r, int c) {
    printf(CSI "%d;%dH", r, c);
}

static inline char rand_char(void) {
    // Conjunto de caracteres (ASCII) para evitar problemas de encoding.
    static const char *set = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#$&*+-/<>|";
    static int set_len = 0;
    if (!set_len) set_len = (int)strlen(set);
    return set[rand() % set_len];
}

int main(void) {
    struct timespec ts = {0, 50 * 1000 * 1000}; // 50 ms
    srand((unsigned)time(NULL) ^ (unsigned)getpid());

    atexit(restore_terminal);
    signal(SIGINT, handle_sigint);
    signal(SIGTERM, handle_sigint);

    int rows, cols;
    get_term_size(&rows, &cols);

    // Longitud de la estela
    int tail_len = rows / 10;
    if (tail_len < 6) tail_len = 6;
    if (tail_len > 24) tail_len = 24;

    // Estado por columna
    int *y = (int *)malloc(sizeof(int) * cols);
    int *cooldown = (int *)malloc(sizeof(int) * cols);
    if (!y || !cooldown) {
        fprintf(stderr, "Sin memoria.\n");
        free(y);
        free(cooldown);
        return 1;
    }

    for (int c = 0; c < cols; ++c) {
        y[c] = -(rand() % rows);
        cooldown[c] = rand() % 3;
    }

    fputs(HIDE_CURSOR CLEAR_SCREEN, stdout);
    fflush(stdout);

    while (running) {
        nanosleep(&ts, NULL);

        for (int c = 0; c < cols; ++c) {
            if (cooldown[c]-- > 0) {
                continue;
            }
            cooldown[c] = rand() % 3;

            int head = y[c];

          if (head >= 1 && head <= rows) {
                move_cursor(head, c + 1);
                fputs(BOLD_WHITE, stdout);
                putchar(rand_char());
            }

            int second = head - 1;
            if (second >= 1 && second <= rows) {
                move_cursor(second, c + 1);
                fputs(BRIGHT_GREEN, stdout);
                putchar(rand_char());
            }

            for (int k = 2; k <= tail_len; ++k) {
                int row = head - k;
                if (row < 1) break;
                move_cursor(row, c + 1);
                fputs(DIM_GREEN, stdout);
                putchar(rand_char());
            }

            int erase_row = head - tail_len - 1;
            if (erase_row >= 1 && erase_row <= rows) {
                move_cursor(erase_row, c + 1);
                fputs(RESET, stdout);
                putchar(' ');
            }

            y[c]++;

            if (y[c] - tail_len > rows + 2) {
                y[c] = -(rand() % (rows / 2 + 1));
            }
        }

        fputs(RESET, stdout);
        fflush(stdout);
    }

    move_cursor(rows, 1);
    return 0;
}
