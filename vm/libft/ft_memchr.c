/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 14:54:59 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/12 21:07:29 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*s1;
	char	ch;
	size_t	i;

	s1 = (char *)s;
	ch = (char)c;
	i = 0;
	while (n > 0)
	{
		if (s1[i] == ch)
			return (s1 + i);
		i++;
		n--;
	}
	return (NULL);
}
