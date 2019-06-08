/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:33:08 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/08 12:33:10 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	op_sub(t_pr *pr, t_op op, uint32_t codage)
{
	if (codage == RRR && pr->reg_err == 0)
	{
		pr->reg[op.args[2].reg_num] = pr->reg[op.args[0].reg_num]\
		- pr->reg[op.args[1].reg_num];
		pr->carry = (pr->reg[op.args[2].reg_num] == 0) ? 1 : 0;
	}
	handle_position(pr, 1);
}