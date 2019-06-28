/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:13:35 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/05 17:13:37 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int		check_ld_codage(uint32_t codage)
{
	if (codage == DR || codage == IR)
		return (0);
	return (1);
}

void	op_ld(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		pos;

	if (check_ld_codage(codage) == 0 && pr->reg_err == 0)
	{
		if (op.args[0].tp == DIR_CODE)
			pr->reg[op.args[1].reg_num] = op.args[0].value;
		else if (op.args[0].tp == IND_CODE)
		{
			op.args[0].value %= IDX_MOD;
			pos = pr->prev_pos + (op.args[0].value % IDX_MOD);
			op.args[0].value = read_bytes(pos);
			pr->reg[op.args[1].reg_num] = op.args[0].value;
		}
		if (g_flag_v == 1)
			ft_printf("P%5d | %s %d r%d\n", pr->pr_id, op.name,\
			op.args[0].value, op.args[1].reg_num + 1);
		pr->carry = (pr->reg[op.args[1].reg_num] == 0) ? 1 : 0;
	}
	handle_position(pr, 1);
}
