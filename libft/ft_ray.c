/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <kosadchu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 20:46:58 by kosadchu          #+#    #+#             */
/*   Updated: 2019/05/04 20:57:24 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*new_array(size_t size)
{
	t_ray	*mass;

	mass = malloc(sizeof(t_ray));
	mass->arr = malloc(sizeof(t_ray) * size);
	mass->len = 0;
	mass->full = size;
	return (mass);
}

void	*push_array(void *dst, void *src)
{
	t_ray	*cst;
	t_ray	**tmp;

	cst = (t_ray*)dst;
	if (cst->len >= cst->full)
	{
		cst->full *= 2;
		tmp = malloc(cst->full * sizeof(t_ray*));
		ft_memcpy(tmp, cst->arr, sizeof(t_ray*) * cst->len);
		free(cst->arr);
		cst->arr = (void **)tmp;
	}
	return ((cst->arr[cst->len++] = src));
}
