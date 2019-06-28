/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:08:14 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 13:34:47 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

int		check_lldi_codage(uint32_t codage)
{
	if (codage == RDR || codage == RRR || codage == DDR || codage == DRR\
	|| codage == IDR || codage == IRR)
		return (0);
	return (1);
}

void	op_lldi(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		pos;

	if (check_lldi_codage(codage) == 0 && pr->reg_err == 0)
	{
		if (op.args[0].tp == IND_CODE)
		{
			pos = pr->prev_pos + (op.args[0].value % IDX_MOD);
			op.args[0].value = read_bytes(pos);
		}
		pos = pr->prev_pos + op.args[0].value + op.args[1].value;
		pr->reg[op.args[2].reg_num] = read_bytes(pos);
		pr->carry = (pr->reg[op.args[2].reg_num] == 0) ? 1 : 0;
		if (g_flag_v == 1)
		{
			ft_printf("P%5d | %s %d %d r%d\n", pr->pr_id, op.name, \
			op.args[0].value, op.args[1].value, op.args[2].reg_num + 1);
			ft_printf(OP_LLDI, op.args[0].value, op.args[1].value,\
			op.args[0].value + op.args[1].value, pos);
		}
	}
	handle_position(pr, 1);
}
