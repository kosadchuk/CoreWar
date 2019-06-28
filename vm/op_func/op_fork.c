/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:50:03 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/08 15:50:05 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	op_fork(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		pos;

	pos = bytes_in_int(pr, op.lable_size);
	if (g_flag_v == 1)
		ft_printf("P%5d | %s %d ", pr->pr_id, op.name, pos);
	pos = (pos % IDX_MOD) + pr->prev_pos;
	if (g_flag_v == 1)
		ft_printf("(%d)\n", pos);
	copy_prcs(pr, pos);
	handle_position(pr, 1);
}
