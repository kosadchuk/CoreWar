/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:10:54 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/08 17:10:56 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	op_lfork(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		pos;

	pos = (op.args[0].value) + pr->cur_pos;
	copy_prcs(pr, pos);
}