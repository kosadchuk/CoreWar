/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarchen <kmarchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:01:29 by kmarchen          #+#    #+#             */
/*   Updated: 2019/06/30 16:27:07 by kmarchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/visualization.h"

void	setup_windows(void)
{
	g_vm->visual->arena = newwin(ARENA_HEIGHT + 2,
		ARENA_WIDTH + 3, 1, 2);
	g_vm->visual->state = newwin(STATE_HEIGHT + 2,
		STATE_WIDTH, 1, ARENA_WIDTH + 8);
}

void	setup_visual(void)
{
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	use_default_colors();
	start_color();
	init_colors();
	setup_windows();
	fill_arena();
}

static	void	process_keys(void)
{
	if (g_vm->visual->key == KEY_SPACE)
		g_vm->visual->paused = (g_vm->visual->paused ? 0 : 1);
}

// static	void	exec_cycle_vs(t_vm *vm)
// {
// 	size_t cursors_num;

// 	if (vm->cursors_num)
// 	{
// 		exec_cycle(vm);
// 		if (vm->cycles_to_die == vm->cycles_after_check
// 			|| vm->cycles_to_die <= 0)
// 		{
// 			cursors_num = vm->cursors_num;
// 			cycles_to_die_check(vm);
// 			if (cursors_num != vm->cursors_num && vm->cursors_num)
// 				play_death_sound(vm);
// 		}
// 		if (!vm->cursors_num)
// 		{
// 			play_victory_sound(vm);
// 			vm->vs->is_running = false;
// 		}
// 	}
// }

// void	start_war(void)
// {
// 	init_start_positions();
// 	while (1)
// 	{
// 		(g_flag_v2 == 1) ? ft_printf("It is now cycle %d\n", g_vm->cycles) : 0;
// 		ft_lstiter(&g_list, &pars_process);
// 		((g_vm->cycles == g_dump && g_dump_flag == 1) ||\
// 		(g_vm->cycles - 1 == 0 && g_dump_flag == 1)) ? print_dump() : 0;
// 		if (g_vm->ctd <= 0 || g_list.list_size == 0)
// 		{
// 			kill_all_processes();
// 			if (g_dump_flag == 0)
// 				ft_printf(WINNER, g_vm->last_alive->id, g_vm->last_alive->name);
// 			break ;
// 		}
// 		g_vm->check_cycle--;
// 		if (g_vm->check_cycle == 0)
// 			check();
// 		g_vm->cycles++;
// 	}
// }


void		exec_vs(void)
{
	setup_visual();
	while ((g_vm->visual->key = getch()) != KEY_ESC)
	{
		process_keys();
		if (!g_vm->visual->paused && (clock() >= get_delay()))
		{
			g_vm->visual->time = clock();
			// exec_cycle_vs(vm);
		}
		render();
	}
	// free_vs(&(vm->vs));
}
