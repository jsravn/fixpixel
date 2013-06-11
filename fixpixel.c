#include <curses.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

// Constants
enum { RED_BG = 1, GREEN_BG = 2, BLUE_BG = 3 };
const static double FPS_CAP = 60.0;
const static double RESOLUTION_MS = 0.1;
static const long ONE_MILLION = 1000000L;
static const long ONE_BILLION = 1000000000L;

// FPS tracking
static unsigned long frames;
static long start;

static long nanotime(void) {
    struct timespec cur;
    clock_gettime(CLOCK_MONOTONIC, &cur);
    return cur.tv_sec * ONE_BILLION + cur.tv_nsec;
}

static void init(void) {
    initscr(); cbreak(); noecho(); nodelay(stdscr, TRUE); curs_set(0);
    int r = start_color();
    if (r) {
        endwin();
        puts("Terminal does not support color mode");
        exit(r);
    }

    init_pair(RED_BG, COLOR_WHITE, COLOR_RED);
    init_pair(GREEN_BG, COLOR_WHITE, COLOR_GREEN);
    init_pair(BLUE_BG, COLOR_WHITE, COLOR_BLUE);

    srand(time(NULL));

    frames = 0;
    start = nanotime();
}

static chtype rand_color_pair(void) {
    switch (rand() % 3) {
        case 0: return COLOR_PAIR(RED_BG);
        case 1: return COLOR_PAIR(GREEN_BG);
        case 2: return COLOR_PAIR(BLUE_BG);
    }

    endwin(); puts("BUG - rand_color_pair"); exit(-1);
}

static void wait_for_next_frame(void) {
    static long last_nanos = 0;
    const struct timespec sleep_time = { 0, RESOLUTION_MS * ONE_MILLION };

    while (true) {
        long cur_nanos = nanotime();
        long since_last_nanos = cur_nanos - last_nanos;

        if (since_last_nanos > (1.0 / FPS_CAP) * ONE_BILLION) {
            last_nanos = cur_nanos;
            break;
        }

        nanosleep(&sleep_time, NULL);
    }
}

static void spamcolors(void) {
    while (getch() == ERR) {
        bkgd(rand_color_pair());
        refresh();
        frames++;
        wait_for_next_frame();
    }
}

static void cleanup(void) {
    endwin();

    double elapsed_s = ((nanotime() - start) / (double) ONE_BILLION);
    printf("Frames per second: %f\n", frames / elapsed_s);
}

int main(void) {
    init();

    spamcolors();

    cleanup();

    return 0;
}
