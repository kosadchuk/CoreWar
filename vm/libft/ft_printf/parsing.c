/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <kosadchu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 20:20:10 by kosadchu          #+#    #+#             */
/*   Updated: 2019/04/06 12:59:56 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	prec_not_zero(char *str, int len)
{
	(str[0] == '-') ? g_bf.buf[g_bf.i++] = '-' : 0;
	space(g_lst.prec, '0');
	(str[0] == '-') ? save_buff(str, len, 1) : 0;
	(str[0] != '-') ? save_buff(str, len, 0) : 0;
}

static void	save_without_minus(char *str, int len)
{
	if (str[0] == '0' && len == 1 && g_lst.dot == 1
	&& (g_lst.type != 'f' || (g_lst.type == 'f' && g_fl.pr_n == 1))
	&& !(g_lst.type == 'o' && g_fl.oc == 1))
		len = 0;
	if (len == 0 && g_bf.buf[g_bf.i - 1] == ' ' && g_lst.width == 0
	&& g_lst.type == 'u')
		g_bf.buf[--g_bf.i] = '\0';
	save_buff(str, len, 0);
}

void		without_minus(char *str, int len)
{
	pars_wm(str, len);
	(g_lst.width > 0 && (g_fl.zr == 0 || (g_fl.zr == 1 && g_lst.dot == 1
	&& g_lst.type != 'f') || g_fl.zr == 2)) ? space(g_lst.width, ' ') : 0;
	if_oct(str, len);
	if (g_fl.pl == 1 && str[0] != '-' && g_bf.buf[g_bf.i - 1] != '+'
	&& (g_lst.type == 'd' || g_lst.type == 'f') && g_fl.pr_n == 0)
		g_bf.buf[g_bf.i++] = '+';
	(g_lst.type == 'f' && g_fl.pr_n == 1) ? g_bf.buf[g_bf.i++] = '-' : 0;
	(g_lst.type == 'f' && g_fl.pr_n == 1 && len == 1)
	? g_bf.buf[g_bf.i++] = '0' : 0;
	if (g_lst.width > 0 && (g_lst.dot < 1 || g_lst.type == 'f'))
	{
		if (str[0] == '-')
		{
			str++;
			g_bf.buf[g_bf.i++] = '-';
		}
		(g_fl.zr == 1) ? space(g_lst.width, '0') : 0;
	}
	if (g_lst.prec > 0)
		prec_not_zero(str, len);
	else
		save_without_minus(str, len);
}

void		pars_if_minus(char *str, int len)
{
	(g_fl.pl == 1 && str[0] != '-' && g_lst.type != 'u' && g_lst.type != 'o'
	&& g_lst.type != 'x' && g_lst.type != 'X' && g_lst.type != 'p'
	&& g_fl.pr_n == 0) ? g_bf.buf[g_bf.i++] = '+' : 0;
	(g_fl.sp == 1 && str[0] != '-' && g_fl.pl == 0 && g_lst.type != 'o'
	&& g_lst.type != 'u' && g_lst.type != 'x' && g_lst.type != 'X'
	&& g_lst.type != 'p' && g_fl.pr_n == 0) ? g_bf.buf[g_bf.i++] = ' ' : 0;
	(g_lst.type != 'o' && g_lst.type != 'u' && g_lst.type != 'x'
	&& g_lst.type != 'X' && g_lst.type != 'p'
	&& ((g_fl.pl == 1 && str[0] != '-') || (str[0] != '-' && g_fl.sp == 1))
	&& g_fl.pr_n == 0) ? g_lst.width-- : 0;
	(g_lst.type == 'o' && g_fl.oc == 1 && g_lst.prec < 1
	&& (str[0] != '0' && len != 1)) ? g_lst.width-- : 0;
	(str[0] == '-' && g_lst.prec > 0) ? g_bf.buf[g_bf.i++] = '-' : 0;
	(g_fl.pr_n == 1) ? g_bf.buf[g_bf.i++] = '-' : 0;
	(g_fl.pr_n == 1) ? g_lst.width-- : 0;
}

void		if_minus(char *str, int len)
{
	pars_if_minus(str, len);
	if (g_lst.prec > 0)
	{
		if_oct(str, len);
		space(g_lst.prec, '0');
		if (str[0] == '-')
			save_buff(str, len, 1);
		else
			save_buff(str, len, 0);
	}
	else
	{
		if_oct(str, len);
		(str[0] == '0' && len == 1 && g_lst.dot == 1 && (g_lst.type == 'd'
		|| g_lst.type == 'x' || g_lst.type == 'X' || g_lst.type == 'u'
		|| (g_lst.type == 'o' && g_fl.oc != 1))) ? len = 0 : 0;
		(len == 0 && g_bf.buf[g_bf.i - 1] == ' ' && (g_lst.type == 'x'
		|| g_lst.type == 'X')) ? g_bf.buf[--g_bf.i] = '\0' : 0;
		save_buff(str, len, 0);
	}
	if (((g_lst.type == 'x' || g_lst.type == 'X')
	&& g_fl.oc == 1 && str[0] != '0' && len != 1) || g_lst.type == 'p')
		g_lst.width -= 2;
	(g_lst.width > 0) ? space(g_lst.width, ' ') : 0;
}
