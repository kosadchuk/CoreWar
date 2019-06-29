/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_av.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:43:38 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 22:26:54 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

void	validate_champ_name(char *str)
{
	char		**arr;
	int			i;

	i = 0;
	arr = ft_strsplit(str, '.');
	while (arr[i])
		i++;
	if (ft_strcmp(arr[i - 1], "cor"))
	{
		ft_printf(ERR_CHAMP_NAME, str);
		ft_error(USG_V3);
	}
	ft_free_array(arr);
}

void	save_players(char *pl, int pl_id)
{
	t_player	*player;

	if (g_save_pl->len == 4)
		ft_err(ft_printf("Too many champions\n"));
	player = ft_memalloc(sizeof(t_player));
	player->n_id = pl_id;
	player->id = 1;
	pars_champs(pl, player);
	push_array(g_save_pl, player);
}

void	check_players_id(void)
{
	int		i;
	int		j;

	i = -1;
	while (++i < g_save_pl->len)
	{
		(g_save_pl->team[i]->n_id > g_save_pl->len) ? ft_error(WRONG_N_NUM) : 0;
		if (g_save_pl->team[i]->n_id == 0)
		{
			j = -1;
			while (++j < g_save_pl->len)
			{
				(j == i && j + 1 < g_save_pl->len) ? j++ : 0;
				(j == i && j + 1 > g_save_pl->len) ? j = 0 : 0;
				if (g_save_pl->team[j]->n_id == g_save_pl->team[i]->id)
				{
					g_save_pl->team[i]->id++;
					j = -1;
				}
			}
			g_save_pl->team[i]->n_id = g_save_pl->team[i]->id;
		}
		else
			g_save_pl->team[i]->id = g_save_pl->team[i]->n_id;
	}
}

void	pars_av(int ac, char **av)
{
	int		i;

	i = 0;
	g_save_pl = new_array(4);
	while (++i < ac)
	{
		if (ft_strchr("-", av[i][0]))
			check_flag(av, &i);
		else
		{
			validate_champ_name(av[i]);
			save_players(av[i], 0);
		}
	}
	check_players_id();
	save_norm_players();
}
