/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 21:41:17 by kosadchu          #+#    #+#             */
/*   Updated: 2019/05/30 21:41:19 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/core.h"

void	init_vm(void)
{
	g_vm = ft_memalloc(sizeof(t_vm));
	g_vm->last_alive = 0;
	g_vm->cycles = 0;
	g_vm->cycles_to_die = CYCLE_TO_DIE;
	g_vm->checks = 0;
}

//void init_op_label_size(void)
//{
//	g_ops->ops[0]->lable_size = 0;
//	g_ops->ops[1]->lable_size = 4;
//	g_ops->ops[2]->lable_size = 4;
//	g_ops->ops[3]->lable_size = 4;
//	g_ops->ops[4]->lable_size = 4;
//	g_ops->ops[5]->lable_size = 4;
//	g_ops->ops[6]->lable_size = 4;
//	g_ops->ops[7]->lable_size = 4;
//	g_ops->ops[8]->lable_size = 4;
//	g_ops->ops[9]->lable_size = 2;
//	g_ops->ops[10]->lable_size = 2;
//	g_ops->ops[11]->lable_size = 2;
//	g_ops->ops[12]->lable_size = 2;
//	g_ops->ops[13]->lable_size = 4;
//	g_ops->ops[14]->lable_size = 2;
//	g_ops->ops[15]->lable_size = 2;
//	g_ops->ops[16]->lable_size = 4;
//}
//
//void 	init_op_cycles(void)
//{
//	g_ops->ops[0]->cycles = 0;
//	g_ops->ops[1]->cycles = 10;
//	g_ops->ops[2]->cycles = 5;
//	g_ops->ops[3]->cycles = 5;
//	g_ops->ops[4]->cycles = 10;
//	g_ops->ops[5]->cycles = 10;
//	g_ops->ops[6]->cycles = 6;
//	g_ops->ops[7]->cycles = 6;
//	g_ops->ops[8]->cycles = 6;
//	g_ops->ops[9]->cycles = 20;
//	g_ops->ops[10]->cycles = 25;
//	g_ops->ops[11]->cycles = 25;
//	g_ops->ops[12]->cycles = 800;
//	g_ops->ops[13]->cycles = 10;
//	g_ops->ops[14]->cycles = 50;
//	g_ops->ops[15]->cycles = 1000;
//	g_ops->ops[16]->cycles = 2;
//}
//
//void 	init_ops(void)
//{
//	t_op	*op;
//	int 	i;
//
//	i = 0;
//	g_ops = new_array(17);
//	while (i < 17)
//	{
//		op = ft_memalloc(sizeof(t_op));
//		push_array(g_ops, op);
//		i++;
//	}
//	init_op_cycles();
//	init_op_label_size();
//}

void	make_map(void) // создали карту и разместили по своим позициям байт коды игроков
{
	int 	i;
	int 	id;
	int		place;

	i = 0;
	id = 1;
	place = 0;
	init_vm();
	while (i < g_players->len)
	{
		if (g_players->team[i]->id == id)
		{
			ft_memcpy(&(g_vm->map[place]), g_players->team[i]->code, \
			g_players->team[i]->size);
			id++;
			i = -1;
			place += MEM_SIZE / g_players->len;
		}
		i++;
	}
}
