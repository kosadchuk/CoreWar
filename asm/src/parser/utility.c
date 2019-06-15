/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:06:49 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/15 14:06:49 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"

void			skip_whitespaces(char const **str)
{
	t_ull		i;
	char const	*tmp;

	if (!str || !str)
		return;
	tmp = *str;
	i = 0;
	while (tmp[i])
	{
		if (!ft_isspace(tmp[i]))
			break;
		++i;
	}
	*str = tmp + i;
}

int				is_skipable(char const *line)
{
	skip_whitespaces(&line);
	if (*line == '#' || *line == '\0')
		return (1);
	return (0);
}

void			mass_memdel(void *a, void *b, void *c, void *d)
{
	ft_memdel(&a);
	ft_memdel(&b);
	ft_memdel(&c);
	ft_memdel(&d);
}