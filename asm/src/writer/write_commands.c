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

static int		get_arg_type_code(t_command const *com, t_ull *len)
{
	(void)com;
	(void)len;
	return (0);
}

static int		get_arg_code(t_code const *src, char const *arg, t_ull *len)
{
	(void)src;
	(void)arg;
	(void)len;
	return (0);
}

static void		init_by_command_data(t_code const *src, t_command const *com, void *dst)
{
	t_ull		len;
	t_ull		i;

	i = 0;
	len = 0;
	int_to_bytecode((char *)dst + i, get_arg_type_code(com, &len), len);
	i += len;
	int_to_bytecode((char *)dst + i, get_arg_code(src, com->arg1, &len), len);
	i += len;
	int_to_bytecode((char *)dst + i, get_arg_code(src, com->arg2, &len), len);
	i += len;
	int_to_bytecode((char *)dst + i, get_arg_code(src, com->arg3, &len), len);
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
