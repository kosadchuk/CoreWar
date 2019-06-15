/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:07:10 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/15 14:07:10 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/asm.h"
#include "../../../libft/inc/libft.h"

#include <stdio.h>

extern t_cm_desc const	g_comms[16];

int			is_valid_t_reg(char const *arg)
{
	t_ull	arg_len;

	arg_len = ft_strlen(arg);
	if (*arg != 'r' || arg_len > 3 || arg_len <= 1)
		return (0);
	if (arg_len == 2)
	{
		if (!ft_isdigit(arg[1]) || arg[1] == '0')
			return (0);
	}
	else
	{
		if (!ft_isdigit(arg[1]) || !ft_isdigit(arg[2]) ||
			(arg[1] == '0' && arg[2] == '0'))
			return (0);
	}
	return (1);
}

int			is_valid_t_dir(char const *arg)
{
	t_ull	arg_len;
	t_ull	i;

	arg_len = ft_strlen(arg);
	if (arg_len <= 1 || arg[0] != '%')
		return (0);
	if (arg[1] == ':')
	{
		if (arg_len == 2)
			return (0);
	}
	else
	{
		if (!ft_isdigit(arg[1]) && arg[1] != '-')
			return (0);
		i = 2;
		while (i < arg_len && ft_isdigit(arg[i]))
			++i;
		if (i != arg_len)
			return (0);
	}
	return (1);
}

int			is_valid_t_ind(char const *arg)
{
	t_ull	arg_len;
	t_ull	i;

	arg_len = ft_strlen(arg);
	if (arg_len == 0)
		return (0);
	if (arg[0] == ':')
	{
		if (arg_len == 1)
			return (0);
	}
	else
	{
		if (!ft_isdigit(arg[0]) && arg[0] != '-')
			return (0);
		i = 1;
		while (i < arg_len && ft_isdigit(arg[i]))
			++i;
		if (i != arg_len)
			return (0);
	}
	return (1);
}

int			compare_arg_types(int command_type_id, int arg_type, int index)
{
	int		needed_type;

	needed_type = 0;
	if (index == 0)
		needed_type = g_comms[command_type_id].arg1_type;
	if (index == 1)
		needed_type = g_comms[command_type_id].arg2_type;
	if (index == 2)
		needed_type = g_comms[command_type_id].arg3_type;
	if (arg_type & needed_type || arg_type == needed_type)
		;
	else
		wrong_arg_type(needed_type, arg_type, index + 1);
	return (1);
}
