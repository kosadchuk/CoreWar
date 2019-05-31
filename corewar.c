/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:32:37 by kosadchu          #+#    #+#             */
/*   Updated: 2019/05/28 12:32:40 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#define	INTRDC	"* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n"

void	introduce_players(void)
{
	int 	i;
	int 	id;

	i = 0;
	id = 1;
	ft_printf("Introducing contestants...\n");
	while (i <= g_players->len)
	{
		if (g_players->team[i]->id == id)
		{
			ft_printf(INTRDC, g_players->team[i]->id, g_players->team[i]->size, \
			g_players->team[i]->name, g_players->team[i]->comment);
			id++;
			i = -1;
		}
		i++;
	}
}

int 	main(int ac, char **av)
{
	if (ac == 1)
		ft_error(NO_PLAYER);
	pars_av(ac, av);//Валидация агрументов и парсинг игроков
	make_map();
	introduce_players();
//	for (int i = 0; i < 4096; ++i) {
//		printf("%.2x ", g_virt->map[i]);
//	}
	return (0);
}