/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_war.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 21:29:06 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 21:35:39 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

void	change_cycles_to_die(void)
{
	int		i;

	i = -1;
	g_vm->ctd -= CYCLE_DELTA;
	g_vm->prev_ctd = g_vm->ctd;
	g_vm->checks = 0;
	if (g_flag_v2 == 1)
		ft_printf("Cycle to die is now %d\n", g_vm->ctd);
	while (++i < g_players->len)
		g_players->team[i]->lives_in_cur = 0;
}

void	kill_all_processes(void)
{
	t_list_elem		*tmp;

	tmp = g_list.start;
	while (tmp && tmp->next)
	{
		ft_lstdel_by_obj(&g_list, tmp);
		tmp = tmp->next;
	}
}

void	delete_dead_process(void)
{
	t_list_elem		*tmp;
	t_list_elem		*tmp_2;

	tmp = g_list.start;
	while (tmp)
	{
		if (g_vm->cycles - ((t_prcs*)tmp->content)->last_live_cycle\
		>= g_vm->ctd)
		{
			if (g_flag_v3 == 1)
				ft_printf(DEAD, g_vm->cycles, ((t_prcs*)tmp->content)->pr_id,\
				g_vm->cycles - ((t_prcs*)tmp->content)->last_live_cycle,\
				g_vm->ctd);
			tmp_2 = tmp->next;
			ft_lstdel_by_obj(&g_list, tmp);
			tmp = tmp_2;
			continue ;
		}
		tmp = tmp->next;
	}
}

void	main_cycle(void)
{
	while (1)
	{
		(g_flag_v2 == 1) ? ft_printf("It is now cycle %d\n", g_vm->cycles) : 0;
		ft_lstiter(&g_list, &pars_process);
		if (g_vm->cycles == g_dump && g_flag_v == 0 && g_dump > 0)
			print_dump();
		if (g_vm->ctd <= 0 || g_list.list_size == 0)
		{
			kill_all_processes();
            // WARNING
            getchar();
            endwin();
            // WARNING
			ft_printf(WINNER, g_vm->last_alive->id, g_vm->last_alive->name);
			break ;
		}
		g_vm->check_cycle--;
		if (g_vm->check_cycle == 0)
		{
			delete_dead_process();
			if (g_vm->count_live_op >= NBR_LIVE || (g_vm->checks == MAX_CHECKS\
			&& g_vm->prev_ctd == g_vm->ctd))
				change_cycles_to_die();
			g_vm->count_live_op = 0;
			g_vm->check_cycle = g_vm->ctd;
			g_vm->checks++;
		}
		g_vm->cycles++;
        // WARNING
        render();     
	}
}

void	start_war(void)
{
	init_start_positions();

    // WARNING
    g_vm->visual = init_visual();
    setup_visual();
    // WARNING

	main_cycle();
}
