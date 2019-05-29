/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <kosadchu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 14:18:24 by kosadchu          #+#    #+#             */
/*   Updated: 2019/04/06 12:59:01 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pars_wm(char *str, int len)
{
	if (g_fl.pl == 1 && str[0] != '-' && g_lst.width < len && g_lst.type == 'd')
		g_bf.buf[g_bf.i++] = '+';
	if (g_fl.sp == 1 && (str[0] != '-' && g_fl.pl == 0
	&& (g_lst.type == 'd' || g_lst.type == 'f')) && g_fl.pr_n == 0)
		g_bf.buf[g_bf.i++] = ' ';
	(g_lst.type == 'd' && ((g_fl.pl == 1 || str[0] == '-' || (g_fl.zr == 1
	&& (g_fl.pl == 1 || g_fl.sp == 1))) || g_fl.sp == 1)) ? g_lst.width-- : 0;
	(g_lst.type == 'f' && g_fl.pr_n == 0 && (g_fl.sp == 1 || g_fl.pl == 1)
	&& str[0] != '-') ? g_lst.width-- : 0;
	(str[0] == '-' && (g_fl.zr == 1 || g_fl.zr == 2) && g_fl.pl == 0
	&& g_lst.type != 'f' && g_lst.type != 'd') ? g_lst.width-- : 0;
	(str[0] == '-' && g_fl.zr == 0 && g_fl.pl == 0 && g_fl.zr == 1
	&& g_lst.type != 'f') ? g_lst.width-- : 0;
	(g_lst.type == 'o' && g_fl.oc == 1
	&& (str[0] != '0' && len != 1) && g_lst.prec < 1) ? g_lst.width-- : 0;
	if (((g_lst.type == 'x' || g_lst.type == 'X' || g_lst.type == 'p')
	&& g_fl.oc == 1 && str[0] != '0' && len != 1) || g_lst.type == 'p')
		g_lst.width -= 2;
	(g_fl.pr_n == 1) ? g_lst.width-- : 0;
}

void	make_prec_width(char *str, int len)
{
	if (g_lst.width > len || g_lst.prec > len)
	{
		(g_lst.prec > len) ? g_lst.prec -= len : 0;
		(g_lst.width > len) ? g_lst.width -= len : 0;
		if (g_lst.prec >= g_lst.width)
			g_lst.width = 0;
		if (g_lst.width > g_lst.prec)
			g_lst.width -= g_lst.prec;
		if (g_lst.type == 'u' && g_fl.sp == 1 && str[0] == '0' && len == 1)
			g_fl.sp = 0;
		(str[0] == '0' && len == 1 && g_lst.dot == 1 && g_fl.oc < 1
		&& g_lst.type != 'f') ? g_lst.width++ : 0;
	}
}

void	free_flags(void)
{
	g_fl.mn = 0;
	g_fl.pl = 0;
	g_fl.oc = 0;
	g_fl.zr = 0;
	g_fl.sp = 0;
	g_lst.type = '0';
	g_lst.prec = 0;
	g_lst.width = 0;
	g_lst.dot = 0;
	g_lst.sz[0] = '0';
	g_lst.sz[1] = '0';
	g_lst.nine = 0;
	g_fl.pr_n = 0;
	g_lst.ecsp = 0;
}

void	if_oct(char *s, int l)
{
	if ((g_lst.type == 'x' && g_fl.oc == 1 && !(s[0] == '0' && l == 1))
		|| g_lst.type == 'p')
	{
		g_bf.buf[g_bf.i++] = '0';
		g_bf.buf[g_bf.i++] = 'x';
	}
	else if (g_lst.type == 'X' && g_fl.oc == 1 && !(s[0] == '0' && l == 1))
	{
		g_bf.buf[g_bf.i++] = '0';
		g_bf.buf[g_bf.i++] = 'X';
	}
	else if (g_lst.type == 'o' && g_fl.oc == 1
	&& (s[0] != '0' && l != 1) && g_lst.prec < 1)
		g_bf.buf[g_bf.i++] = '0';
}

int		if_dot(const char *f)
{
	if (f[g_bf.it] == '.' && !ft_strchr("0123456789", f[g_bf.it + 1]))
	{
		g_lst.dot = 1;
		g_bf.it++;
		return (1);
	}
	else if (f[g_bf.it] == '.' && f[g_bf.it + 1] == '0')
	{
		while (f[g_bf.it + 1] == '0')
			g_bf.it++;
		if (ft_strchr("123456789", f[g_bf.it + 1]))
			return (0);
		else
		{
			g_lst.dot = 1;
			g_bf.it += 1;
		}
		return (1);
	}
	return (0);
}
