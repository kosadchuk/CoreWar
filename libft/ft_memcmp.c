/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 15:45:36 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/12 21:08:37 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	i;

	str1 = (char*)s1;
	str2 = (char*)s2;
	i = 0;
	while (n > 0)
	{
		if (str1[i] != str2[i])
			return (((unsigned char*)str1)[i] - ((unsigned char*)str2)[i]);
		i++;
		n--;
	}
	return (0);
}
