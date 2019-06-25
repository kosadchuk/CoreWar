/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 14:07:09 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/08 14:07:11 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int		check_or_codage(uint32_t codage)
{
	if (codage == RRR || codage == RIR || codage == RDR\
	|| codage == IRR || codage == IIR || codage == IDR\
	|| codage == DRR || codage == DIR || codage == DDR)
		return (0);
	return (1);
}

void	op_or(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		value;

	if (check_or_codage(codage) == 0 && pr->reg_err == 0)
	{
		value = op.args[0].value | op.args[1].value;
		pr->reg[op.args[2].reg_num] = value;
		pr->carry = (pr->reg[op.args[2].reg_num] == 0) ? 1 : 0;
	}
	if (g_flag_v == 1)
		ft_printf("P%5d | %s %d %d r%d\n", pr->pr_id, op.name,\
		op.args[0].value, op.args[1].value, op.args[2].reg_num + 1);
	handle_position(pr, 1);
}
