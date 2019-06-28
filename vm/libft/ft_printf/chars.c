/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <kosadchu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:13:19 by kosadchu          #+#    #+#             */
/*   Updated: 2019/03/31 16:23:36 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_space(char *s, int len)
{
	if (g_fl.mn == 1)
	{
		save_buff(s, len, 0);
		space(g_lst.width, ' ');
	}
	else if (g_fl.mn != 1)
	{
		space(g_lst.width, ' ');
		save_buff(s, len, 0);
	}
}

void		pars_str(char *s)
{
	int		len;

	(!s) ? s = "(null)" : 0;
	len = ft_strlen(s);
	(g_lst.prec > 0 && g_lst.prec < len) ? len = g_lst.prec : len;
	if (g_lst.width > len && g_lst.dot != 1)
	{
		g_lst.width -= len;
		print_space(s, len);
	}
	else if (g_lst.width > 0 && g_lst.dot == 1 && g_fl.zr > 0 && g_fl.mn != 1)
		space(g_lst.width, '0');
	else if (g_lst.width > 0 && g_lst.dot == 1)
		space(g_lst.width, ' ');
	else if (g_lst.dot != 1)
		save_buff(s, len, 0);
}

void		pars_char(char c, int len)
{
	if (g_lst.width > len)
	{
		g_lst.width -= len;
		if (g_fl.mn == 1)
		{
			g_bf.buf[g_bf.i++] = c;
			space(g_lst.width, ' ');
		}
		else
		{
			(g_fl.zr > 0) ? space(g_lst.width, '0') : 0;
			(g_fl.zr == 0) ? space(g_lst.width, ' ') : 0;
			g_bf.buf[g_bf.i++] = c;
		}
	}
	else
		g_bf.buf[g_bf.i++] = c;
}

void		str_char(const char *f, va_list ap)
{
	char	*s;
	char	ch;

	if (f[g_bf.it] == 's')
	{
		s = va_arg(ap, char*);
		pars_str(s);
	}
	if (f[g_bf.it] == 'c')
	{
		ch = (char)va_arg(ap, int);
		pars_char(ch, 1);
	}
}
