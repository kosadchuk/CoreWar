#include "../../inc/visualization.h"

void    init_colors(void)
{
    init_color(1, 355, 355, 355);
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, 1, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
}

void                create_border(WINDOW *win)
{
    box(win, 0, 0);
}

void    setup_windows(void)
{
    g_vm->visual->arena = newwin(ARENA_HEIGHT + 2, ARENA_WIDTH + 3, 1, 2);
    create_border(g_vm->visual->arena);
    wrefresh(g_vm->visual->arena);
    g_vm->visual->state = newwin(STATE_HEIGHT + 2, STATE_WIDTH, 1, ARENA_WIDTH + 8);
    create_border(g_vm->visual->state);
    wrefresh(g_vm->visual->state);
}

void    render_arena(void)
{
    int x;
    int y;

    y = -1;
    while (++y < CELLS_NUMBER)
    {
        x = -1;
        while (++x < CELLS_NUMBER)
        {
            wattron(g_vm->visual->arena, COLOR_PAIR(2 | A_BOLD));
            mvwprintw(g_vm->visual->arena, y + 1, 2 + x * 3, "%0.2x", 0x0);
            wattroff(g_vm->visual->arena, COLOR_PAIR(2 | A_BOLD));
        }
    }
    wrefresh(g_vm->visual->arena);
}

void    render_players(void)
{
    int i;

    i = -1;
    while (++i < g_players->len)
    {
        mvwprintw(g_vm->visual->state, 15 + i * 4, 6, "Player -%d:", g_players->team[i]->id);
        mvwprintw(g_vm->visual->state, 15 + i * 4, 17, "%s", g_players->team[i]->name);
        mvwprintw(g_vm->visual->state, 16 + i * 4, 10, "Last live");
        mvwprintw(g_vm->visual->state, 16 + i * 4, 45, "%d", g_players->team[i]->last_live);
        mvwprintw(g_vm->visual->state, 17 + i * 4, 10, "Lives in current period");
        mvwprintw(g_vm->visual->state, 17 + i * 4, 45, "%d", g_players->team[i]->lives_in_cur);
    }
}

void    render_state(void)
{
    mvwprintw(g_vm->visual->state, 3, 6, "STATE");
    
    wattron(g_vm->visual->state, COLOR_PAIR(3 | A_BOLD));
    mvwprintw(g_vm->visual->state, 3, 45, "PAUSED");
    wattroff(g_vm->visual->state, COLOR_PAIR(3 | A_BOLD));
    
    mvwprintw(g_vm->visual->state, 6, 6, "Cycles/second limit");
    mvwprintw(g_vm->visual->state, 6, 45, "%d", g_vm->cycles);

    mvwprintw(g_vm->visual->state, 8, 6, "Cycle");
    mvwprintw(g_vm->visual->state, 8, 45, "0");

    mvwprintw(g_vm->visual->state, 10, 6, "Processes");
    mvwprintw(g_vm->visual->state, 10, 45, "%d", g_players->len);

    render_players();

    wrefresh(g_vm->visual->state);
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

    render_arena();
    render_state();

    getchar();

    endwin();
}
