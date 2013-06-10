#include <curses.h>

static const short RED_BG = 1;
static const short GREEN_BG = 2;
static const short BLUE_BG = 3;

int main(void) {
    initscr(); cbreak(); noecho();
    int r = start_color();
    if (r) {
        endwin();
        puts("Terminal does not support color mode");
        return r;
    }

    init_pair(RED_BG, COLOR_WHITE, COLOR_RED);
    init_pair(GREEN_BG, COLOR_WHITE, COLOR_GREEN);
    init_pair(BLUE_BG, COLOR_WHITE, COLOR_BLUE);

    while (true) {
        bkgd(COLOR_PAIR(RED_BG));
        refresh();
        bkgd(COLOR_PAIR(GREEN_BG));
        refresh();
        bkgd(COLOR_PAIR(BLUE_BG));
        refresh();
    }

    getch();
    endwin();
    return 0;
}
