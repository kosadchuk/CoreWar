/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:35:41 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/08 12:35:43 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int 	check_and_codage(uint32_t codage)
{
	if (codage == RRR || codage == RIR || codage == RDR\
	|| codage == DRR || codage == DIR || codage == DDR\
	|| codage == IRR || codage == IIR || codage == IDR)
		return (0);
	return (1);
}

void	op_and(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		value;

	if (check_and_codage(codage) == 0 && pr->reg_err == 0)
	{
		value = op.args[0].value & op.args[1].value;
		pr->reg[op.args[2].reg_num] = value;
		pr->carry = (pr->reg[op.args[2].reg_num] == 0) ? 1 : 0;
	}
	handle_position(pr, 1);
}