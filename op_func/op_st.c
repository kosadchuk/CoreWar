/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 20:22:48 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/09 16:27:17 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int		check_st_codage(uint32_t codage)
{
	if (codage == RI || codage == RR)
		return (0);
	return (1);
}

void	op_st(t_pr *pr, t_op op, uint32_t codage)
{
	int32_t		value;
	uint8_t		buf[4];

//	ft_printf("codage %d\n", codage);
	if (check_st_codage(codage) == 0 && pr->reg_err == 0)
	{
//		ft_printf("r%d ", op.args[0].reg_num + 1);
		if (op.args[1].tp == IND_CODE)
		{
//			op.args[1].value %= IDX_MOD;
//			ft_printf("	IND : %d\n", op.args[1].value);
//			ft_printf("%d\n", op.args[1].value % IDX_MOD);
//			ft_printf("cur %d, prev %d\n", pr->cur_pos, pr->prev_pos);
			handle_position(pr, -4);
			value = pr->cur_pos + (op.args[1].value % IDX_MOD);
//			handle_position(pr, op.args[1].value);
//			ft_printf("	cur pos %d\n", pr->cur_pos);
//			value = pr->cur_pos + op.args[1].value;
//			ft_printf("value size %d\n", op.args[1].sz);
//			int_to_byte(op.args[0].value, &buf);
			int_to_byte(op.args[0].value, &(*buf));
			ft_memcpy(&g_vm->map[value], buf, 4);
//			for (int i = 0; i < 4; ++i)
//			{
//				if (value + 1 >= MEM_SIZE)
//					value = (value + 1) % MEM_SIZE;
//				g_vm->map[value++] = buf[i];
////				value++;
//			}
			//			g_vm->map[value] = op.args[0].value;
			handle_position(pr, 5);
		}
		else if (op.args[1].tp == REG_CODE)
		{
//			ft_printf("reg[%d] %d\n", op.args[1].reg_num, op.args[1].value);
			pr->reg[op.args[1].reg_num] = op.args[0].value;
			handle_position(pr, 1);
		}
	}
}
