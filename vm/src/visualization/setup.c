#include "../../inc/visualization.h"

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

void fill_player(int32_t pos, int32_t player, int32_t size)
{
    int32_t i;
    int32_t value;

    i = pos;
    value = ((player - 1) % MAX_PLAYER_ID) + 1;
    while (i < size + pos)
    {
        g_vm->visual->data[i].color = get_player_color(player);
        i++;
    }
}

void fill_cursors()
{
    t_list_elem *prcs;

    prcs = g_list.start;
    while (prcs)
    {
        g_vm->visual->data[((t_prcs *)prcs->content)->cur_pos].color = get_player_cursor(((t_prcs *)prcs->content)->parent_id - 1);
        prcs = prcs->next;
    }
}

void fill_arena()
{
    int32_t i;
    int32_t pos;

    i = -1;
    pos = 0;
    while (++i < MEM_SIZE)
    {
        g_vm->visual->data[i].color = COLOR_PAIR(GRAY);
    }
    i = -1;
    while (++i < g_players->len)
    {
        fill_player(pos, i, g_players->team[i]->size);
        pos += MEM_SIZE / g_players->len;
    }

    fill_cursors();
}

// void    get_cell(int32_t index)
// {
//     return g_vm->visual->data[index];
// }

void    render_arena(void)
{
    int x;
    int y;

    y = -1;

    fill_arena();

    while (++y < CELLS_NUMBER)
    {
        x = -1;
        while (++x < CELLS_NUMBER)
        {
            wattron(g_vm->visual->arena, g_vm->visual->data[y * CELLS_NUMBER + x].color);
            mvwprintw(g_vm->visual->arena, y + 1, 2 + x * 3, "%0.2x", 0xFF & g_vm->map[y * CELLS_NUMBER + x]);
            wattroff(g_vm->visual->arena, g_vm->visual->data[y * CELLS_NUMBER + x].color);
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
        wattron(g_vm->visual->state, get_player_color(i));
        mvwprintw(g_vm->visual->state, 15 + i * 4, 17, "%s", g_players->team[i]->name);
        wattroff(g_vm->visual->state, get_player_color(i));
        mvwprintw(g_vm->visual->state, 16 + i * 4, 10, "Last live");
        mvwprintw(g_vm->visual->state, 16 + i * 4, 45, "%d", g_players->team[i]->last_live);
        mvwprintw(g_vm->visual->state, 17 + i * 4, 10, "Lives in current period");
        mvwprintw(g_vm->visual->state, 17 + i * 4, 45, "%d", g_players->team[i]->lives_in_cur);
    }
}

void    render_state(void)
{
    werase(g_vm->visual->state);
    mvwprintw(g_vm->visual->state, 3, 6, "STATE");
    
    wattron(g_vm->visual->state, COLOR_PAIR(STATE_PAUSED | A_BOLD));
    mvwprintw(g_vm->visual->state, 3, 45, " PAUSED ");
    wattroff(g_vm->visual->state, COLOR_PAIR(STATE_PAUSED | A_BOLD));

    // wattron(g_vm->visual->state, COLOR_PAIR(5 | A_BOLD));
    // mvwprintw(g_vm->visual->state, 3, 45, " RUNNING ");
    // wattroff(g_vm->visual->state, COLOR_PAIR(5 | A_BOLD));
    
    mvwprintw(g_vm->visual->state, 6, 6, "Cycles/second limit");
    mvwprintw(g_vm->visual->state, 6, 45, "%d", 50);

    mvwprintw(g_vm->visual->state, 8, 6, "Cycle");
    mvwprintw(g_vm->visual->state, 8, 45, "%d", g_vm->cycles);

    mvwprintw(g_vm->visual->state, 10, 6, "Processes");
    mvwprintw(g_vm->visual->state, 10, 45, "%d", g_list.list_size);

    render_players();

    int players_offset = 15 + g_players->len * 4;

    mvwprintw(g_vm->visual->state, players_offset + 3, 6, "CYCLE_TO_DIE");
    mvwprintw(g_vm->visual->state, players_offset + 3, 45, "%d", CYCLE_TO_DIE);

    mvwprintw(g_vm->visual->state, players_offset + 5, 6, "CYCLE_DELTA");
    mvwprintw(g_vm->visual->state, players_offset + 5, 45, "%d", CYCLE_DELTA);

    mvwprintw(g_vm->visual->state, players_offset + 7, 6, "NBR_LIVE");
    mvwprintw(g_vm->visual->state, players_offset + 7, 45, "%d", NBR_LIVE);

    mvwprintw(g_vm->visual->state, players_offset + 9, 6, "MAX_CHECKS");
    mvwprintw(g_vm->visual->state, players_offset + 9, 45, "%d", MAX_CHECKS);

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
