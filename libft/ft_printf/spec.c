/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <kosadchu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:50:30 by kosadchu          #+#    #+#             */
/*   Updated: 2019/04/05 15:57:29 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_width(const char *f)
{
	char	*s;
	char	*tmp;
	int		len;

	len = 0;
	while (ft_strchr("0123456789", f[g_bf.it]))
	{
		g_bf.it++;
		len++;
	}
	s = ft_strsub(f, g_bf.it - len, len);
	tmp = s;
	free(tmp);
	g_lst.width = ft_atoi(s);
}

void	check_prec(const char *f)
{
	char	*s;
	int		len;
	char	*tmp;

	len = 0;
	if (if_dot(f) == 0)
	{
		g_bf.it++;
		while (ft_strchr("0123456789", f[g_bf.it]))
		{
			g_bf.it++;
			len++;
		}
		s = ft_strsub(f, g_bf.it - len, len);
		tmp = s;
		free(tmp);
		g_lst.prec = ft_atoi(s);
	}
}

void	save_flags(const char *f)
{
	while (ft_strchr("-+#0 ", f[g_bf.it]))
	{
		if (f[g_bf.it] == '-' || g_fl.mn == 1)
			g_fl.mn = 1;
		if (f[g_bf.it] == '+' || g_fl.pl == 1)
			g_fl.pl = 1;
		if (f[g_bf.it] == '#' || g_fl.oc == 1)
			g_fl.oc = 1;
		if (f[g_bf.it] == '0' || g_fl.zr == 1)
			g_fl.zr = 1;
		if (f[g_bf.it] == ' ' || g_fl.sp == 1)
			g_fl.sp = 1;
		g_bf.it++;
	}
}

void	save_size(const char *f)
{
	if (f[g_bf.it] == 'l' && f[g_bf.it + 1] != 'l')
		g_lst.sz[0] = 'l';
	else if (f[g_bf.it] == 'l' && f[g_bf.it + 1] == 'l')
	{
		g_lst.sz[0] = 'l';
		g_lst.sz[1] = 'l';
		while (f[g_bf.it] == 'l')
			g_bf.it++;
		g_bf.it--;
	}
	else if (f[g_bf.it] == 'h' && f[g_bf.it + 1] != 'h')
		g_lst.sz[0] = 'h';
	else if (f[g_bf.it] == 'h' && f[g_bf.it + 1] == 'h')
	{
		g_lst.sz[0] = 'h';
		g_lst.sz[1] = 'h';
		while (f[g_bf.it] == 'h')
			g_bf.it++;
		g_bf.it--;
	}
	else if (f[g_bf.it] == 'L')
		g_lst.sz[0] = 'L';
	g_bf.it++;
}

void	check_spec(const char *f, va_list ap)
{
	if (ft_strchr("-+#0 ", f[g_bf.it]))
		save_flags(f);
	if (ft_strchr("123456789", f[g_bf.it]))
		check_width(f);
	if (f[g_bf.it] == '.')
		check_prec(f);
	if (ft_strchr("lhL", f[g_bf.it]))
		save_size(f);
	if (ft_strchr("scdiouxXpf%", f[g_bf.it]))
	{
		if (ft_strchr("sc", f[g_bf.it]))
			str_char(f, ap);
		if (ft_strchr("diouxXpf", f[g_bf.it]))
			numbers(f, ap);
		if (f[g_bf.it] == '%')
			pars_char('%', 1);
		g_bf.it++;
	}
}
