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
	int32_t		arg;

	arg = bytes_in_int(pr, 4);
	if (g_flag_v == 1)
		ft_printf("P%5d | %s %d\n", pr->pr_id, op.name, arg);
	pr->last_live_cycle = g_vm->cycles;
	(arg < 0) ? arg *= -1 : 0;
	if (arg > 0 && arg <= g_players->len)
	{
		g_players->team[arg - 1]->last_live = g_vm->cycles;
		g_players->team[arg - 1]->lives_in_cur++;
		g_vm->last_alive = g_players->team[arg - 1];
	}
	g_vm->count_live_op++;
	handle_position(pr, 1);
}
