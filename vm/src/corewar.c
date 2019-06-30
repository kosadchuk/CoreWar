/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarchen <kmarchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:32:37 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/30 17:05:59 by kmarchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

void	del_ptr(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

void	introduce_players(void)
{
	int		i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < g_players->len)
	{
		ft_printf(INTRDC, g_players->team[i]->id, g_players->team[i]->size, \
		g_players->team[i]->name, g_players->team[i]->comment);
		i++;
	}
}

int		main(int ac, char **av)
{
	if (ac == 1)
		ft_error(USG_V3);
	pars_av(ac, av);
	make_map();
	introduce_players();
	if (g_flag_p)
		start_war_vs();
	else
		start_war();
	return (0);
}
