/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 17:48:09 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 13:33:44 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

void	check_op(t_prcs *pr)
{
	pr->prev_pos = pr->cur_pos;
	if (g_op_tab[pr->cur_op].codage == 0)
		g_op_tab[pr->cur_op].f(pr, g_op_tab[pr->cur_op], 0);
	else
		valid_op_args(pr);
}

void	pars_process(t_list_elem *prcs)
{
	t_prcs	*pr;

	pr = (t_prcs *)prcs->content;
	if (pr->cycle_count > 0)
		pr->cycle_count--;
	if (pr->cycle_count == 0)
	{
		if (pr->cur_op < 1 || pr->cur_op > 16)
		{
			pr->cur_op = g_vm->map[pr->cur_pos];
			if (pr->cur_op < 1 || pr->cur_op > 16)
				pr->cur_op = 0;
			pr->cycle_count = (pr->cur_op < 1 || pr->cur_op > 16)\
			? 0 : g_op_tab[pr->cur_op].cycles - 1;
		}
		if (pr->cycle_count == 0 && pr->cur_op > 0 && pr->cur_op < 17)
		{
			check_op(pr);
			pr->cur_op = 0;
		}
		else if (pr->cycle_count == 0 && (pr->cur_op < 1 || pr->cur_op > 16))
			handle_position(pr, 1);
	}
}
