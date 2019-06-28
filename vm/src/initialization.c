/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 21:41:17 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 13:33:09 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

void	copy_prcs(t_pr *pr, int32_t pos)
{
	t_pr	new_pr;
	int		i;

	new_pr.pr_id = g_prc_id;
	new_pr.carry = pr->carry;
	new_pr.parent_id = pr->parent_id;
	new_pr.last_live_cycle = pr->last_live_cycle;
	new_pr.cur_op = 0;
	new_pr.cycle_count = 0;
	new_pr.cur_pos = pos;
	new_pr.prev_pos = 0;
	i = -1;
	while (++i < REG_NUMBER)
		new_pr.reg[i] = pr->reg[i];
	g_prc_id++;
	ft_lstpush_front(&g_list, ft_lstnew(&new_pr, sizeof(t_pr)));
}

void	handle_position(t_pr *pr, int step)
{
	if (pr->cur_pos + step >= MEM_SIZE)
		pr->cur_pos = (pr->cur_pos + step) % MEM_SIZE;
	else if (pr->cur_pos + step < 0)
		pr->cur_pos = (pr->cur_pos + step) + MEM_SIZE;
	else
		pr->cur_pos += step;
}

void	init_vm(void)
{
	g_vm = ft_memalloc(sizeof(t_vm));
	g_vm->last_alive = 0;
	g_vm->cycles = 1;
	g_vm->ctd = CYCLE_TO_DIE;
	g_vm->check_cycle = CYCLE_TO_DIE;
	g_vm->checks = 0;
	g_vm->prev_ctd = CYCLE_TO_DIE;
}

void	init_start_positions(void)
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
		ft_bzero(&prcs, sizeof(t_prcs));
		prcs.pr_id = g_prc_id;
		prcs.parent_id = i + 1;
		prcs.cur_pos = place;
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
