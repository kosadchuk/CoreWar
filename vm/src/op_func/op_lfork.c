/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:10:54 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 13:34:31 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

void	op_lfork(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		pos;

	pos = bytes_in_int(pr, op.lable_size);
	if (g_flag_v == 1)
		ft_printf("P%5d | %s %d ", pr->pr_id, op.name, pos);
	pos = pos + pr->prev_pos;
	if (g_flag_v == 1)
		ft_printf("(%d)\n", pos);
	copy_prcs(pr, pos);
	handle_position(pr, 1);
}
