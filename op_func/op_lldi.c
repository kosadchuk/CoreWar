/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:08:14 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/08 17:08:16 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int 	check_lldi_codage(uint32_t codage)
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
			pos = op.args[0].value % IDX_MOD;
			handle_position(pr, pos);
			op.args[0].value = bytes_in_int(pr, 4);
		}
		pos = (op.args[0].value + op.args[1].value);
		handle_position(pr, pos);
		pr->reg[op.args[2].reg_num] = bytes_in_int(pr, 4);
		pr->carry = (pr->reg[op.args[2].reg_num] == 0) ? 1 : 0;
	}
	handle_position(pr, 1);
}