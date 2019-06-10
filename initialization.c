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

void	copy_prcs(t_pr *pr, int32_t pos)
{
	t_pr	new_pr;
	int		i;

	new_pr.pr_id = g_prc_id;
	new_pr.carry = pr->carry;
	new_pr.parent_id = pr->parent_id;
	new_pr.cur_op = 0;
	new_pr.last_live_cycle = 0;
	new_pr.cycle_count = 0;
	new_pr.cur_pos = pos;
	new_pr.prev_pos = 0;
	i = -1;
	while (++i < REG_NUMBER)
		new_pr.reg[i] = pr->reg[i];
//	ft_printf("PR %d r1[%d]\n", g_prc_id, new_pr.reg[0]);
	g_prc_id++;
	ft_lstpush_front(&g_list, ft_lstnew(&new_pr, sizeof(t_pr)));
}

void	handle_position(t_pr *pr, int step)
{
	if (pr->cur_pos + step >= MEM_SIZE)
		pr->cur_pos = (pr->cur_pos + step) % MEM_SIZE;
	if (pr->cur_pos + step < 0)
		pr->cur_pos = (pr->cur_pos + step) + MEM_SIZE;
	else
		pr->cur_pos += step;
}

void	int_to_byte(int32_t nbr, uint8_t *buf)
{
	int32_t	tmp;

	tmp = nbr;
	tmp = tmp >> 24;
	buf[0] = tmp;
	tmp = nbr;
	tmp = tmp << 8;
	tmp = tmp >> 24;
	buf[1] = tmp;
	tmp = nbr;
	tmp = tmp << 16;
	tmp = tmp >> 24;
	buf[2] = tmp;
	tmp = nbr;
	tmp = tmp << 24;
	tmp = tmp >> 24;
	buf[3] = tmp;
}

int32_t		bytes_in_int(t_prcs *pr, int size)
{
	int 	i;
	uint8_t buf[4];
	int32_t res;

	i = -1;
	res = 0;
	while (++i < size)
	{
		if (pr->cur_pos + 1 >= MEM_SIZE)
			pr->cur_pos = (pr->cur_pos + 1) % MEM_SIZE;
		buf[i] = g_vm->map[++pr->cur_pos];
	}
	if (size == 4)
	{
		res |= (unsigned char)buf[0] << 24;
		res |= (unsigned char)buf[1] << 16;
		res |= (unsigned char)buf[2] << 8;
		res |= (unsigned char)buf[3];
		return ((int32_t)res);
	}
	else if (size == 2)
	{
		res |= (unsigned char)buf[0] << 8;
		res |= (unsigned char)buf[1];
		return ((short)res);
	}
	else if (size == 1)
		return ((unsigned char)buf[0]);
	return (0);
}

void	init_vm(void)
{
	g_vm = ft_memalloc(sizeof(t_vm));
	g_vm->last_alive = 0;
	g_vm->cycles = 1;
	g_vm->cycles_to_die = CYCLE_TO_DIE;
	g_vm->check_cycle = 0;
	g_vm->checks = 0;
	g_vm->prev_cycle_to_die = CYCLE_TO_DIE;
}

void del_ptr(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

void 	init_start_positions(void) // создаем первые каретки и делаем двусвязный список
{
	t_prcs	prcs;
	int		i;
	int		j;
	int		place;

	i = -1;
	place = 0;
	g_prc_id = 1;
	ft_lstinit(&g_list, &del_ptr);
	while (++i < g_players->len)
	{
		prcs.pr_id = g_prc_id;
		prcs.carry = 0;
		prcs.cycle_count = 0;
		prcs.parent_id = i + 1;
		prcs.cur_pos = place;
		prcs.reg_err = 0;
		prcs.last_live_cycle = 0;
		j = -1;
		while (++j < REG_NUMBER)
			prcs.reg[j] = 0;
		prcs.reg[0] = (i + 1) * -1;
		ft_lstpush_front(&g_list, ft_lstnew(&prcs, sizeof(t_prcs)));
		place += MEM_SIZE / g_players->len;
		g_prc_id++;
	}
	g_vm->last_alive = g_players->team[i - 1];
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
