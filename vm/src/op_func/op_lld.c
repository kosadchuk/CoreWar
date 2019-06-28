/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:04:06 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 13:34:42 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

void	op_lld(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		value;
	int32_t		pos;

	if ((codage == DR || codage == IR) && pr->reg_err == 0)
	{
		if (op.args[0].tp == DIR_CODE)
			pr->reg[op.args[1].reg_num] = op.args[0].value;
		else if (op.args[0].tp == IND_CODE)
		{
			pos = pr->prev_pos + op.args[0].value;
			value = read_bytes(pos);
			pr->reg[op.args[1].reg_num] = value;
		}
		if (g_flag_v == 1)
			ft_printf("P%5d | %s %d r%d\n", pr->pr_id, op.name,\
			op.args[0].value, op.args[1].reg_num + 1);
		pr->carry = (pr->reg[op.args[1].reg_num] == 0) ? 1 : 0;
	}
	handle_position(pr, 1);
}
