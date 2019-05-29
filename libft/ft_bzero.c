/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:15:49 by kosadchu          #+#    #+#             */
/*   Updated: 2019/04/08 16:16:08 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	__int128_t		*t_bzero_s;
	unsigned char	*uchar_s;
	size_t			i;

	t_bzero_s = (__int128_t *)s;
	uchar_s = (unsigned char *)s;
	i = n - (n % sizeof(__int128_t));
	while (i < n)
		uchar_s[i++] = 0;
	n /= sizeof(__int128_t);
	while (n)
		t_bzero_s[--n] = 0;
}
