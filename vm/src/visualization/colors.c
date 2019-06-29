#include "../../inc/visualization.h"

void    init_colors(void)
{
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(COLOR_GREEN, 0, 1000, 0);
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    init_color(COLOR_BLUE, 0, 0, 1000);
    init_color(COLOR_MAGENTA, 1000, 0, 1000);
    init_color(COLOR_CYAN, 0, 1000, 1000);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_color(COLOR_GRAY, 355, 355, 355);
    init_color(LIGHT_RED, 700, 0, 0);
    init_color(DARK_RED, 255, 0, 0);
    init_color(LIGHT_GREEN, 0, 700, 0);
    init_color(DARK_GREEN, 0, 255, 0);
    init_pair(STATE_PAUSED, LIGHT_RED, DARK_RED);
    init_pair(STATE_RUNNING, LIGHT_GREEN, DARK_GREEN);
    init_pair(GRAY, COLOR_GRAY, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(GRAY_CURSOR, COLOR_BLACK, COLOR_GRAY);
    init_pair(RED_CURSOR, COLOR_BLACK, COLOR_RED);
    init_pair(GREEN_CURSOR, COLOR_BLACK, COLOR_GREEN);
    init_pair(BLUE_CURSOR, COLOR_BLACK, COLOR_BLUE);
    init_pair(MAGENTA_CURSOR, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(RED_LIVE, COLOR_WHITE, COLOR_RED);
    init_pair(GREEN_LIVE, COLOR_WHITE, COLOR_GREEN);
    init_pair(BLUE_LIVE, COLOR_WHITE, COLOR_BLUE);
    init_pair(MAGENTA_LIVE, COLOR_WHITE, COLOR_MAGENTA);
}

int    get_player_color(int index)
{
    int colors[15] = {
        COLOR_PAIR(RED),
        COLOR_PAIR(GREEN),
        COLOR_PAIR(BLUE),
        COLOR_PAIR(MAGENTA)
    };
    return (colors[index]);
}
