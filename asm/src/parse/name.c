#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

static t_ull	is_name_command(char const *line)
{
	t_ull		i;
	t_ull		len;

	i = -1;
	while (line[++i])
	{
		if (ft_isspace(line[i]))
			continue;
		break;
	}
	len = ft_strlen(line + i);
	if (len <= 5)
		return (0);
	if (!ft_memcmp((void *)(line + i), (void *)".name", 5))
		return (i + 5);
	return (0);
}

static char		*get_name(char const *file_content, char const *part)
{
	char		*ret;
	char		*tmp;
	char		*line;
	char		*end;
	t_ull const	len = ft_strlen(file_content);

	ret = ft_strdup(part);
	while ((line = get_line_from_src(file_content, len, 0)))
	{
		if ((end = ft_strchr(line, '\"')))
		{
			tmp = ft_strsub(line, 0, end - line);
			ft_memdel((void **)&line);
			end = ft_strjoin(ret, tmp);
			ft_memdel((void **)&tmp);
			ft_memdel((void **)&ret);
			return (end);
		}
		tmp = ft_strjoin(ret, line);
		ft_memdel((void **)&ret);
		ft_memdel((void **)&line);
		ret = tmp;
	}
	ft_memdel((void **)&ret);
	return (ret);
}

static int		init_name_field(char const *file_content, char const *line, void **name, t_ull *name_size)
{
	t_ull		i;
	char		*end;

	i = -1;
	while (line[++i])
	{
		if (ft_isspace(line[i]))
			continue;
		break;
	}
	if (line[i] != '\"')
		return (0);
	if ((end = ft_strchr(line + ++i, '\"')))
	{
		*name_size = end - line - i;
		*name = (void *)ft_strsub(line + i, 0, *name_size);
	}
	else
	{
		*name = (void *)get_name(file_content, line + i);
		*name_size = ft_strlen((char *)*name);
	}
	return (*name == 0 ? 0 : 1);
}

int				parse_name(char const *file_content, void **name, t_ull *name_size)
{
	t_ull		len;
	t_ull		after_name_index;
	char		*line;
	int			ret;

	ret = 0;
	get_line_from_src(file_content, 0, 1);
	len = ft_strlen(file_content);
	while ((line = get_line_from_src(file_content, len, 0)))
	{
		if (line[0] != '#' && !is_white_space_only(line))
		{
			if ((after_name_index = is_name_command(line)))
			{
				ret = init_name_field(file_content, line + after_name_index, name, name_size);
				ft_memdel((void **)&line);
				break;
			}
		}
		ft_memdel((void **)&line);
	}
	return (ret);
}
