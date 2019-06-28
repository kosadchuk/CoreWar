/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 17:43:49 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 13:33:21 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

void	make_map(void)
{
	int		i;
	int		place;

	i = 0;
	place = 0;
	init_vm();
	while (i < g_players->len)
	{
		ft_memcpy(&(g_vm->map[place]), g_players->team[i]->code,\
		g_players->team[i]->size);
		place += MEM_SIZE / g_players->len;
		i++;
	}
}

void	print_dump(void)
{
	int		i;
	int		num;

	i = -1;
	num = 0;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0)
		{
			if (i != 0)
				ft_printf("\n");
			num = i;
			if (i == num)
			{
				if (num == 0)
					ft_printf("0x0000 : ");
				else
					ft_printf("%#.4x : ", num);
			}
		}
		ft_printf("%.2x ", g_vm->map[i]);
	}
	ft_printf("\n");
}

void	write_in_map(int32_t pos, uint8_t *buf)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		if (pos >= MEM_SIZE)
			pos = pos % MEM_SIZE;
		else if (pos < 0)
			pos = pos + MEM_SIZE;
		g_vm->map[pos] = buf[i];
		pos++;
	}
}
