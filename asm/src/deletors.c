/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:06:29 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/28 18:16:28 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libft.h"
#include "../inc/asm.h"

extern t_err_manager_storage g_on_error;

void		command_deleter(void *content, t_ull size)
{
	t_command	*command;

	(void)size;
	command = (t_command *)content;
	ft_memdel((void **)&command->arg1);
	ft_memdel((void **)&command->arg2);
	ft_memdel((void **)&command->arg3);
}

void		mark_deleter(void *content, t_ull size)
{
	t_mark		*mark;

	(void)size;
	mark = (t_mark *)content;
	ft_memdel((void **)&mark->name);
}

void		on_error_deleter(void)
{
	ft_memdel((void **)&g_on_error.file_name);
	ft_memdel((void **)&g_on_error.file_content);
	if (!g_on_error.to_del)
		return ;
	ft_memdel((void **)&(g_on_error.to_del->name));
	ft_memdel((void **)&(g_on_error.to_del->comment));
	if (!g_on_error.to_del->code)
		return ;
	ft_lstdel(&g_on_error.to_del->code->commands, command_deleter);
	ft_lstdel(&g_on_error.to_del->code->marks, mark_deleter);
	ft_memdel((void **)&(g_on_error.to_del->code));
}
