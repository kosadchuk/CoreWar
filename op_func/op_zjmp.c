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
	int32_t		value;

	if (pr->carry == 1)
	{
		value = bytes_in_int(pr, op.lable_size);
		value %= IDX_MOD;
//		ft_printf("%d\n", value);
		pr->cur_pos = pr->prev_pos;
		handle_position(pr, value);
	}
}