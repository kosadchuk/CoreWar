/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 17:25:23 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/03 17:25:26 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	op_live(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t 	res;

//	handle_position(pr, 1);
	res = bytes_in_int(pr, op.lable_size);
	pr->last_live_cycle = g_vm->cycles;
	if (res > 0 && res < g_players->len)
	{
		g_players->team[res - 1]->last_live = g_vm->cycles;
		g_players->team[res - 1]->lives_in_cur++;
		g_vm->last_alive = g_players->team[res - 1];
	}
	g_vm->count_live_op++;
}