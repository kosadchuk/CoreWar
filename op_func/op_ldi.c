/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:03:08 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/08 15:03:11 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int 	check_ldi_codage(uint32_t codage)
{
	if (codage == RDR || codage == RRR || codage == DDR || codage == DRR\
	|| codage == IDR || codage == IRR)
		return (0);
	return (1);
}

void	op_ldi(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		pos;

	if (check_ldi_codage(codage) == 0 && pr->reg_err == 0)
	{
		if (op.args[0].tp == IND_CODE)
		{
			pos = op.args[0].value % IDX_MOD;
			handle_position(pr, pos);
			op.args[0].value = bytes_in_int(pr, 4);
		}
		pos = (op.args[0].value + op.args[1].value) % IDX_MOD;
		handle_position(pr, pos);
		pr->reg[op.args[2].reg_num] = bytes_in_int(pr, 4);
	}
	handle_position(pr, 1);
}