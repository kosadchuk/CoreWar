/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <kosadchu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:55:45 by kosadchu          #+#    #+#             */
/*   Updated: 2019/03/31 16:22:31 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t		cast_dec(va_list ap)
{
	if (g_lst.sz[0] == 'l' && g_lst.sz[1] != 'l')
		return (va_arg(ap, long int));
	else if (g_lst.sz[0] == 'l' && g_lst.sz[1] == 'l')
		return (va_arg(ap, long long int));
	else if (g_lst.sz[0] == 'h' && g_lst.sz[1] != 'h')
		return ((short int)va_arg(ap, int));
	else if (g_lst.sz[0] == 'h' && g_lst.sz[1] == 'h')
		return ((signed char)va_arg(ap, int));
	else
		return (va_arg(ap, int));
}

long double		cast_flo(va_list ap)
{
	if (g_lst.sz[0] == 'L' && g_lst.sz[1] == '0' && g_lst.type == 'f')
		return (va_arg(ap, long double));
	else
		return (va_arg(ap, double));
}

uintmax_t		cast_hex(va_list ap)
{
	if (g_lst.sz[0] == 'l' && g_lst.sz[1] != 'l')
		return (va_arg(ap, unsigned long int));
	else if (g_lst.sz[0] == 'l' && g_lst.sz[1] == 'l')
		return (va_arg(ap, unsigned long long int));
	else if (g_lst.sz[0] == 'h' && g_lst.sz[1] != 'h')
		return ((unsigned short int)va_arg(ap, unsigned int));
	else if (g_lst.sz[0] == 'h' && g_lst.sz[1] == 'h')
		return ((unsigned char)va_arg(ap, unsigned int));
	else if (g_lst.type == 'p')
		return (va_arg(ap, unsigned long int));
	else
		return (va_arg(ap, unsigned int));
}

void			two_zero(char *num, int len)
{
	if (g_lst.dot == 1 && num[0] == '0' && len == 1 && g_fl.two_zr == 1)
		g_fl.two_zr = 2;
	else if (g_lst.dot == 1 && num[0] == '0' && len == 1 && g_fl.two_zr < 1)
	{
		g_fl.save_i = g_bf.i;
		g_fl.two_zr = 1;
	}
}

void			clean_zero(void)
{
	int		len;

	len = g_bf.i;
	if (g_fl.two_zr == 2 && g_fl.oc != 1 && g_lst.type != 'p')
	{
		while (len >= g_fl.save_i)
		{
			if (g_bf.buf[len] == '0')
				g_bf.buf[len] = ' ';
			len--;
		}
		g_fl.two_zr = 0;
	}
}
