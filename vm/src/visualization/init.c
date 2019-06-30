/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarchen <kmarchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:01:22 by kmarchen          #+#    #+#             */
/*   Updated: 2019/06/30 17:13:22 by kmarchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/visualization.h"

t_visualization		*init_visual(void)
{
	t_visualization *visual;

	if (!(visual = (t_visualization *)ft_memalloc(sizeof(t_visualization))))
		return (NULL);
	visual->key = -1;
	visual->offset = 0;
	visual->speed = 50;
	visual->paused = true;
	visual->arena = NULL;
	visual->state = NULL;
	return (visual);
}
