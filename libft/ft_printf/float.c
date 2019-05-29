/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <kosadchu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:15:06 by kosadchu          #+#    #+#             */
/*   Updated: 2019/04/05 15:39:23 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			with_dot(char *s1)
{
	int			len;
	char		*tmp;

	g_lst.prec = 0;
	if (g_fl.oc == 1)
	{
		s1 = ft_strjoin(s1, ".");
		tmp = s1;
		free(tmp);
	}
	len = ft_strlen(s1);
	(g_lst.width <= len) ? g_lst.width = 0 : 0;
	make_prec_width(s1, len);
	(g_fl.mn == 1) ? if_minus(s1, len) : 0;
	(g_fl.mn != 1) ? without_minus(s1, len) : 0;
}

void			without_dot(char *s1, char *s2)
{
	int			len;
	char		*s3;
	char		*tmp;

	s1 = ft_strjoin(s1, ".");
	s3 = ft_strjoin(s1, s2);
	tmp = s3;
	free(s1);
	free(tmp);
	len = ft_strlen(s3);
	(g_lst.width <= len) ? g_lst.width = 0 : 0;
	g_lst.prec = 0;
	make_prec_width(s3, len);
	(g_fl.mn == 1) ? if_minus(s3, len) : 0;
	(g_fl.mn != 1) ? without_minus(s3, len) : 0;
}

static void		make_str_s2(__int128_t d, long double x, int len, char *s)
{
	int			i;

	i = 0;
	x = x - d;
	while (len + 1 > 0)
	{
		x = x * 10;
		d = (__int128_t)x;
		s[i] = (char)(d % 10 + 48);
		x = x - d;
		len--;
		i++;
	}
	i--;
	(s[i] > '0') ? g_lst.ecsp = 1 : 0;
	if (s[i] >= '5')
	{
		while (s[i - 1] == '9')
		{
			(s[i - 1] == '9') ? s[i - 1] -= 9 : 0;
			i--;
			g_lst.nine++;
		}
		(s[i - 1] >= '0' && s[i - 1] <= '8') ? s[i - 1] += 1 : 0;
	}
}

char			*make_s2(__int128_t d, long double x)
{
	char		*s;
	int			i;
	int			len;

	g_lst.nine = 0;
	i = 0;
	len = g_lst.prec;
	(g_lst.dot == 1) ? len = 19 : 0;
	(d < 0) ? d *= -1 : 0;
	(x < 0) ? x *= -1 : 0;
	s = (char *)ft_memalloc(sizeof(char) * len + 2);
	make_str_s2(d, x, len, s);
	while (s[i] != '\0' && i < g_lst.prec)
		i++;
	s[i] = '\0';
	return (s);
}

void			flo(va_list ap)
{
	long double	x;
	__int128_t	d;
	char		*s1;
	char		*s2;

	x = cast_flo(ap);
	if ((x != x) || (x * 2 == x && x != 0))
		inf_nan(x);
	else
	{
		d = (__int128_t)x;
		minus_zero(x, d);
		(g_lst.prec == 0) ? g_lst.prec = 6 : 0;
		s2 = make_s2(d, x);
		(((g_lst.dot == 1 && s2[0] == '5' && d % 10 != 2 && d % 2 != 0
		&& d > 0) || (g_lst.dot == 1 && s2[0] > '5' && d >= 0)
		|| g_lst.nine == g_lst.prec || (g_lst.dot == 1 && s2[0] >= '5'
		&& g_lst.ecsp == 1)) && d >= 0) ? d = d + 1 : 0;
		((g_lst.dot == 1 && s2[0] == '5' && d % 10 != 2 && d % 2 != 0
		&& d < 0) || (g_lst.nine > 0 && d < 0)) ? d = d - 1 : 0;
		s1 = ft_itoa_bs_pf(d, 0, 10);
		(g_lst.dot == 1) ? with_dot(s1) : 0;
		(g_lst.dot == 0) ? without_dot(s1, s2) : 0;
		free(s2);
	}
}
