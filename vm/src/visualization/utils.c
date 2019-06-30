/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmarchen <kmarchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:01:31 by kmarchen          #+#    #+#             */
/*   Updated: 2019/06/30 17:43:08 by kmarchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/visualization.h"

int32_t		correct_pos(int32_t pos)
{
	pos %= MEM_SIZE;
	if (pos < 0)
		pos += MEM_SIZE;
	return (pos);
}

clock_t		get_delay(void)
{
	return (g_vm->visual->offset + CLOCKS_PER_SEC / g_vm->visual->speed);
}

void		finish_vs(void)
{
	delwin(g_vm->visual->arena);
	delwin(g_vm->visual->state);
	ft_memdel((void **)&g_vm->visual);
	endwin();
}
