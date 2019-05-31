/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 21:41:17 by kosadchu          #+#    #+#             */
/*   Updated: 2019/05/30 21:41:19 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	init_karetka(void)
{
	t_kar	*kar;

	kar = ft_memalloc(sizeof(t_kar));
	kar->id = 0;
	kar->carry = FALSE;
	kar->parrent_id = 0;
	kar->cur_op = 0;
	kar->last_live_cycle = 0;
	kar->cycle_count = 0;
	kar->cur_pos = 0;
}

void	init_virt(void)
{
	g_virt = ft_memalloc(sizeof(t_virt));
	g_virt->last_alive = 0;
	g_virt->cycles_count = 0;
	g_virt->cycles_to_die = CYCLE_TO_DIE;
	g_virt->check_count = 0;
}

void	make_map(void)
{
	int 	i;
	int 	id;
	int		place;

	i = 0;
	id = 1;
	place = 0;
	init_virt();
	while (i < g_players->len)
	{
		if (g_players->team[i]->id == id)
		{
			ft_memcpy(&(g_virt->map[place]), g_players->team[i]->code, \
			g_players->team[i]->size);
			id++;
			i = -1;
			place += MEM_SIZE / g_players->len;
		}
		i++;
	}
}
