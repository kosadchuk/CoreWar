#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdio.h>
#include <stdlib.h>

#define T_REG 1
#define T_DIR 2
#define T_IND 4

static t_ull			g_last_stack_id = 0;

static t_cm_desc const	g_comms[16] =\
{
	{ 0x01, "live",	T_DIR,					0,						0,				0, 4 },
	{ 0x02, "ld",	T_DIR | T_IND,			T_REG,					0,				1, 4 },
	{ 0x03, "st",	T_REG,					T_REG | T_IND,			0,				1, 4 },
	{ 0x04, "add",	T_REG,					T_REG,					T_REG,			1, 4 },
	{ 0x05, "sub",	T_REG,					T_REG,					T_REG,			1, 4 },
	{ 0x06, "and",	T_REG | T_DIR | T_IND,	T_REG | T_DIR | T_IND,	T_REG,			1, 4 },
	{ 0x07, "or",	T_REG | T_DIR | T_IND,	T_REG | T_DIR | T_IND,	T_REG,			1, 4 },
	{ 0x08, "xor",	T_REG | T_DIR | T_IND,	T_REG | T_DIR | T_IND,	T_REG,			1, 4 },
	{ 0x09, "zjmp",	T_DIR,					0,						0,				0, 2 },
	{ 0x0a, "ldi",	T_REG | T_DIR | T_IND,	T_REG | T_DIR,			T_REG,			1, 2 },
	{ 0x0b, "sti",	T_REG,					T_REG | T_DIR | T_IND,	T_REG | T_DIR,	1, 2 },
	{ 0x0c, "fork",	T_DIR,					0,						0,				0, 2 },
	{ 0x0d, "lld",	T_DIR | T_IND,			T_REG,					0,				1, 4 },
	{ 0x0e, "lldi",	T_REG | T_DIR | T_IND,	T_REG | T_DIR,			T_REG,			1, 2 },
	{ 0x0f,	"lfork",T_DIR,					0,						0,				0, 2 },
	{ 0x10,	"aff",	T_REG,					0,						0,				1, 4 }
};

static t_ull			process_id_type(char const **line, t_ull *id_type)
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
				break;
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
	return (0);
}

static char const		*get_arg(char const* line)
{
	char const			*ret;
	t_ull				copy_to;

	if (!line)
		return (0);
	copy_to = 0;
	while (line[copy_to] && line[copy_to] != ',')
		++copy_to;
	if (copy_to == 0)
		return (0);
	ret = ft_strsub(line, 0, copy_to);
	return (ret);
}

static int				process_arg(char const **line, char const *args[3], int i)
{
	skip_whitespaces(line);
	if (**line == '\0')
		return (1);
	args[i] = get_arg(*line);
	if (args[i] == 0)
		return (0);
	*line = *line + ft_strlen(args[i]);
	if (**line)
		*line = *line + 1;
	return (1);
}

static int				is_valid_t_reg(char const *arg)
{
	t_ull				arg_len;

	arg_len = ft_strlen(arg);
	if (*arg != 'r' || arg_len > 3 || arg_len <= 1)
		return (0);
	if (arg_len == 2)
	{
		if (!ft_isalnum(arg[1]) || arg[1] == '0')
			return (0);
	}
	else
	{
		if (!ft_isalnum(arg[1]) || !ft_isalnum(arg[2]) ||
			(arg[1] == '0' && arg[2] == '0'))
			return (0);
	}
	return (1);
}

static int				is_valid_t_dir(char const *arg)
{
	t_ull				arg_len;
	t_ull				i;

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
		if (!ft_isalnum(arg[1]) && arg[1] != '-')
			return (0);
		i = 2;
		while (i < arg_len && ft_isalnum(arg[i]))
			++i;
		if (i != arg_len)
			return (0);
	}
	return (1);
}

static int				is_valid_t_ind(char const *arg)
{
	t_ull				arg_len;
	t_ull				i;

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
		if (!ft_isalnum(arg[0]) && arg[0] != '-')
			return (0);
		i = 1;
		while (i < arg_len && ft_isalnum(arg[i]))
			++i;
		if (i != arg_len)
			return (0);
	}
	return (1);
}

static int				get_arg_type(char const *arg)
{
	if (!arg)
		return (0);
	if (is_valid_t_reg(arg))
		return (T_REG);
	if (is_valid_t_dir(arg))
		return (T_DIR);
	if (is_valid_t_ind(arg))
		return (T_IND);
	return (0);
}

static t_ull			get_arg_size_in_bytes(int arg_type, t_ull command_type_id)
{
	if (arg_type == T_REG)
		return (1);
	if (arg_type == T_IND)
		return (2);
	if (arg_type == T_DIR)
		return (g_comms[command_type_id].t_dir_size);
	return (0);
}

static int				compare_arg_types(char const *command, int command_type_id, int arg_type, int index)
{
	int					needed_type;

	if (index == 0)
		needed_type = g_comms[command_type_id].arg1_type;
	if (index == 1)
		needed_type = g_comms[command_type_id].arg2_type;
	if (index == 2)
		needed_type = g_comms[command_type_id].arg3_type;
	if (arg_type & needed_type || arg_type == needed_type)
		;
	else
	{
		wrong_arg_type(command, needed_type, arg_type, index + 1);
		return (0);
	}
	return (1);
}

static int				process_bytes_len(char const *command, char const *args[3], t_ull id_type, t_ull *len)
{
	t_ull				size;
	int					arg_types[3];
	int					err_code;

	err_code = 1;
	--id_type;
	size = 1;// operation code
	size += g_comms[id_type].has_type_code;
	arg_types[0] = get_arg_type(args[0]);
	err_code &= compare_arg_types(command, id_type, arg_types[0], 0);
	size += get_arg_size_in_bytes(arg_types[0], id_type);
	arg_types[1] = get_arg_type(args[1]);
	err_code &= compare_arg_types(command, id_type, arg_types[1], 1);
	size += get_arg_size_in_bytes(arg_types[1], id_type);
	arg_types[2] = get_arg_type(args[2]);
	err_code &= compare_arg_types(command, id_type, arg_types[2], 2);
	size += get_arg_size_in_bytes(arg_types[2], id_type);
	if (args[0])
		{}//printf("[%s] == [%s]\n", args[0], (arg_types[0] != 1 ? (arg_types[0] == 2 ? "T_DIR" : "T_IND") : "T_REG"));
	if (args[1])
		{}//printf("[%s] == [%s]\n", args[1], (arg_types[1] != 1 ? (arg_types[1] == 2 ? "T_DIR" : "T_IND") : "T_REG"));
	if (args[2])
		{}//printf("[%s] == [%s]\n", args[2], (arg_types[2] != 1 ? (arg_types[2] == 2 ? "T_DIR" : "T_IND") : "T_REG"));
	*len = size;
	return (err_code);
}

static t_command		*create_command(t_ull id_in_stack, t_ull id_type, char const *args[3], t_ull bytes)
{
	t_command			*ret;

	ret = (t_command *)ft_memalloc(sizeof(t_command));
	ret->id_in_stack = id_in_stack;
	ret->id_type = id_type;
	ret->arg1 = args[0];
	ret->arg2 = args[1];
	ret->arg3 = args[2];
	ret->bytes = bytes;
	return (ret);
}

static int				append_command(t_asm *dst, t_command *to_append)
{
	if (!dst || !dst->code)
		return (0);
	if (dst->code->commands)
		ft_lstadd_before(&dst->code->commands, ft_lstnew(to_append, sizeof(t_command)));
	else
		dst->code->commands = ft_lstnew(to_append, sizeof(t_command));
	return (1);
}

int						parse_command(char const *line, t_asm *dst)
{
	char const			*args[3] = { 0, 0, 0 };
	char const			*command;
	t_ull				id_type;
	t_ull				bytes_len;
	char				error_code;

	id_type = 0;
	bytes_len = 0;
	error_code = 1;
	command = line;
	error_code &= process_id_type(&line, &id_type);
	error_code &= process_arg(&line, args, 0);
	error_code &= process_arg(&line, args, 1);
	error_code &= process_arg(&line, args, 2);
	error_code &= process_bytes_len(command, args, id_type, &bytes_len);
	error_code &= append_command(dst, create_command(g_last_stack_id, --id_type, args, bytes_len));
	dst->code->curr_location += bytes_len;
	++g_last_stack_id;
	return (error_code);
}
