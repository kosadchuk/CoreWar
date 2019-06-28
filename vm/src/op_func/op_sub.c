/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:33:08 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 13:35:05 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

void	op_sub(t_pr *pr, t_op op, uint32_t codage)
{
	if (codage == RRR && pr->reg_err == 0)
	{
		pr->reg[op.args[2].reg_num] = op.args[0].value - op.args[1].value;
		pr->carry = (pr->reg[op.args[2].reg_num] == 0) ? 1 : 0;
	}
	if (g_flag_v == 1)
		ft_printf("P%5d | %s r%d r%d r%d\n", pr->pr_id, op.name,\
		op.args[0].reg_num + 1, op.args[1].reg_num + 1, op.args[2].reg_num + 1);
	handle_position(pr, 1);
}
