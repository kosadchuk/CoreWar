/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:04:06 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/08 17:04:08 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	op_lld(t_pr *pr, t_op op, uint32_t codage)
{
	if ((codage == DR || codage == IR ) && pr->reg_err == 0)
	{
		int32_t		value;

		if (op.args[0].tp == DIR_CODE)
			pr->reg[op.args[1].reg_num] = op.args[0].value;
		if (op.args[0].tp == IND_CODE)
		{
			handle_position(pr, op.args[0].value);
			value = bytes_in_int(pr, 4);
			pr->reg[op.args[1].reg_num] = value;
		}
		pr->carry = (pr->reg[op.args[1].reg_num] == 0) ? 1 : 0;
	}
	handle_position(pr, 1);
}
