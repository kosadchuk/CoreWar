#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

int				is_white_space_only(char const *line)
{
	t_ull		i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int			get_count(char const *line, char c)
{
	int		ret;

	ret = 0;
	while (*line)
	{
		if (*line == c)
			ret++;
		++line;
	}
	return (ret);
}

int				get_br(char const *line, int reset)
{
	static int	br = 0;

	if (reset)
		br = 0;
	if (!line)
		return (br);
	br += get_count(line, '\"');
	return (br);
}
