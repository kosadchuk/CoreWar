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

void			init_by_command_data(t_asm const *src, t_command const *com, void **dst, t_ull *len)
{
	(void)src;
	(void)com;
	(void)dst;
	(void)len;
}

void			write_commands_in_binary(int fd, t_asm const *content)
{
	t_command	*command;
	t_list		*lst;
	void		*data;
	t_ull		len;

	lst = content->code->commands;
	while (lst)
	{
		data = 0;
		len = 0;
		command = (t_command *)lst->content;
		init_by_command_data(content, command, &data, &len);
		len = write(fd, data, len);
		lst = lst->next;
	}
}
