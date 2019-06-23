/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 14:18:48 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/08 14:18:50 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int		check_xor_codage(uint32_t codage)
{
	if (codage == RRR || codage == RIR || codage == RDR\
	|| codage == IRR || codage == IIR || codage == IDR\
	|| codage == DRR || codage == DIR || codage == DDR)
		return (0);
	return (1);
}

void	op_xor(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		pos;
	int32_t		value;

	if (check_xor_codage(codage) == 0 && pr->reg_err == 0)
	{
		if (op.args[0].tp == IND_CODE)
		{
			op.args[0].value %= IDX_MOD;
			pos = pr->prev_pos + (op.args[0].value % IDX_MOD);
			op.args[0].value = read_bytes(pos);
		}
		if (op.args[1].tp == IND_CODE)
		{
			op.args[1].value %= IDX_MOD;
			pos = pr->prev_pos + (op.args[1].value % IDX_MOD);
			op.args[0].value = read_bytes(pos);
		}
		value = op.args[0].value ^ op.args[1].value;
		if (g_flag_v == 1)
			ft_printf("P%5d | %s %d %d r%d\n", pr->pr_id, op.name,\
			op.args[0].value, op.args[1].value, op.args[2].reg_num + 1);
		pr->reg[op.args[2].reg_num] = value;
		pr->carry = (pr->reg[op.args[2].reg_num] == 0) ? 1 : 0;
	}
	handle_position(pr, 1);
}
