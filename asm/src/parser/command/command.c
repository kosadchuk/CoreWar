/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:07:05 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/28 18:51:16 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/asm.h"
#include "../../../libft/inc/libft.h"
#include "../../../inc/op.h"

#include <stdio.h>
#include <stdlib.h>

static t_ull	g_last_stack_id = 0;

t_cm_desc const	g_comms[16] =\
{
	{ 0x01, "live", T_DIR, 0, 0, 0, 4 },
	{ 0x02, "ld", T_DIR | T_IND, T_REG, 0, 1, 4 },
	{ 0x03, "st", T_REG, T_REG | T_IND, 0, 1, 4 },
	{ 0x04, "add", T_REG, T_REG, T_REG, 1, 4 },
	{ 0x05, "sub", T_REG, T_REG, T_REG, 1, 4 },
	{ 0x06, "and", T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG, 1, 4 },
	{ 0x07, "or", T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG, 1, 4 },
	{ 0x08, "xor", T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG, 1, 4 },
	{ 0x09, "zjmp", T_DIR, 0, 0, 0, 2 },
	{ 0x0a, "ldi", T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG, 1, 2 },
	{ 0x0b, "sti", T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR, 1, 2 },
	{ 0x0c, "fork", T_DIR, 0, 0, 0, 2 },
	{ 0x0d, "lld", T_DIR | T_IND, T_REG, 0, 1, 4 },
	{ 0x0e, "lldi", T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG, 1, 2 },
	{ 0x0f, "lfork", T_DIR, 0, 0, 0, 2 },
	{ 0x10, "aff", T_REG, 0, 0, 1, 4 }
};

static t_ull			init_id_type(char const **line, t_ull *id_type)
{
	t_ull				ret;
	t_ull				i;

	skip_whitespaces(line);
	ret = 0;
	while (ret < 16)
	{
		i = 0;
		while (g_comms[ret].name[i])
		{
			if (g_comms[ret].name[i] != (*line)[i])
				break ;
			++i;
		}
		if (g_comms[ret].name[i] == '\0' && (*line)[i] == ' ')
		{
			*line = *line + ft_strlen(g_comms[ret].name);
			*id_type = ++ret;
			return (1);
		}
		++ret;
	}
	wrong_command_name(*line);
	return (0);
}

static int				process_arg(char const **line, char const *args[3],\
									int i)
{
	int					has_separator;

	if (**line == '\0')
		return (1);
	skip_whitespaces(line);
	has_separator = **line == SEPARATOR_CHAR ? 1 : 0;
	if (i == 0 && has_separator)
	{
		printf("Error: unexpected separator\n");
		return (0);
	}
	if (i != 0)
	{
		*line = *line + 1;
		skip_whitespaces(line);
	}
	args[i] = get_arg(*line);
	*line = *line + ft_strlen(args[i]);
	if (has_separator && !args[i])
	{
		printf("Error: separator without the arg at the end of command\n");
		return (0);
	}
	return (1);
}

static int				process_bytes_len(char const *args[3],\
						t_ull id_type, t_ull *len)
{
	t_ull				size;
	int					arg_types[3];
	int					err_code;

	err_code = 1;
	size = 1;
	size += g_comms[id_type].has_type_code;
	arg_types[0] = get_arg_type(args[0]);
	err_code &= compare_arg_types(id_type, arg_types[0], 0);
	size += get_arg_size_in_bytes(arg_types[0], id_type);
	arg_types[1] = get_arg_type(args[1]);
	err_code &= compare_arg_types(id_type, arg_types[1], 1);
	size += get_arg_size_in_bytes(arg_types[1], id_type);
	arg_types[2] = get_arg_type(args[2]);
	err_code &= compare_arg_types(id_type, arg_types[2], 2);
	size += get_arg_size_in_bytes(arg_types[2], id_type);
	*len = size;
	return (err_code);
}

int						parse_command(char const *line, t_asm *dst)
{
	char const			*args[3] = { 0, 0, 0 };
	t_ull				id_type;
	t_ull				bytes_len;
	char				error_code;

	id_type = 0;
	bytes_len = 0;
	error_code = 1;
	RETN_IF_NULL(init_id_type(&line, &id_type));
	--id_type;
	error_code &= process_arg(&line, args, 0);
	error_code &= process_arg(&line, args, 1);
	error_code &= process_arg(&line, args, 2);
	skip_whitespaces(&line);
	if ((*line && *line != COMMENT_CHAR) || !error_code)
		return (0);
	error_code &= process_bytes_len(args, id_type, &bytes_len);
	error_code &= append_command(dst,\
					create_command(g_last_stack_id, id_type, args, bytes_len));
	dst->code->curr_location += bytes_len;
	++g_last_stack_id;
	return (error_code);
}
