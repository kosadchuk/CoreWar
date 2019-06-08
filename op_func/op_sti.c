/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:37:40 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/08 15:37:42 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int		check_sti_codage(uint32_t codage)
{
	if (codage == RRD || codage == RDD || codage == RID\
	|| codage == RRR || codage == RDR || codage == RIR)
		return (0);
	return (1);
}

void	op_sti(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		pos;

	if (check_sti_codage(codage) == 0 && pr->reg_err == 0)
	{
		if (op.args[1].tp == IND_CODE)
		{
			pos = op.args[1].value % IDX_MOD;
			handle_position(pr, pos);
			op.args[1].value = bytes_in_int(pr, 4);
		}
		pos = (op.args[1].value + op.args[2].value) % IDX_MOD;
		handle_position(pr, pos);
		g_vm->map[pr->cur_pos] = op.args[0].value;
	}
	handle_position(pr, 1);
}
