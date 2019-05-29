/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 18:06:30 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/13 13:39:47 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	sz_d;
	size_t	sz_s;

	sz_d = ft_strlen(dst);
	sz_s = ft_strlen(src);
	i = 0;
	j = 0;
	if (sz_d >= dstsize)
		return (dstsize + sz_s);
	while (dst[i])
		i++;
	while (src[j] && (dstsize - 1) > i)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (sz_d + sz_s);
}
