/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:37:58 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/20 18:39:36 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_words_num(char const *s, char c)
{
	int		word;
	int		i;

	word = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			while (s[i] != '\0' && s[i] != c)
				i++;
			word += 1;
		}
	}
	word = word + 1;
	return (word);
}
