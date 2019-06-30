/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarchen <kmarchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:01:26 by kmarchen          #+#    #+#             */
/*   Updated: 2019/06/30 17:43:12 by kmarchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/visualization.h"

void	render_cursors(void)
{
	int32_t i;

	i = -1;
	while (++i < MEM_SIZE)
		g_vm->visual->cursors[i] = COLOR_PAIR(GRAY);
	fill_cursors();
}

void	render_cell(int32_t x, int32_t y, int32_t pos)
{
	if (g_vm->visual->cursors[pos] != COLOR_PAIR(GRAY))
	{
		if (g_vm->visual->data[pos] == COLOR_PAIR(GRAY))
		{
			wattron(g_vm->visual->arena, COLOR_PAIR(GRAY_CURSOR));
			mvwprintw(g_vm->visual->arena, y + 1, 2 + x * 3,
				"%0.2x", 0xFF & g_vm->map[pos]);
			wattroff(g_vm->visual->arena, COLOR_PAIR(GRAY_CURSOR));
		}
		else
		{
			wattron(g_vm->visual->arena, g_vm->visual->cursors[pos]);
			mvwprintw(g_vm->visual->arena, y + 1, 2 + x * 3,
				"%0.2x", 0xFF & g_vm->map[pos]);
			wattroff(g_vm->visual->arena, g_vm->visual->cursors[pos]);
		}
	}
	else
	{
		wattron(g_vm->visual->arena, g_vm->visual->data[pos]);
		mvwprintw(g_vm->visual->arena, y + 1, 2 + x * 3,
			"%0.2x", 0xFF & g_vm->map[pos]);
		wattroff(g_vm->visual->arena, g_vm->visual->data[pos]);
	}
}

void	render_arena(void)
{
	int32_t x;
	int32_t y;

	y = -1;
	render_cursors();
	while (++y < CELLS_NUMBER)
	{
		x = -1;
		while (++x < CELLS_NUMBER)
			render_cell(x, y, y * CELLS_NUMBER + x);
	}
}

void	render(void)
{
	werase(g_vm->visual->arena);
	werase(g_vm->visual->state);
	render_arena();
	box(g_vm->visual->arena, 0, 0);
	render_state();
	box(g_vm->visual->state, 0, 0);
	wrefresh(g_vm->visual->arena);
	wrefresh(g_vm->visual->state);
}
