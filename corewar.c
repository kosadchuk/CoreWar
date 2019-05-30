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

int 	main(int ac, char **av)
{
	if (ac == 1)
		ft_error("Please, choose a players for blood war!\n");
	pars_av(ac, av); //Валидация агрументов и парсинг игроков
	for (int i = 0; i < g_players->len; ++i) {
		printf("id : %d\n", g_players->team[i]->id);
		printf("name : %s\n", g_players->team[i]->name);
		printf("comment : %s\n", g_players->team[i]->comment);
		printf("size : %d\n", g_players->team[i]->size);
		for (int j = 0; j < g_players->team[i]->size; ++j) {
			printf("%.2x ", g_players->team[i]->code[j]);
		}
		printf("\n");
	}
	ft_printf("working\n");
	return (0);
}