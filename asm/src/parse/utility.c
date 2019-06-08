#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

int			is_white_space_only(char const *line)
{
	t_ull	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}
