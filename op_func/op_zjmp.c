/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 14:21:02 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/08 14:21:04 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	op_zjmp(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		step;

	step = bytes_in_int(pr, op.lable_size);
	if (pr->carry == 1)
	{
		step %= IDX_MOD;
		handle_position(pr, step);
	}
	handle_position(pr, 1);
}