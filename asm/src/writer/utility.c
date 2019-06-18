#include "../../inc/asm.h"
#include "../../inc/op.h"
#include "../../libft/inc/libft.h"

#include <stdio.h>

void				int_to_bytecode(char *data, int value, int bytes)
{
	int				i;

	i = 0;
	printf("bytes in covert function: %d\n", bytes);
	while (bytes)
	{
		data[bytes - 1] = (char)((value >> i) & 0xFF);
		//printf("c = [%c]\n", (char)((value >> i) & 0xFF));
		i += 8;
		bytes--;
	}
}

t_mark				*find_mark(t_list const *marks, char const* label)
{
	t_list const	*tmp;
	t_mark const	*mark;
	t_ull			i;

	if (!marks || !label)
		return (0);
	i = 0;
	if (label[0] == DIRECT_CHAR)
		i = 2;
	if (label[0] == LABEL_CHAR)
		i = 1;
	tmp = marks;
	while (tmp)
	{
		mark = (t_mark *)tmp->content;
		if (ft_strequ(mark->name, label + i))
			return ((t_mark *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}
