/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:02:49 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/18 20:09:57 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_minus(int *n, int *minus)
{
	if (*n < 0)
	{
		*n *= -1;
		*minus = 1;
	}
}

char			*ft_itoa(int n)
{
	char	*s;
	int		i;
	int		len;
	int		minus;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_lenint(n);
	if (!(s = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	minus = 0;
	ft_minus(&n, &minus);
	s[len] = '\0';
	while (len > minus)
	{
		s[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	if (minus == 1)
		s[0] = '-';
	return (s);
}
