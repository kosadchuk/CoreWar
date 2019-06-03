/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_war.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 21:29:06 by kosadchu          #+#    #+#             */
/*   Updated: 2019/05/31 21:29:10 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/core.h"

//void	show_elements(t_list_elem *elem)
//{
//	ft_printf("id = %d\n", ((t_kar *)elem->content)->parent_id);
//	ft_printf("cp = %d\n", ((t_kar *)elem->content)->cur_pos);
//	ft_printf("code = %.2x\n", g_vm->map[((t_kar *)elem->content)->cur_pos]);
//}

void 	*init_start_positions(t_list *list) // создаем первые каретки и делаем двусвязный список
{
	t_prcs	prcs;
	int 	i;
	int 	place;

	i = 0;
	place = 0;
	ft_lstinit(list, NULL);
	while (i < g_players->len)
	{
		prcs.parent_id = i + 1;
		prcs.cur_pos = place;
		prcs.reg[0] = (i + 1) * -1;
		ft_lstpush_back(list, ft_lstnew(&prcs, sizeof(t_prcs)));
		i++;
		place += MEM_SIZE / g_players->len;
	}
	g_vm->last_alive = g_players->team[i];
	return (list);
}

//void 	make_op(t_prcs *k)
//{
//	if (k->cur_op >= 1 && k->cur_op <= 16)
//	{
//		valid_args();
//	}
//	else
//	{
//		if (k->cur_pos + 1 >= MEM_SIZE)
//			k->cur_pos = k->cur_pos % MEM_SIZE;
//		else
//			k->cur_pos++;
//	}
//}

void	pars_process(t_list_elem *prcs)
{
	t_prcs	*pr;

	pr = (t_prcs *)prcs->content;
	pr->cur_op = g_vm->map[pr->cur_pos];
	pr->cycle_count = (pr->cur_op < 1 || pr->cur_op > 16)\
	? 0 : g_op_tab[pr->cur_op].cycles;
	(pr->cycle_count > 0) ? pr->cycle_count-- : 0;
//	if (k->cycle_count == 0)
//		make_op(k);

//	ft_printf("cycles %d\n", g_ops->ops[k->cur_op]->cycles);
}

void	start_cycles(t_list *list)
{
	while (1)
	{
		ft_lstiter(list, &pars_process); // ф-я итерируется по всему списку кареток и к каждой применяет функцию pars_process
		g_vm->cycles++;
		if (g_vm->cycles == 1) // условие выхода будет другое
			break ;
	}
}

void	start_war(void)
{
	t_list	list;

	init_start_positions(&list); // для кареток
	start_cycles(&list); // выполняем основной цикл
//	ft_lstiter(&list, &show_elements);
//	for (int i = 0; i < 16; ++i) {
//		ft_printf("op_name = %s\n", g_op_tab[i].name);
//	}
}