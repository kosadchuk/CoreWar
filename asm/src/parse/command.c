#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdio.h>
#include <stdlib.h>

#define T_REG 1
#define T_DIR 2
#define T_IND 4

static t_ull			g_last_stack_id = 0;
static char const*		commands[] =\
	{
		"live", "ld", "st", "add", "sub", "and", "or", "xor",
		"zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"
	};

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
		while (commands[ret][i])
		{
			if (commands[ret][i] != (*line)[i])
				break;
			++i;
		}
		if (commands[ret][i] == '\0' && (*line)[i] == ' ')
		{
			*line = *line + ft_strlen(commands[ret]);
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

	copy_to = 0;
	while (line[copy_to] && line[copy_to] != ',')
		++copy_to;
	if (line == line + copy_to)
		return (0);
	ret = ft_strsub(line, 0, copy_to);
	return (ret);
}

static int				process_arg(char const **line, char const *args[3], int i)
{
	skip_whitespaces(line);
	args[i] = get_arg(*line);
	if (args[i] == 0)
		return (0);
	*line = *line + ft_strlen(args[i]) + 1;
	return (1);
}

static int				process_bytes_len(char const *args[3], t_ull id_type, t_ull *len)
{
	(void)args;
	(void)id_type;
	(void)len;
	return (1);
}

int						parse_command(char const *line, t_asm *dst)
{
	char const			*args[3] = {0, 0, 0 };
	t_ull				id_type;
	t_ull				bytes_len;
	char				error_code;

	(void)dst;
	(void)g_comms;
	id_type = 0;
	bytes_len = 0;
	error_code = 1;
	error_code &= process_id_type(&line, &id_type);
	error_code &= process_arg(&line, args, 0);
	error_code &= process_arg(&line, args, 1);
	error_code &= process_arg(&line, args, 2);
	error_code &= process_bytes_len(args, id_type, &bytes_len);
	printf("[%s][%s][%s][%s]\n", commands[id_type - 1], args[0], args[1], args[2]);
	++g_last_stack_id;
	return (1);
}
