#include "../../inc/visualization.h"

t_visualization     *init_visual(void)
{
    t_visualization *visual;

    if (!(visual = (t_visualization *)ft_memalloc(sizeof(t_visualization))))
        printf("Error in memory allocation");
    visual->paused = true;
    visual->arena = NULL;
    visual->state = NULL;
    return (visual);
}
