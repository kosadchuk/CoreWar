/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarchen <kmarchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 17:42:33 by kmarchen          #+#    #+#             */
/*   Updated: 2019/06/30 17:42:34 by kmarchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZATION_H
# define VISUALIZATION_H

# include <ncurses.h>
# include "core.h"
# include <time.h>

# define CELLS_NUMBER       64
# define ARENA_WIDTH        (CELLS_NUMBER * 3)
# define ARENA_HEIGHT       (MEM_SIZE / CELLS_NUMBER)

# define STATE_WIDTH        60
# define STATE_HEIGHT       ARENA_HEIGHT

# define COLOR_GRAY         8
# define LIGHT_RED			9
# define DARK_RED			10
# define LIGHT_GREEN		11
# define DARK_GREEN			12
# define STATE_PAUSED		13
# define STATE_RUNNING      14
# define GRAY				15
# define RED				16
# define GREEN	    		17
# define BLUE				18
# define MAGENTA	    	19
# define GRAY_CURSOR		20
# define RED_CURSOR			21
# define GREEN_CURSOR		22
# define BLUE_CURSOR		23
# define MAGENTA_CURSOR     24
# define RED_LIVE           25
# define GREEN_LIVE         26
# define BLUE_LIVE          27
# define MAGENTA_LIVE       28

# define PLAYER_COLOR       1
# define PLAYER_CURSOR      2
# define PLAYER_LIVE        3

# define KEY_ESC				27
# define KEY_SPACE				' '
# define KEY_SPEED_PLUS_1		'q'
# define KEY_SPEED_PLUS_10		'w'
# define KEY_SPEED_PLUS_100		'e'
# define KEY_SPEED_MINUS_1		'a'
# define KEY_SPEED_MINUS_10		's'
# define KEY_SPEED_MINUS_100	'd'

typedef struct		s_visualization
{
	int				key;
	clock_t			offset;
	int				speed;
	int				paused;
	WINDOW			*arena;
	WINDOW			*state;
	int				data[MEM_SIZE];
	int				cursors[MEM_SIZE];
}					t_visualization;

t_visualization		*init_visual(void);

void				setup_visual(void);
void				init_colors(void);
int					get_player_color(int32_t index, int32_t type);

void				fill_arena(void);
void				fill_cursors(void);
void				fill_map(int32_t player, int32_t pos, int32_t size);
void				fill_player(int32_t player, int32_t pos, int32_t size);

void				render_arena(void);
void				render_cursors(void);
void				render_state(void);
void				render_players(void);
void				render_status(void);
void				render_state(void);
void				render_winner(void);
void				render(void);

int32_t				correct_pos(int32_t pos);
clock_t				get_delay(void);

void				start_war_vs(void);
void				finish_vs(void);

static int g_player_colors[4] = {
	COLOR_PAIR(RED),
	COLOR_PAIR(GREEN),
	COLOR_PAIR(BLUE),
	COLOR_PAIR(MAGENTA)
};

static int g_player_cursors[4] = {
	COLOR_PAIR(RED_CURSOR),
	COLOR_PAIR(GREEN_CURSOR),
	COLOR_PAIR(BLUE_CURSOR),
	COLOR_PAIR(MAGENTA_CURSOR)
};

static int g_player_lives[4] = {
	COLOR_PAIR(RED_LIVE),
	COLOR_PAIR(GREEN_LIVE),
	COLOR_PAIR(BLUE_LIVE),
	COLOR_PAIR(MAGENTA_LIVE)
};

#endif
