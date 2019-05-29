/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:33:40 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/13 16:59:24 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ss;
	char	ch;

	i = 0;
	ss = (char *)s;
	ch = (char)c;
	while (ss[i])
		i++;
	while (ss[i] != ch)
	{
		if (i == 0)
			return (NULL);
		i--;
	}
	return (ss + i);
}
