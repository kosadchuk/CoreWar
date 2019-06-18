/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:06:04 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/15 14:07:45 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"
#include "../../inc/op.h"
#include "../../libft/inc/libft.h"

#include <stdio.h>
#include <unistd.h>

extern t_cm_desc const	g_comms[16];

static int		get_arg_type_code(t_command const *com, t_ull *len)
{
	int			ret;

	*len = 0;
	if (g_comms[com->id_type].has_type_code == 0)
		return (0);
	*len = 1;
	ret = 0;
	ret |= get_arg_type(com->arg1) << 24;
	ret |= get_arg_type(com->arg2) << 16;
	ret |= get_arg_type(com->arg3) << 8;
	return (ret);
}

static int		get_arg_code(t_code const *src, t_command const *com, char const *arg, t_ull *len)
{
	t_mark		*mark;
	int			mark_location_byte;
	int			ret;
	int			type;

	type = get_arg_type(arg);
	*len = (type == T_REG ? 1 : 2);
	if (type == T_DIR)
		*len = g_comms[com->id_type].t_dir_size;
	ret = 0;
	if (type == T_REG)
		ret = ft_atoi(arg + 1);
	else
	{
		if ((mark = find_mark(src->marks, arg)))
			mark_location_byte = mark->location;
		if (type == T_DIR)
			ret = (arg[1] == ':' ? mark_location_byte - (int)com->starting_byte_index : ft_atoi(arg + 1));
		if (type == T_IND)
			ret = (arg[0] == ':' ? mark_location_byte : ft_atoi(arg));
	}
	return (ret);
}

static void		init_by_command_data(t_code const *src, t_command const *com, void *dst)
{
	t_ull		len;
	t_ull		i;

	i = 0;
	len = 0;
	int_to_bytecode((char *)dst + i, get_arg_type_code(com, &len), len);
	i += len;
	int_to_bytecode((char *)dst + i, get_arg_code(src, com, com->arg1, &len), len);
	i += len;
	int_to_bytecode((char *)dst + i, get_arg_code(src, com, com->arg2, &len), len);
	i += len;
	int_to_bytecode((char *)dst + i, get_arg_code(src, com, com->arg3, &len), len);
	i += len;
}

void			write_commands_in_binary(int fd, t_asm const *content)
{
	t_command	*command;
	t_list		*lst;
	void		*data;

	lst = content->code->commands;
	while (lst)
	{
		command = (t_command *)lst->content;
		data = ft_memalloc(command->bytes);
		init_by_command_data(content->code, command, &data);
		t_ull len = write(fd, data, command->bytes);
		(void)len;
		ft_memdel((void **)&data);
		lst = lst->next;
	}
}
