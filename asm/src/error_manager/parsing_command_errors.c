#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdlib.h>
#include <stdio.h>

extern t_err_manager_storage g_on_error;

void		wrong_asm_in_file(int type)
{
	if (type == 4)
	{
		ft_putendl("Error: smth went wrong while code parsing");
	}
	else
	{
		ft_putstr("Error: is seems like there is a faggot in front of monitor: ");
		ft_putnbr(type);
		ft_putendl("");
	}
	on_error_deleter();
	exit(6);
}

void				wrong_command_name(char const *command)
{
	char const		*tmp;
	t_ull			len;

	tmp = command;
	skip_whitespaces(&tmp);
	len = 0;
	while (tmp[len] && tmp[len] != ' ' && tmp[len] != '\t')
		++len;
	tmp = ft_strsub(tmp, 0, len);
	ft_putstr("Error: unknown identifier ");
	ft_putendl(tmp);
	ft_putstr("in command ");
	ft_putendl(command);
	ft_memdel((void **)&tmp);
	on_error_deleter();
	exit(7);
}

static char const	*get_expected(int expected_arg_types)
{
	char const		*ret;
	char const		*tmp;

	ret = 0;
	if (expected_arg_types & T_REG)
		ret = ft_strdup("T_REG");
	if (expected_arg_types & T_DIR)
	{
		if (ret)
			tmp = ft_strjoin(ret, " or T_DIR");
		else
			tmp = ft_strjoin("", "T_DIR");
		ft_memdel((void **)&ret);
		ret = tmp;
	}
	if (expected_arg_types & T_IND)
	{
		if (ret)
			tmp = ft_strjoin(ret, " or T_IND");
		else
			tmp = ft_strjoin("", "T_IND");
		ft_memdel((void **)&ret);
		ret = tmp;
	}
	return (ret);
}

void				wrong_arg_type(int valid_type, int current_type, int index)
{
	char const*		expected;

	printf("valid type = %d\n", valid_type);
	expected = get_expected(valid_type);
	if (current_type == 0)
		printf("Command: %s\nUnknown type of argument %d\n", g_on_error.curr_line, index);
	else
		printf("Command: %s\nWrong type of argument %d\n", g_on_error.curr_line, index);
	if (current_type == T_REG)
		printf("Expected: %s\nReal one: T_REG\n", expected);
	else if (current_type == T_DIR)
		printf("Expected: %s\nReal one: T_DIR\n", expected);
	else if (current_type == T_IND)
		printf("Expected: %s\nReal one: T_IND\n", expected);
	on_error_deleter();
	exit(8);
}
