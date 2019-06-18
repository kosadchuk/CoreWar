/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:06:13 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/15 14:06:13 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"
#include "../../inc/op.h"
#include "../../libft/inc/libft.h"

#include <stdio.h>
#include <unistd.h>

void		int_to_bytecode(char *data, int value, int bytes)
{
	int		i;

	i = 0;
	while (bytes)
	{
		data[bytes - 1] = (char)((value >> i) & 0xFF);
		printf("c = [%c]\n", (char)((value >> i) & 0xFF));
		i += 8;
		bytes--;
	}
}

static int	get_exec_code_size(t_asm const *content)
{
	t_list	*tmp;
	int		ret;

	ret = 0;
	tmp = content->code->commands;
	while (tmp)
	{
		ret += ((t_command *)tmp->content)->bytes;
		tmp = tmp->next;
	}
	return (ret);
}

void		write_header_in_binary(int fd, t_asm const *content)
{
	t_ull	len[2];
	char	*txt;
	int		command_bytes;
	int		i;

	len[0] = ft_strlen(content->name);
	len[1] = ft_strlen(content->comment);
	command_bytes = get_exec_code_size(content);
	txt = ft_strnew(sizeof(char) * (16 + PROG_NAME_LENGTH + COMMENT_LENGTH));
	int_to_bytecode(txt, COREWAR_EXEC_MAGIC, 4);
	i = 4;
	ft_memcpy(txt + i, content->name, len[0] > PROG_NAME_LENGTH ? PROG_NAME_LENGTH : len[0]);
	i += PROG_NAME_LENGTH;
	i += 4;
	int_to_bytecode(txt + i, command_bytes, 4);
	i += 4;
	ft_memcpy(txt + i, content->comment, len[1] > COMMENT_LENGTH ? COMMENT_LENGTH : len[1]);
	i += COMMENT_LENGTH;
	i = write(fd, txt, i);
	ft_memdel((void **)&txt);
}