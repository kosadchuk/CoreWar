/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarchen <kmarchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:01:20 by kmarchen          #+#    #+#             */
/*   Updated: 2019/06/30 17:06:23 by kmarchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/visualization.h"

void	fill_map(int32_t player, int32_t pos, int32_t size)
{
	while (size)
	{
		g_vm->visual->data[correct_pos(pos + size - 1)] = \
			get_player_color(player, PLAYER_COLOR);
		size--;
	}
}

void	fill_player(int32_t player, int32_t pos, int32_t size)
{
	int32_t i;

	i = pos;
	while (i < size + pos)
	{
		g_vm->visual->data[i] = get_player_color(player, PLAYER_COLOR);
		i++;
	}
}

void	fill_arena(void)
{
	int32_t i;
	int32_t pos;

	i = -1;
	pos = 0;
	while (++i < MEM_SIZE)
		g_vm->visual->data[i] = COLOR_PAIR(GRAY);
	i = -1;
	while (++i < g_players->len)
	{
		fill_player(i, pos, g_players->team[i]->size);
		pos += MEM_SIZE / g_players->len;
	}
}

void	fill_cursors(void)
{
	int32_t		pos;
	int32_t		player;
	t_list_elem	*prcs;

	prcs = g_list.start;
	while (prcs)
	{
		pos = correct_pos(((t_prcs *)prcs->content)->cur_pos);
		player = ((t_prcs *)prcs->content)->parent_id - 1;
		g_vm->visual->cursors[pos] = get_player_color(player, PLAYER_CURSOR);
		prcs = prcs->next;
	}
}
