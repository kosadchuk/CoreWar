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
//	ft_printf("%d ", pos);
	pos = (pos % IDX_MOD) + pr->prev_pos;
//	ft_printf("(%d)\n", pos);
//	ft_printf("	op num [%d]\n", g_vm->map[pos]);
	copy_prcs(pr, pos);
	handle_position(pr, 1);
}
