/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <kosadchu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:33:24 by kosadchu          #+#    #+#             */
/*   Updated: 2019/04/05 15:40:02 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_nan(char *s, int len)
{
	(g_lst.prec > 0) ? g_lst.prec = 0 : 0;
	(g_lst.width > len) ? g_lst.width -= len : 0;
	(g_lst.width <= len) ? g_lst.width = 0 : 0;
	if (g_fl.mn == 1)
	{
		if (g_fl.sp == 1 && s[0] == 'i')
		{
			g_bf.buf[g_bf.i++] = ' ';
			g_lst.width--;
		}
		save_buff(s, len, 0);
		space(g_lst.width, ' ');
	}
	else
	{
		space(g_lst.width, ' ');
		save_buff(s, len, 0);
	}
}

void	inf_nan(long double x)
{
	char *s;
	char *tmp;

	if (x != x)
	{
		s = ft_strdup("nan");
		print_nan(s, 3);
	}
	if (x * 2 == x && x < 0)
	{
		s = ft_strdup("-inf");
		print_nan(s, 4);
	}
	if (x * 2 == x && x > 0 && g_fl.pl == 1)
	{
		s = ft_strdup("+inf");
		print_nan(s, 4);
	}
	if (x * 2 == x && x > 0 && g_fl.pl < 1)
	{
		s = ft_strdup("inf");
		print_nan(s, 3);
	}
	tmp = s;
	free(tmp);
}

void	minus_zero(double i, __int128_t d)
{
	long long *tmp;
	long long bitmove;
	long long j;

	tmp = (long long *)(&i);
	bitmove = *tmp;
	j = bitmove >> 63;
	if (j < 0 && d == 0)
		g_fl.pr_n = 1;
	else
		g_fl.pr_n = 0;
}
