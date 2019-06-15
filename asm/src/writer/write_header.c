#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdio.h>
#include <unistd.h>

void		int_to_bytecode(char *data, int value)
{
	int		i;
	int		size;

	i = 0;
	size = 4;
	while (size)
	{
		data[size - 1] = (char)((value >> i) & 0xFF);
		printf("c = [%c]\n", (char)((value >> i) & 0xFF));
		i += 8;
		size--;
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
	char	*txt;
	int		command_bytes;
	int		i;

	command_bytes = get_exec_code_size(content);
	txt = ft_strnew(sizeof(char) * (16 + 128 + 2048));
	int_to_bytecode(txt, 0xea83f3);
	i = 4;
	ft_memcpy(txt + i, content->name, ft_strlen(content->name));
	i += 128;
	i += 4;
	int_to_bytecode(txt + i, command_bytes);
	i += 4;
	ft_memcpy(txt + i, content->comment, ft_strlen(content->comment));
	i += 2048;
	i = write(fd, txt, i);
	ft_memdel((void **)&txt);
}