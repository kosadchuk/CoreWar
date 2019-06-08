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

int 	check_ld_codage(uint32_t codage)
{
	if (codage == DR || codage == IR)
		return (0);
	return (1);
}

void	op_ld(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		value;

	if (check_ld_codage(codage) == 0 && pr->reg_err == 0)
	{
		if (op.args[0].tp == DIR_CODE)
			pr->reg[op.args[1].reg_num] = op.args[0].value;
		if (op.args[0].tp == IND_CODE)
		{
			op.args[0].value %= IDX_MOD;
			handle_position(pr, op.args[0].value);
			value = bytes_in_int(pr, 4);
			pr->reg[op.args[1].reg_num] = value;
		}
		pr->carry = (pr->reg[op.args[1].reg_num] == 0) ? 1 : 0;
	}
	handle_position(pr, 1);
}

//void	op_ld(t_pr *pr, t_op op, uint32_t codage)
//{
//	int32_t		arg1;
//	int32_t		arg2;
//	int32_t		value;
//
//	arg1 = bytes_in_int(pr, op.args[0].sz);
//	arg2 = bytes_in_int(pr, op.args[1].sz);
//	if (check_ld_codage(codage) == 0 && arg2 >= 0 && arg2 <= 15)
//	{
//		if (op.args[0].tp == DIR_CODE)
//			pr->reg[arg2] = (int)arg1;
//		if (op.args[0].tp == IND_CODE)
//		{
//			arg1 %= IDX_MOD;
//			handle_position(pr, arg1);
//			value = bytes_in_int(pr, 4);
//			pr->reg[arg2] = value;
//		}
//		pr->carry = (pr->reg[arg2] == 0) ? 1 : 0;
//	}
//	handle_position(pr, 1);
//}