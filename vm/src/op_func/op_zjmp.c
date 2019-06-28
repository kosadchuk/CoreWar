/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <kosadchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 14:21:02 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 15:25:16 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

void	op_zjmp(t_pr *pr, t_op op, uint32_t codage)
{
	short		value;

	codage = 0;
	value = bytes_in_int(pr, op.lable_size);
	if (pr->carry == 1)
	{
		if (g_flag_v == 1)
			ft_printf("P%5d | %s %d OK\n", pr->pr_id, op.name, value);
		value %= IDX_MOD;
		pr->cur_pos = pr->prev_pos;
		handle_position(pr, value);
	}
	else
	{
		if (g_flag_v == 1)
			ft_printf("P%5d | %s %d FAILED\n", pr->pr_id, op.name, value);
		handle_position(pr, 1);
	}
}
