/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 20:27:11 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/12 15:43:09 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	char	*s1;
	size_t	i;

	ch = (char)c;
	s1 = (char *)s;
	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == ch)
			return (s1 + i);
		i++;
	}
	if (ch == '\0')
		return (s1 + i);
	return (NULL);
}
