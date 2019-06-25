/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_args_pars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 17:46:28 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/23 17:46:29 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	take_ind_arg(t_arg *arg, t_prcs *pr)
{
	int32_t	reg_num;

	arg->sz = 1;
	reg_num = bytes_in_int(pr, arg->sz);
	reg_num -= 1;
	if (reg_num >= 0 && reg_num <= 15)
	{
		arg->value = pr->reg[reg_num];
		arg->reg_num = reg_num;
	}
	else
		pr->reg_err = 1;
}

void	take_args_value(t_arg *args, t_prcs *pr)
{
	int		i;

	i = -1;
	pr->reg_err = 0;
	while (++i < g_op_tab[pr->cur_op].types_num)
	{
		if (args[i].tp == REG_CODE)
			take_ind_arg(&args[i], pr);
		if (args[i].tp == DIR_CODE)
		{
			args[i].sz = g_op_tab[pr->cur_op].lable_size;
			args[i].value = bytes_in_int(pr, args[i].sz);
		}
		if (args[i].tp == IND_CODE)
		{
			args[i].sz = IND_SIZE;
			args[i].value = bytes_in_int(pr, args[i].sz);
		}
	}
}

void	valid_op_args(t_prcs *pr)
{
	uint32_t	codage;

	handle_position(pr, 1);
	codage = (unsigned char)g_vm->map[pr->cur_pos];
	g_op_tab[pr->cur_op].args[0].tp = (codage & 0b11000000) >> 6;
	g_op_tab[pr->cur_op].args[1].tp = (codage & 0b00110000) >> 4;
	g_op_tab[pr->cur_op].args[2].tp = (codage & 0b00001100) >> 2;
	take_args_value(&(*g_op_tab[pr->cur_op].args), pr);
	g_op_tab[pr->cur_op].f(pr, g_op_tab[pr->cur_op], codage);
}
