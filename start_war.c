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

//int32_t	read_ind_value(int cur_pos, int step)
//{
//	int32_t		res;
//	uint8_t		buf[4];
//	int			i;
//
//	i = 0;
//	if (cur_pos + step >= MEM_SIZE)
//		cur_pos = (cur_pos + step) % MEM_SIZE;
//	if (cur_pos + step < 0)
//		cur_pos = (cur_pos + step) + MEM_SIZE;
//	else
//		cur_pos += step;
//	while (i < 4)
//	{
//		if (cur_pos >= MEM_SIZE)
//			cur_pos = (cur_pos) % MEM_SIZE;
//		buf[i] = g_vm->map[cur_pos++];
//		i++;
//	}
//	res |= (unsigned char)buf[0] << 24;
//	res |= (unsigned char)buf[1] << 16;
//	res |= (unsigned char)buf[2] << 8;
//	res |= (unsigned char)buf[3];
//	return (res);
//}

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
			reg_num -= 1;
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
//	ft_printf("P  %d | %s ", pr->pr_id, g_op_tab[pr->cur_op].name);
	take_args_value(&g_op_tab[pr->cur_op], pr);
	g_op_tab[pr->cur_op].f(pr, g_op_tab[pr->cur_op], codage);
}

void 	check_op(t_prcs *pr)
{
	if (g_op_tab[pr->cur_op].codage == 0)
	{
//		ft_printf("P  %d | %s ", pr->pr_id, g_op_tab[pr->cur_op].name);
		pr->prev_pos = pr->cur_pos;
		g_op_tab[pr->cur_op].f(pr, g_op_tab[pr->cur_op], 0);
	}
	else
	{
		pr->prev_pos = pr->cur_pos;
		valid_op_args(pr);
	}
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

void	start_cycles(void)
{
	t_list_elem		*tmp;

	while (1)
	{
//				ft_printf("karetki %d\n", g_list.list_size);
		ft_lstiter(&g_list, &pars_process); // ф-я итерируется по всему списку кареток и к каждой применяет функцию pars_process
//		if (g_vm->cycles_to_die <= 0)
//		{
//			tmp = g_list.start;
//			while (tmp)
//			{
//
//								ft_printf("Pr %d hasn't lived for %d cycles (CTD %d)\n", ((t_prcs*)tmp->content)->pr_id,\
//						g_vm->cycles - ((t_prcs*)tmp->content)->last_live_cycle, g_vm->cycles_to_die);
//				ft_lstdel_by_obj(&g_list, tmp);
//				tmp = tmp->next;
//			}
//			ft_printf("\nwhen end cycles Winner %s!\n", g_vm->last_alive->name);
//			break;
//		}
		if (g_vm->cycles == g_dump)
		{
			for (int i = 0; i < MEM_SIZE; ++i)
			{
				if (i % 64 == 0)
					ft_printf("\n");
				else
					ft_printf("%.2x ", g_vm->map[i]);
			}
		}
		if (g_vm->check_cycle - 1 == g_vm->cycles_to_die || g_vm->cycles_to_die <= 0)
		{
			g_vm->check_cycle = 1;
			tmp = g_list.start;
			while (tmp)
			{
				if (g_vm->cycles - ((t_prcs*)tmp->content)->last_live_cycle\
				>= g_vm->cycles_to_die)
				{

//					ft_printf("res %d CTD %d\n", g_vm->cycles - ((t_prcs*)tmp->content)->last_live_cycle, g_vm->cycles_to_die);
//					ft_printf("Pr %d hasn't lived for %d cycles (CTD %d)\n\n", ((t_prcs*)tmp->content)->pr_id,\
					g_vm->cycles - ((t_prcs*)tmp->content)->last_live_cycle, g_vm->cycles_to_die);
					ft_lstdel_by_obj(&g_list, tmp);
				}
				tmp = tmp->next;
			}
			g_vm->checks++;
			if (g_vm->count_live_op >= NBR_LIVE)
			{
				g_vm->cycles_to_die -= CYCLE_DELTA;
//				ft_printf("cycles to die %d\n", g_vm->cycles_to_die);
				for (int i = 0; i < g_players->len; ++i)
				{
					g_players->team[i]->lives_in_cur = 0;
				}
				g_vm->prev_cycle_to_die = g_vm->cycles_to_die;
				g_vm->count_live_op = 0;
				g_vm->checks = 0;
			}
			if (g_vm->checks == MAX_CHECKS && g_vm->prev_cycle_to_die == g_vm->cycles_to_die)
			{
				g_vm->cycles_to_die -= CYCLE_DELTA;
				for (int i = 0; i < g_players->len; ++i)
				{
					g_players->team[i]->lives_in_cur = 0;
				}
				g_vm->prev_cycle_to_die = g_vm->cycles_to_die;
				g_vm->count_live_op = 0;
				g_vm->checks = 0;
			}
			if (g_list.list_size == 0)
			{
				ft_printf("Winner %s!\n", g_vm->last_alive->name);
				break ;
			}
		}
		g_vm->cycles++;
		g_vm->check_cycle++;
//		ft_printf("check cycles %d\n", g_vm->check_cycle);
		ft_printf("It is now cycles %d\n", g_vm->cycles);
	}
		ft_printf("cycles_to_die %d\n", g_vm->cycles_to_die);
//	ft_printf("VSE cycles %d\n", g_vm->cycles);
//	ft_printf("check cycles %d\n", g_vm->check_cycle);
}

void	start_war(void)
{
	init_start_positions(); // для кареток
	start_cycles(); // выполняем основной цикл
}
