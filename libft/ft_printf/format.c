/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <kosadchu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:06:40 by kosadchu          #+#    #+#             */
/*   Updated: 2019/03/31 17:40:47 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	space(int len, char c)
{
	while (len--)
	{
		if (g_bf.i >= 4000)
		{
			print_buf();
			ft_bzero(g_bf.buf, 4090);
			g_bf.i = 0;
		}
		g_bf.buf[g_bf.i++] = c;
	}
}

void	save_buff(char *s, int len, int minus)
{
	if (minus == 0)
		while (*s && len--)
		{
			if (g_bf.i >= 4000)
			{
				print_buf();
				ft_bzero(g_bf.buf, 4090);
				g_bf.i = 0;
			}
			g_bf.buf[g_bf.i++] = *s++;
		}
	else if (minus == 1)
	{
		s++;
		while (*s)
		{
			if (g_bf.i >= 4000)
			{
				print_buf();
				ft_bzero(g_bf.buf, 4090);
				g_bf.i = 0;
			}
			g_bf.buf[g_bf.i++] = *s++;
		}
	}
}

void	print_buf(void)
{
	int		l;

	l = 0;
	while (l < g_bf.i)
	{
		write(1, &g_bf.buf[l], 1);
		l++;
	}
	g_bf.ret += g_bf.i;
}

void	if_procent(const char *f, va_list ap)
{
	free_flags();
	if (!ft_strchr("-+#0 123456789.lhLscdiouxXpf%", f[g_bf.it + 1])
	|| f[g_bf.it + 1] == '\0')
		g_bf.it++;
	else
	{
		if (ft_strchr("-+#0 123456789.lhLscdiouxXpf%", f[g_bf.it + 1]))
		{
			g_bf.it++;
			check_spec(f, ap);
		}
		else
			g_bf.it++;
	}
}

void	check_format(const char *f, va_list ap)
{
	g_bf.i = 0;
	g_bf.it = 0;
	g_fl.two_zr = 0;
	g_fl.save_i = 0;
	while (f[g_bf.it] != '\0')
	{
		g_lst.width = 0;
		g_lst.prec = 0;
		if (f[g_bf.it] == '%')
			if_procent(f, ap);
		if (f[g_bf.it] != '%' && f[g_bf.it] != '\0')
		{
			g_bf.buf[g_bf.i++] = f[g_bf.it];
			g_bf.it++;
		}
	}
	print_buf();
}
