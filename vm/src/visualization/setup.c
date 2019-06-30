/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarchen <kmarchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:01:29 by kmarchen          #+#    #+#             */
/*   Updated: 2019/06/30 16:02:48 by kmarchen         ###   ########.fr       */
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
	// render();
}
