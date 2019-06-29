#ifndef VISUALIZATION_H
# define VISUALIZATION_H

# include <ncurses.h>
# include "core.h"

# define MIN_PLAYER_ID			1
# define MAX_PLAYER_ID			4

# define CELLS_NUMBER			64
# define ARENA_WIDTH			(CELLS_NUMBER * 3)
# define ARENA_HEIGHT			(MEM_SIZE / CELLS_NUMBER)

# define STATE_WIDTH			60
# define STATE_HEIGHT			ARENA_HEIGHT

# define CYCLE_TO_WAIT			50

/*
	COLORS
*/


// # define COLOR_BLACK		0
// # define COLOR_RED			1
// # define COLOR_GREEN		2
// # define COLOR_YELLOW		3
// # define COLOR_BLUE			4
// # define COLOR_MAGENTA	5
// # define COLOR_CYAN			6
// # define COLOR_WHITE		7
# define COLOR_GRAY			8
# define LIGHT_RED			9
# define DARK_RED				10
# define LIGHT_GREEN		11
# define DARK_GREEN			12
# define STATE_PAUSED		13
# define STATE_RUNNING	14
# define GRAY						15
# define RED						16
# define GREEN					17
# define BLUE						18
# define MAGENTA				19
# define GRAY_CURSOR		20
# define RED_CURSOR			21
# define GREEN_CURSOR		22
# define BLUE_CURSOR		23
# define MAGENTA_CURSOR	24
# define RED_LIVE				25
# define GREEN_LIVE			26
# define BLUE_LIVE			27
# define MAGENTA_LIVE		28

typedef struct		s_cell
{
	int				color;
	ssize_t			cycles;
}					t_cell;

typedef struct  s_visualization
{
    int         paused;
    WINDOW      *arena;
    WINDOW		*state;
    t_cell		data[MEM_SIZE];
}               t_visualization;

t_visualization				*init_visual(void);

void	setup_visual(void);
void	init_colors(void);
int		get_player_color(int);
int     get_player_cursor(int);

void        update_map(int32_t, int32_t, int32_t);

void render_arena(void);
void render_state(void);

#endif
