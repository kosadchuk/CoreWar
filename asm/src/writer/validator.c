#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdio.h>

static int			contains_label(t_list const *marks, char const* label)
{
	t_list const	*tmp;
	t_mark const	*mark;
	t_ull			i;

	i = 0;
	if (label[0] == '%')
		i = 2;
	if (label[0] == ':')
		i = 1;
	tmp = marks;
	while (tmp)
	{
		mark = (t_mark *)tmp->content;
		if (ft_strequ(mark->name, label + i))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int			is_label(char const *arg)
{
	if (!arg || !arg[0] || !arg[1])
		return (0);
	if (arg[0] == ':')
		return (1);
	if (arg[0] == '%' && arg[1] == ':')
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
		if (is_label(command->arg1) && !contains_label(marks, command->arg1))
		{
			return (0);
		}
		if (is_label(command->arg2) && !contains_label(marks, command->arg2))
		{
			return (0);
		}
		if (is_label(command->arg3) && !contains_label(marks, command->arg3))
		{
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int					validate_parsed_data(t_asm const* data)
{
	if (!data || !(data->name) || !(data->comment))
	{
		printf("Error: first wall in validation data\n");
		return (0);
	}
	if (!(data->code) || !(data->code->commands))
	{
		printf("Error: second wall in validation data\n");
		printf("I think, file doesn't contain any command at all\n");
		return (0);
	}
	if (!validate_marks(data->code->commands, data->code->marks))
	{
		printf("Error: threed wall in validation data\n");
		printf("It seems like u try to use undeclared label.. ugly bitch!\n");
		return (0);
	}
	return (1);
}