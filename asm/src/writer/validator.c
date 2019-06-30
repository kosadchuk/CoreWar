/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:06:18 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/30 14:45:03 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"
#include "../../inc/op.h"
#include "../../libft/inc/libft.h"

static int			is_mark(char const *arg)
{
	if (!arg || !arg[0] || !arg[1])
		return (0);
	if (arg[0] == LABEL_CHAR)
		return (1);
	if (arg[0] == DIRECT_CHAR && arg[1] == LABEL_CHAR)
		return (1);
	return (0);
}

static int			validate_marks(t_list const *commands, t_list const *marks)
{
	t_list const	*tmp;
	t_command const	*command;

	tmp = commands;
	while (tmp)
	{
		command = (t_command *)tmp->content;
		if (is_mark(command->arg1) && !find_mark(marks, command->arg1))
		{
			return (0);
		}
		if (is_mark(command->arg2) && !find_mark(marks, command->arg2))
		{
			return (0);
		}
		if (is_mark(command->arg3) && !find_mark(marks, command->arg3))
		{
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int					validate_parsed_data(t_asm const *data)
{
	if (!data || !(data->name) || !(data->comment))
	{
		ft_putendl("Error: first wall in validation data");
		return (0);
	}
	if (!(data->code) || !(data->code->commands))
	{
		ft_putendl("Error: second wall in validation data");
		ft_putendl("I think, file doesn't contain any command at all");
		return (0);
	}
	if (!validate_marks(data->code->commands, data->code->marks))
	{
		ft_putendl("Error: threed wall in validation data");
		ft_putendl("It seems like u try to use undeclared label.. ugly bitch!");
		return (0);
	}
	return (1);
}
