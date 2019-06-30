/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarchen <kmarchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:01:34 by kmarchen          #+#    #+#             */
/*   Updated: 2019/06/30 17:55:38 by kmarchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/visualization.h"

void	render_players(void)
{
	int32_t i;

	i = -1;
	while (++i < g_players->len)
	{
		mvwprintw(g_vm->visual->state, 15 + i * 4, 6,
			"Player -%d:", g_players->team[i]->id);
		wattron(g_vm->visual->state, get_player_color(i, PLAYER_COLOR));
		mvwprintw(g_vm->visual->state, 15 + i * 4, 17,
			"%.36s", g_players->team[i]->name);
		wattroff(g_vm->visual->state, get_player_color(i, PLAYER_COLOR));
		mvwprintw(g_vm->visual->state, 16 + i * 4, 10, "Last live");
		mvwprintw(g_vm->visual->state, 16 + i * 4, 45,
			"%d", g_players->team[i]->last_live);
		mvwprintw(g_vm->visual->state, 17 + i * 4, 10,
			"Lives in current period");
		mvwprintw(g_vm->visual->state, 17 + i * 4, 45,
			"%d", g_players->team[i]->lives_in_cur);
	}
}

void	render_status(void)
{
	mvwprintw(g_vm->visual->state, 3, 6, "STATE");
	if (g_vm->visual->paused)
	{
		wattron(g_vm->visual->state, COLOR_PAIR(STATE_PAUSED) | A_BOLD);
		mvwprintw(g_vm->visual->state, 3, 45, " PAUSED ");
		wattroff(g_vm->visual->state, COLOR_PAIR(STATE_PAUSED) | A_BOLD);
	}
	else
	{
		wattron(g_vm->visual->state, COLOR_PAIR(STATE_RUNNING) | A_BOLD);
		mvwprintw(g_vm->visual->state, 3, 45, " RUNNING ");
		wattroff(g_vm->visual->state, COLOR_PAIR(STATE_RUNNING) | A_BOLD);
	}
}

void	render_winner(void)
{
	int players_offset;

	players_offset = 15 + g_players->len * 4;
	mvwprintw(g_vm->visual->state, players_offset + 11, 6, "WINNER");
	wattron(g_vm->visual->state,
		get_player_color(g_vm->last_alive->id - 1, PLAYER_COLOR));
	mvwprintw(g_vm->visual->state, players_offset + 11, 15,
		" %.36s (%d) ", g_vm->last_alive->name, g_vm->last_alive->id);
	wattroff(g_vm->visual->state,
		get_player_color(g_vm->last_alive->id - 1, PLAYER_COLOR));
}

void	render_state(void)
{
	int players_offset;

	players_offset = 15 + g_players->len * 4;
	render_status();
	mvwprintw(g_vm->visual->state, 6, 6, "Cycles/second limit");
	mvwprintw(g_vm->visual->state, 6, 45, "%d", g_vm->visual->speed);
	mvwprintw(g_vm->visual->state, 8, 6, "Cycle");
	mvwprintw(g_vm->visual->state, 8, 45, "%d", g_vm->cycles);
	mvwprintw(g_vm->visual->state, 10, 6, "Processes");
	mvwprintw(g_vm->visual->state, 10, 45, "%d", g_list.list_size);
	render_players();
	mvwprintw(g_vm->visual->state, players_offset + 3, 6, "CYCLE_TO_DIE");
	mvwprintw(g_vm->visual->state, players_offset + 3, 45, "%d", CYCLE_TO_DIE);
	mvwprintw(g_vm->visual->state, players_offset + 5, 6, "CYCLE_DELTA");
	mvwprintw(g_vm->visual->state, players_offset + 5, 45, "%d", CYCLE_DELTA);
	mvwprintw(g_vm->visual->state, players_offset + 7, 6, "NBR_LIVE");
	mvwprintw(g_vm->visual->state, players_offset + 7, 45, "%d", NBR_LIVE);
	mvwprintw(g_vm->visual->state, players_offset + 9, 6, "MAX_CHECKS");
	mvwprintw(g_vm->visual->state, players_offset + 9, 45, "%d", MAX_CHECKS);
	if (g_vm->ctd <= 0 || g_list.list_size == 0)
		render_winner();
}
