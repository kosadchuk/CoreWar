/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:04:00 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/08 16:59:30 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l;
	int		i;
	char	*jo;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	l = (ft_strlen(s1) + ft_strlen(s2));
	jo = (char*)malloc(sizeof(char) * (l + 1));
	if (jo == NULL)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
	{
		jo[i++] = *s1++;
	}
	while (*s2 != '\0')
	{
		jo[i++] = *s2++;
	}
	jo[i] = '\0';
	return (jo);
}
