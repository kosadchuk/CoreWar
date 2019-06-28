#ifndef VISUALIZATION_H
# define VISUALIZATION_H

# include <ncurses.h>
# include "core.h"

# define MIN_PLAYER_ID			1
# define MAX_PLAYER_ID			4

# define WIDTH					(64 * 3 + 5)
# define HEIGHT					(MEM_SIZE / 64 + 4)

typedef struct  s_visualization
{
    int         paused;
    WINDOW      *arena;
}               t_visualization;

t_visualization				*init_visual(void);

void	setup_visual(void);

#endif
