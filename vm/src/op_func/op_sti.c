/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:37:40 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 13:35:01 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

int		check_sti_codage(uint32_t codage)
{
	if (codage == RRD || codage == RDD || codage == RID\
	|| codage == RRR || codage == RDR || codage == RIR)
		return (0);
	return (1);
}

static void write_vs_map(int32_t player, int32_t pos)
{
    int     i;

    i = -1;
    while (++i < 4)
    {
        g_vm->visual->data[calc_addr(pos)].color = get_player_color(player, PLAYER_COLOR);
        pos++;
    }
}

void	op_sti(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		pos;
	uint8_t		buf[4];

	if (check_sti_codage(codage) == 0 && pr->reg_err == 0)
	{
		if (op.args[1].tp == IND_CODE)
		{
			op.args[0].value %= IDX_MOD;
			pos = pr->prev_pos + (op.args[1].value % IDX_MOD);
			op.args[1].value = read_bytes(pos);
		}
		pos = pr->prev_pos + ((op.args[1].value + op.args[2].value) % IDX_MOD);
		if (g_flag_v == 1)
			ft_printf(OP_STI2, pr->pr_id, op.name, op.args[0].reg_num + 1,\
			op.args[1].value, op.args[2].value, op.args[1].value,\
			op.args[2].value, op.args[1].value + op.args[2].value, pos);
		int_to_byte(op.args[0].value, buf);
		write_in_map(pos, buf);
        write_vs_map(pr->parent_id - 1, pos);
	}
	handle_position(pr, 1);
}
