/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 17:09:33 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 13:33:39 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

void	pars_n_flag(char **av, int *i)
{
	int		num;

	num = ft_atoi(av[++(*i)]);
	if (num < 1 || num > MAX_PLAYERS)
		ft_err(ft_printf("%s%d!\n%s%d\n", FLAG_ERR, num, FLAG_ERR_2, 4));
	else if (av[(*i) + 1] != NULL)
	{
		validate_champ_name(av[++(*i)]);
		save_players(av[(*i)], num);
	}
	else
		ft_error(USG_V3);
}

void	pars_v_flag(char **av, int *i)
{
	int		num;

	num = ft_atoi(av[++(*i)]);
	if (num == 1)
		g_flag_v = 1;
	else if (num == 2)
		g_flag_v2 = 1;
	else if (num == 3)
		g_flag_v3 = 1;
	else
	{
		ft_printf(ERR_FLAG_V);
		ft_err(ft_printf(USG_V3));
	}
	if (av[(*i) + 1] != NULL)
	{
		validate_champ_name(av[++(*i)]);
		save_players(av[(*i)], num);
	}
	else
		ft_error(USG_V3);
}

void	check_flag(char **av, int *i)
{
	int		d;

	g_dump = 0;
	g_flag_v = 0;
	g_flag_v2 = 0;
	g_flag_v3 = 0;
	if (!ft_strcmp("-dump", av[(*i)]) && av[(*i) + 1] != NULL\
	&& av[(*i) + 2] != NULL)
	{
		d = ft_atoi(av[++(*i)]);
		if (d < 0 || d > 2147483647)
			ft_err(ft_printf(ERR_DUMP_NUM));
		g_dump = d;
	}
	else if (!ft_strcmp("-n", av[(*i)]) && av[(*i) + 1] != NULL)
		pars_n_flag(av, i);
	else if (!ft_strcmp("-v", av[(*i)]) && av[(*i) + 1] != NULL)
		pars_v_flag(av, i);
	else
		ft_err(ft_printf(ERRR"[%s] %s%s", av[(*i)], UNC_COMND, USG_V3));
}
