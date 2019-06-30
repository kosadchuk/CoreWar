/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarchen <kmarchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:01:08 by kmarchen          #+#    #+#             */
/*   Updated: 2019/06/30 16:01:09 by kmarchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/visualization.h"

void	init_colors(void)
{
	init_color(COLOR_GRAY, 355, 355, 355);
	init_color(LIGHT_RED, 700, 0, 0);
	init_color(DARK_RED, 255, 0, 0);
	init_color(LIGHT_GREEN, 0, 700, 0);
	init_color(DARK_GREEN, 0, 255, 0);
	init_pair(STATE_PAUSED, LIGHT_RED, DARK_RED);
	init_pair(STATE_RUNNING, LIGHT_GREEN, DARK_GREEN);
	init_pair(GRAY, COLOR_GRAY, COLOR_BLACK);
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(GRAY_CURSOR, COLOR_BLACK, COLOR_GRAY);
	init_pair(RED_CURSOR, COLOR_BLACK, COLOR_RED);
	init_pair(GREEN_CURSOR, COLOR_BLACK, COLOR_GREEN);
	init_pair(BLUE_CURSOR, COLOR_BLACK, COLOR_BLUE);
	init_pair(MAGENTA_CURSOR, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(RED_LIVE, COLOR_WHITE, COLOR_RED);
	init_pair(GREEN_LIVE, COLOR_WHITE, COLOR_GREEN);
	init_pair(BLUE_LIVE, COLOR_WHITE, COLOR_BLUE);
	init_pair(MAGENTA_LIVE, COLOR_WHITE, COLOR_MAGENTA);
}

int		get_player_color(int32_t index, int32_t type)
{
	if (type == PLAYER_COLOR)
		return (g_player_colors[index]);
	else if (type == PLAYER_CURSOR)
		return (g_player_cursors[index]);
	else if (type == PLAYER_LIVE)
		return (g_player_lives[index]);
	return (-1);
}
