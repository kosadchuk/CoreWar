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

#include "includes/core.h"
#define	INTRDC	"* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n"

void	introduce_players(void)
{
	int 	i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < g_players->len)
	{
		ft_printf(INTRDC, g_players->team[i]->id, g_players->team[i]->size, \
		g_players->team[i]->name, g_players->team[i]->comment);
		i++;
	}
}

int 	main(int ac, char **av)
{
	if (ac == 1)
		ft_error(NO_PLAYER);
	pars_av(ac, av);//Валидация агрументов и парсинг игроков
	make_map(); // созадли карту и разместили код игроков на свои позиции
//	introduce_players(); // представили игроков перед битвой
	start_war();
//	printf("\n2\n");
//	for (int i = 0; i < MEM_SIZE; ++i) {
//		printf("%.2x ", g_vm->map[i]);
//	}
//	system("leaks -q Corewar");
	return (0);
}