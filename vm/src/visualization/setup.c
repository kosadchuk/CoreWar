#include "../../inc/visualization.h"

void    init_colors(void)
{
    init_color(1, 355, 355, 355);
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, 1, COLOR_BLACK);
}

void                create_border(WINDOW *win)
{
    box(win, 0, 0);
}

void    setup_windows(void)
{
    g_vm->visual->arena = newwin(HEIGHT, WIDTH + 4, 1, 2);
    create_border(g_vm->visual->arena);
    wrefresh(g_vm->visual->arena);
}

void print_map(void)
{
    int                 i;

    i = -1;

    wmove(g_vm->visual->arena, 1, 2);

    while (++i < MEM_SIZE)
    {
        wattron(g_vm->visual->arena, COLOR_PAIR(2 | A_BOLD));
        wprintw(g_vm->visual->arena, "%0.2x", 0x0);
        wattroff(g_vm->visual->arena, COLOR_PAIR(2 | A_BOLD));
        waddch(g_vm->visual->arena, ' ');
    }
    wrefresh(g_vm->visual->arena);
}

void    setup_visual(void)
{
    initscr();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(false);
    cbreak();
    noecho();
    use_default_colors();
    start_color();
    init_colors();
    setup_windows();

    print_map();

    getchar();

    endwin();
}
