/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 20:22:48 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/07 20:22:51 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int		check_st_codage(uint32_t codage)
{
	if (codage == RI || codage == RR)
		return (0);
	return (1);
}

void	op_st(t_pr *pr, t_op op, uint32_t codage)
{
	if (check_st_codage(codage) == 0 && pr->reg_err == 0)
	{
		if (op.args[1].tp == IND_CODE)
		{
			op.args[1].value %= IDX_MOD;
			handle_position(pr, op.args[1].value);
			g_vm->map[pr->cur_pos] = op.args[0].value;
		}
		if (op.args[1].tp == REG_CODE)
			pr->reg[op.args[1].reg_num] = op.args[0].value;
	}
	handle_position(pr, 1);
}