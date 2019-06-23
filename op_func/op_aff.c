/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:13:13 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/08 17:13:15 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

void	op_aff(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		value;

	if (codage == R && pr->reg_err == 0)
	{
		value = op.args[0].value % 256;
		ft_printf("%c\n", value);
	}
	if (g_flag_v == 1)
		ft_printf("P%5d | %s\n", pr->pr_id, op.name);
	handle_position(pr, 1);
}
