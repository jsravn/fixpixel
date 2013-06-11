#include <stdlib.h>
#include <curses.h>

enum { RED_BG, GREEN_BG, BLUE_BG };

void init(void) {
    initscr(); cbreak(); noecho(); nodelay(stdscr, TRUE);
    int r = start_color();
    if (r) {
        endwin();
        puts("Terminal does not support color mode");
        exit(r);
    }

    init_pair(RED_BG, COLOR_WHITE, COLOR_RED);
    init_pair(GREEN_BG, COLOR_WHITE, COLOR_GREEN);
    init_pair(BLUE_BG, COLOR_WHITE, COLOR_BLUE);
}

void spamcolors(void) {
    while (getch() == ERR) {
        bkgd(COLOR_PAIR(RED_BG));
        refresh();
        bkgd(COLOR_PAIR(GREEN_BG));
        refresh();
        bkgd(COLOR_PAIR(BLUE_BG));
        refresh();
    }
}

void cleanup(void) {
    endwin();
}

int main(void) {
    init();

    spamcolors();

    cleanup();

    return 0;
}
