/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:44:57 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/09 11:45:47 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*m;
	int		i;

	i = ft_strlen(s1);
	m = (char *)malloc(sizeof(char) * (i + 1));
	if (m == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		m[i] = s1[i];
		i++;
	}
	m[i] = '\0';
	return (m);
}
