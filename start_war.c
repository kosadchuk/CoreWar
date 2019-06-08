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

void	take_args_value(t_op *op, t_prcs *pr)
{
	int		i;
	int32_t	reg_num;

	i = -1;
	pr->reg_err = 0;
	while (++i < 3)
	{
		if (op->args[i].tp == REG_CODE)
		{
			op->args[i].sz = 1;
			reg_num = bytes_in_int(pr, op->args[i].sz);
			if (reg_num >= 0 && reg_num <= 15)
			{
				op->args[i].value = pr->reg[reg_num];
				op->args[i].reg_num = reg_num;
			}
			else
				pr->reg_err = 1;
		}
		if (op->args[i].tp == DIR_CODE)
		{
			op->args[i].sz = op->lable_size;
			op->args[i].value = bytes_in_int(pr, op->args[i].sz);
		}
		if (op->args[i].tp == IND_CODE)
		{
			op->args[i].sz = IND_SIZE;
			op->args[i].value = bytes_in_int(pr, op->args[i].sz);
		}
	}
}

void	valid_op_args(t_prcs *pr)
{
	uint32_t	codage;

	handle_position(pr, 1);
	codage = (unsigned char)g_vm->map[pr->cur_pos];
	g_op_tab[pr->cur_op].args[0].tp = (codage & 0b11000000) >> 6;
	g_op_tab[pr->cur_op].args[1].tp = (codage & 0b00110000) >> 4;
	g_op_tab[pr->cur_op].args[2].tp = (codage & 0b00001100) >> 2;
	take_args_value(&g_op_tab[pr->cur_op], pr);
//	printf("arg %d  sz %d val %d reg_num %d\n", g_op_tab[pr->cur_op].args[0].tp, g_op_tab[pr->cur_op].args[0].sz,\
//	g_op_tab[pr->cur_op].args[0].value, g_op_tab[pr->cur_op].args[0].reg_num);
//	printf("arg %d  sz %d val %d reg_num %d\n", g_op_tab[pr->cur_op].args[1].tp, g_op_tab[pr->cur_op].args[1].sz,\
//	g_op_tab[pr->cur_op].args[0].value, g_op_tab[pr->cur_op].args[1].reg_num);
//	printf("arg %d  sz %d val %d reg_num %d\n", g_op_tab[pr->cur_op].args[2].tp, g_op_tab[pr->cur_op].args[2].sz,\
//	g_op_tab[pr->cur_op].args[0].value, g_op_tab[pr->cur_op].args[2].reg_num);
	g_op_tab[pr->cur_op].f(pr, g_op_tab[pr->cur_op], codage);
}

void 	check_op(t_prcs *pr)
{
	if (g_op_tab[pr->cur_op].codage == 0)
		g_op_tab[pr->cur_op].f(pr, g_op_tab[pr->cur_op], 0);
	else
		valid_op_args(pr);
}

void	pars_process(t_list_elem *prcs)
{
	t_prcs	*pr;

	pr = (t_prcs *)prcs->content;
	if (pr->cycle_count == 0)
	{
		pr->cur_op = g_vm->map[pr->cur_pos];
		pr->cycle_count = ((pr->cur_op < 1 || pr->cur_op > 16))\
		? 0 : g_op_tab[pr->cur_op].cycles;
	}
	(pr->cycle_count > 0) ? pr->cycle_count-- : 0;
	if (pr->cycle_count == 0 && pr->cur_op > 0 && pr->cur_op < 17)
		check_op(pr);
	else if (pr->cycle_count == 0 && (pr->cur_op < 1 || pr->cur_op > 16))
		handle_position(pr, 1);
}

t_list_elem	*take_dead_prcs(t_list_elem *start)
{
	while (start)
	{
		if (g_vm->cycles - ((t_prcs*)start->content)->last_live_cycle\
		>=g_vm->cycles_to_die)
			return (start);
		start = start->next;
	}
	return (NULL);
}

void	start_cycles(void)
{
	t_list_elem		*del;

	while (1)
	{
		ft_lstiter(list, &pars_process); // ф-я итерируется по всему списку кареток и к каждой применяет функцию pars_process
		g_vm->cycles++;
		g_vm->check_cycle++;
		if (g_vm->cycles_to_die <= 0)
		{
			printf("hana vsem\n");
		}
		if (g_vm->check_cycle == g_vm->cycles_to_die)
		{
			g_vm->check_cycle = 0;
			g_vm->checks++;
			if (g_vm->count_live_op >= NBR_LIVE)
			{
				g_vm->cycles_to_die -= CYCLE_DELTA;
				g_vm->checks = 0;
			}
			if (g_vm->checks == MAX_CHECKS && g_vm->prev_cycle_to_die == g_vm->cycles_to_die)
			{
				g_vm->cycles_to_die -= CYCLE_DELTA;
				g_vm->prev_cycle_to_die = g_vm->cycles_to_die;
				g_vm->checks = 0;
			}
			g_vm->count_live_op = 0;
			while ((del = take_dead_prcs(list->start)) != NULL)
				ft_lstdel_by_obj(list, del);
		}
		if (g_vm->cycles == 10000)
//		if (list->start == NULL)
			break ;
	}
}

//void  mem_print(t_list list)
//{
//	int  i;
//
//	i = -1;
//
//	int f;
//
//	while (++i < 4096)
//	{
//		f = 0;
//		if (i % 64 == 0)
//			ft_printf("\n");
//		for (int j = 0; j < list.list_size; ++j)
//			if (((t_prcs*)list.start)->cur_pos - (int)g_vm->map == i)
//			{
//				ft_printf("\033[01;31m%.2x \e[0m", g_vm->map[i]);
//				f = 1;
//				list.start = list.start->next;
//			}
//		if (f)
//			continue;
//		ft_printf("%.2x ", g_vm->map[i]);
//	}
//}

void	start_war(void)
{
	init_start_positions(); // для кареток
	start_cycles(&g_list); // выполняем основной цикл
//	mem_print(list);
//	ft_lstiter(&list, &show_elements);
//	for (int i = 0; i < 16; ++i) {
//		ft_printf("op_name = %s\n", g_op_tab[i].name);
//	}
}