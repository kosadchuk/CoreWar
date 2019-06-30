/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarchen <kmarchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:01:29 by kmarchen          #+#    #+#             */
/*   Updated: 2019/06/30 17:43:10 by kmarchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/visualization.h"

void		setup_windows(void)
{
	g_vm->visual->arena = newwin(ARENA_HEIGHT + 2,
		ARENA_WIDTH + 3, 1, 2);
	g_vm->visual->state = newwin(STATE_HEIGHT + 2,
		STATE_WIDTH, 1, ARENA_WIDTH + 8);
}

void		setup_visual(void)
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

static void	process_keys(void)
{
	if (g_vm->visual->key == KEY_SPACE)
		g_vm->visual->paused = (g_vm->visual->paused ? 0 : 1);
	else if (g_vm->visual->key == KEY_SPEED_PLUS_1)
		g_vm->visual->speed += 1;
	else if (g_vm->visual->key == KEY_SPEED_PLUS_10)
		g_vm->visual->speed += 10;
	else if (g_vm->visual->key == KEY_SPEED_PLUS_100)
		g_vm->visual->speed += 100;
	else if (g_vm->visual->key == KEY_SPEED_MINUS_1)
		g_vm->visual->speed -= 1;
	else if (g_vm->visual->key == KEY_SPEED_MINUS_10)
		g_vm->visual->speed -= 10;
	else if (g_vm->visual->key == KEY_SPEED_MINUS_100)
		g_vm->visual->speed -= 100;
}

void		process_war(void)
{
	ft_lstiter(&g_list, &pars_process);
	if (g_vm->ctd <= 0 || g_list.list_size == 0)
	{
		g_vm->visual->paused = 1;
		kill_all_processes();
		render();
		return ;
	}
	g_vm->check_cycle--;
	if (g_vm->check_cycle == 0)
		check();
	g_vm->cycles++;
}

void		start_war_vs(void)
{
	init_start_positions();
	g_vm->visual = init_visual();
	setup_visual();
	while ((g_vm->visual->key = getch()) != KEY_ESC)
	{
		process_keys();
		if (g_vm->ctd <= 0 || g_list.list_size == 0)
			g_vm->visual->paused = 1;
		if (g_vm->visual->speed <= 0)
			g_vm->visual->speed = 1;
		if (g_vm->visual->speed > 1000)
			g_vm->visual->speed = 1000;
		if (!g_vm->visual->paused && (clock() >= get_delay()))
		{
			g_vm->visual->offset = clock();
			process_war();
		}
		render();
	}
	finish_vs();
}
