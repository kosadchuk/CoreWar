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

void	print_dump(void)
{
	int		i;
	int		num;

	i = -1;
	num = 0;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0)
		{
			ft_printf("\n");
			num = i;
			if (i == num)
			{
				if (num == 0)
					ft_printf("0x0000 : ");
				else
					ft_printf("%#.4x : ", num);
			}
		}
		else
			ft_printf("%.2x ", g_vm->map[i]);
	}
}

void	delete_dead_process(void)
{
	t_list_elem		*tmp;

	tmp = g_list.start;
	while (tmp)
	{
		if (g_vm->cycles - ((t_prcs*)tmp->content)->last_live_cycle\
		>= g_vm->ctd)
			ft_lstdel_by_obj(&g_list, tmp);
		tmp = tmp->next;
	}
}

void	change_cycles_to_die(void)
{
	int		i;

	i = -1;
	g_vm->ctd -= CYCLE_DELTA;
	while (++i < g_players->len)
		g_players->team[i]->lives_in_cur = 0;
	g_vm->prev_ctd = g_vm->ctd;
	g_vm->count_live_op = 0;
	g_vm->checks = 0;
}

void	main_cycle(void)
{
	while (1)
	{
		ft_lstiter(&g_list, &pars_process);
		(g_vm->cycles == g_dump) ? print_dump() : 0;
		if (g_vm->ctd <= 0 || g_list.list_size == 0)
		{
			delete_dead_process();
			ft_printf("Winner %s!\n", g_vm->last_alive->name);
			break ;
		}
		if (g_vm->check_cycle == g_vm->ctd)
		{
			g_vm->check_cycle = 0;
			delete_dead_process();
			if (g_vm->count_live_op >= NBR_LIVE)
				change_cycles_to_die();
			if (g_vm->checks == MAX_CHECKS && g_vm->prev_ctd == g_vm->ctd)
				change_cycles_to_die();
			g_vm->checks++;
		}
		g_vm->cycles++;
		g_vm->check_cycle++;
	}
}

void	start_war(void)
{
	init_start_positions(); // для кареток
	main_cycle(); // выполняем основной цикл
}
