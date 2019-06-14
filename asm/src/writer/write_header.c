#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdio.h>
#include <unistd.h>

static void string_two_hex_string(char *input, char **output, int flag)
{
	t_ull	len;
	int		loop;
	int		i;

	printf("input : %s\n", input);
	if (flag == 1)
		len = 128;
	if (flag == 2)
		len = 2048;
	if (flag == 4)
		len = ft_strlen(input);
	*output = ft_memalloc(sizeof(char) * len);
	ft_memset((void *)*output, 0, len);
	i = 0;
	loop = 0;
	while (input[loop] != '\0')
	{
		sprintf((char*)(*output+i),"%02X", input[loop]);
		loop+=1;
		i+=2;
	}
	(*output)[i++] = '\0';
}

static void	decimal10_to_16(char *input, char **output)
{
	
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
	char	*tmp;
	t_ull	len;

	len = write(fd, "00ea83f3", 16);

	string_two_hex_string(content->name, &txt, 1);
	len = write(fd, txt, 128);
	ft_memdel((void **)&txt);

	len = write(fd, "\0\0\0\0", 4);

	tmp = ft_itoa((int)get_exec_code_size(content));
	string_two_hex_string(tmp, &txt, 3);
	len = write(fd, txt, ft_strlen(tmp));
	ft_memdel((void **)&txt);
	ft_memdel((void **)&tmp);

	string_two_hex_string(content->comment, &txt, 2);
	len = write(fd, txt, 2048);
	ft_memdel((void **)&txt);
	(void)len;
}