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

#include "includes/core.h"

void	handle_position(t_pr *pr, int step)
{
	if (pr->cur_pos + step >= MEM_SIZE)
		pr->cur_pos = (pr->cur_pos + step) % MEM_SIZE;
	if (pr->cur_pos + step < 0)
		pr->cur_pos = (pr->cur_pos + step) + MEM_SIZE;
	else
		pr->cur_pos += step;
}

int32_t		bytes_in_int(t_prcs *pr, int size)
{
	int 	i;
	uint8_t buf[4];
	int32_t res;

	i = 0;
	while (i < size)
	{
		if (pr->cur_pos + 1 >= MEM_SIZE)
			pr->cur_pos = (pr->cur_pos + 1) % MEM_SIZE;
		buf[i++] = g_vm->map[++pr->cur_pos];
	}
	if (size == 4)
	{
		res = (unsigned char)buf[0] << 24;
		res |= (unsigned char)buf[1] << 16;
		res |= (unsigned char)buf[2] << 8;
		res |= (unsigned char)buf[3];
		return ((int32_t)res);
	}
	else if (size == 2)
	{
		res = (unsigned char)buf[0] << 8;
		res |= (unsigned char)buf[1];
		return ((short)res);
	}
	else if (size == 1)
		return (res = (unsigned char)buf[0]);
	return (0);
}

void	init_vm(void)
{
	g_vm = ft_memalloc(sizeof(t_vm));
	g_vm->last_alive = 0;
	g_vm->cycles = 0;
	g_vm->cycles_to_die = CYCLE_TO_DIE;
	g_vm->check_cycle = 0;
	g_vm->checks = 0;
	g_vm->prev_cycle_to_die = CYCLE_TO_DIE;
}

void 	init_start_positions(void) // создаем первые каретки и делаем двусвязный список
{
	t_prcs	prcs;
	int		i;
	int		j;
	int		place;

	i = -1;
	place = 0;
	ft_lstinit(g_list, NULL);
	while (++i < g_players->len)
	{
		prcs.carry = 0;
		prcs.cycle_count = 0;
		prcs.parent_id = i + 1;
		prcs.cur_pos = place;
		prcs.reg_err = 0;
		j = -1;
		while (++j < REG_NUMBER)
			prcs.reg[j] = 0;
		prcs.reg[0] = (i + 1) * -1;
		ft_lstpush_back(list, ft_lstnew(&prcs, sizeof(t_prcs)));
		place += MEM_SIZE / g_players->len;
	}
	g_vm->last_alive = g_players->team[i];
}

void	make_map(void) // создали карту и разместили по своим позициям байт коды игроков
{
	int 	i;
	int		place;

	i = 0;
	place = 0;
	init_vm();
	while (i < g_players->len)
	{
		ft_memcpy(&(g_vm->map[place]), g_players->team[i]->code, \
		g_players->team[i]->size);
		place += MEM_SIZE / g_players->len;
		i++;
	}
//	printf("\n1\n");
//	for (int i = 0; i < MEM_SIZE; ++i) {
//		printf("%.2x ", g_vm->map[i]);
//	}
}
