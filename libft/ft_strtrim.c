/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:45:28 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/18 19:53:45 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_gogo(const char *s)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	j = i;
	while (s[i] != '\0')
		i++;
	i--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i--;
	i++;
	len = i - j;
	if (len <= 0)
		len = 0;
	return (len);
}

char			*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	char	*trim;

	i = 0;
	if (!s)
		return (NULL);
	if (!(trim = (char*)malloc(sizeof(char) * (ft_gogo(s) + 1))))
		return (NULL);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	j = i;
	i = 0;
	while (i != ft_gogo(s))
		trim[i++] = s[j++];
	trim[i] = '\0';
	return (trim);
}
