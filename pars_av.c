/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_av.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:43:38 by kosadchu          #+#    #+#             */
/*   Updated: 2019/05/28 15:43:40 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	validate_champ_name(char *str)
{
	char		**arr;
	int			i;

	i = 0;
	arr = ft_strsplit(str, '.');
	while (arr[i])
		i++;
	if (ft_strcmp(arr[i - 1], "cor"))
		ft_err(ft_printf("ERROR! -> %s <- is invalid champion name!\n", str));
}

void	save_players(char *pl, int pl_id)
{
	t_player	*player;

	player = ft_memalloc(sizeof(t_player*));
	player->n_id = pl_id;
	player->id = 1;
	pars_champs(pl, player); //<-- парсим байт лист
//	ft_printf("save : %s\n", player->comment);
	push_array(g_players, player); // типа по очереди запушили игроков в глобальную структуру, можно с ними делать все что захочешь и где захочешь
}

void	check_flag(char **av, int *i)
{
	int		num;

	if (!ft_strcmp("-dump", av[(*i)])) // с dump разберусь попозже
		ft_err(ft_printf("Hello! I'm dump!\n"));
	if (!ft_strcmp("-n", av[(*i)]) && av[(*i) + 1] != NULL)
	{
		if ((num = ft_atoi(av[++(*i)])) < 1 || num > MAX_PLAYERS) // если не валидный номер игрока, идем на хуй
			ft_err(ft_printf("%s%d!\n%s%d\n", FLAG_ERR, num, FLAG_ERR_2, 4));
		else if (av[(*i) + 1] != NULL)
		{
			validate_champ_name(av[++(*i)]);
			save_players(av[(*i) + 1], num);
		}
		else
			ft_error(USAGE);
	}
	else
		ft_err(ft_printf("ERROR! [%s] %s%s", av[(*i)], UNC_COMND, USAGE));
}

void	check_players_id(void)
{
	int		i;
	int		j;

	i = -1;
	while (++i < g_players->len)
	{
		(g_players->team[i]->n_id > g_players->len) ? ft_error(WRONG_N_NUM) : 0;
		if (g_players->team[i]->n_id == 0)
		{
			j = -1;
			while (++j < g_players->len)
			{
				(j == i && j + 1 < g_players->len) ? j++ : 0;
				(j == i && j + 1 > g_players->len) ? j = 0 : 0;
				if (g_players->team[j]->n_id == g_players->team[i]->id)
				{
					g_players->team[i]->id++;
					j = -1;
				}
			}
			g_players->team[i]->n_id = g_players->team[i]->id;
		}
		else
			g_players->team[i]->id = g_players->team[i]->n_id;
	}
}

void	pars_av(int ac, char **av)
{
	int			i;

	i = 0;
	g_players = new_array(4);
	while (++i < ac)
	{
		if (ft_strchr("-", av[i][0]))
			check_flag(av, &i); //смотрим есть ли флаги -n или -damp
		else
		{
			validate_champ_name(av[i]); //проверяем на валидность имя чемпиона
			save_players(av[i], 0); //сохраняем игроков в глобальный массив структур g_players
		}
	}
	check_players_id(); //по итогам присваиваем игрокам id номер
}
