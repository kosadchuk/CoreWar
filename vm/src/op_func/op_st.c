/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 20:22:48 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 13:34:57 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

int		check_st_codage(uint32_t codage)
{
	if (codage == RI || codage == RR)
		return (0);
	return (1);
}

// inline static void	vs_st(t_pr *pr, int32_t addr)
// {
// 	if (g_vm->visual)
// 		update_map(cursor, cursor->pc + (addr % IDX_MOD), DIR_SIZE);
// }

static void	write_vs_map(int32_t player, int32_t pos)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		if (pos >= MEM_SIZE)
			pos = pos % MEM_SIZE;
		else if (pos < 0)
			pos = pos + MEM_SIZE;
		g_vm->visual->data[pos].color = get_player_color(player);
		pos++;
	}
}

void	op_st(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		pos;
	uint8_t		buf[4];

	if (check_st_codage(codage) == 0 && pr->reg_err == 0)
	{
		if (g_flag_v == 1)
			ft_printf("P%5d | %s r%d %d\n", pr->pr_id, op.name,\
			op.args[0].reg_num + 1, op.args[1].value);
		if (op.args[1].tp == REG_CODE)
		{
			pr->reg[op.args[1].reg_num] = op.args[0].value;
		}
		else if (op.args[1].tp == IND_CODE)
		{
			op.args[1].value %= IDX_MOD;
			pos = pr->prev_pos + (op.args[1].value % IDX_MOD);
			int_to_byte(op.args[0].value, buf);
			write_in_map(pos, buf);
			write_vs_map(pr->parent_id - 1, pos);
			// printf("pos -> %d\n", pos);
		}
	}
	handle_position(pr, 1);
}
