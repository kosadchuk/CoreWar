/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 17:50:39 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/18 19:56:10 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*word_len(char const *s, char c, int *j)
{
	int		t;
	int		len;
	char	*wrd;

	len = 0;
	while (s[*j] == c)
		(*j)++;
	while (s[*j] != c && s[*j] != '\0')
	{
		(*j)++;
		len++;
	}
	if (!(wrd = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	(*j) = (*j) - len;
	t = 0;
	while (t < len)
	{
		wrd[t] = s[*j];
		t++;
		(*j)++;
	}
	wrd[t] = '\0';
	return (wrd);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		len;
	char	**str;

	if (!s)
		return (NULL);
	len = ft_words_num(s, c);
	if (!(str = (char**)malloc(sizeof(char*) * len)))
		return (NULL);
	i = 0;
	j = 0;
	while ((--len) > 0)
	{
		str[i] = word_len(s, c, &j);
		i++;
	}
	str[i] = NULL;
	return (str);
}
