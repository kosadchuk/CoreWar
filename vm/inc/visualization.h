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

/*
	COLORS
*/

typedef struct  s_visualization
{
    int         paused;
    WINDOW      *arena;
    WINDOW		*state;
}               t_visualization;

t_visualization				*init_visual(void);

void	setup_visual(void);

#endif
