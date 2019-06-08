#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdlib.h>
#include <stdio.h>

#define CALL_ERR_FLAG(x) wrong_asm_in_file(x); exit(1);
#define CALL_ERR1_IF(x) if (!(is_white_space_only((x)))) { CALL_ERR_FLAG(1); }
#define CALL_ERR2_IF(x) if ((x)) { CALL_ERR_FLAG(2); }
#define CALL_ERR3_IF(x) if (!(is_white_space_only((x)))) { CALL_ERR_FLAG(3); }
#define DOUBLE_MEM_DEL(x, y) ft_memdel((void **)&(x)); ft_memdel((void **)&(y));

static t_ull	is_part_command(char const *line, char const *part)
{
	t_ull		i;
	t_ull		len;
	t_ull const	part_len = ft_strlen(part);

	if ((get_br(0, 0) % 2 && !ft_strchr(line, '\"')) ||
		(get_br(0, 0) % 2 == 0 && get_count(line, '\"') % 2 == 1))
		return (0);
	i = -1;
	while (line[++i])
	{
		if (ft_isspace(line[i]))
			continue;
		break;
	}
	len = ft_strlen(line + i);
	if (len <= part_len)
		return (0);
	if (!ft_memcmp((void *)(line + i), (void *)part, part_len))
		return (i + part_len);
	return (0);
}

static char		*get_part(char const *file_content, char const *part)
{
	char		*ret;
	char		*tmp;
	char		*line;
	char		*end;
	t_ull const	len = ft_strlen(file_content);

	ret = ft_strdup(part);
	while ((line = get_line_from_src(file_content, len, 0)))
	{
		get_br(line, 0);
		if ((end = ft_strchr(line, '\"')))
		{
			tmp = ft_strsub(line, 0, end - line);
			CALL_ERR1_IF(end + 1);
			ft_memdel((void **)&line);
			end = ft_strjoin(ret, tmp);
			DOUBLE_MEM_DEL(tmp, ret);
			return (end);
		}
		tmp = ft_strjoin(ret, line);
		DOUBLE_MEM_DEL(ret, line);
		ret = tmp;
	}
	ft_memdel((void **)&ret);
	return (ret);
}

static int		init_part_field(char const *file_content, char const *line, void **dst, t_ull *dst_size)
{
	t_ull		i;
	char		*end;

	CALL_ERR2_IF(*dst);
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
		*dst_size = end - line - i;
		*dst = (void *)ft_strsub(line + i, 0, *dst_size);
		CALL_ERR3_IF(line + i + *dst_size + 1);
	}
	else
	{
		*dst = (void *)get_part(file_content, line + i);
		*dst_size = ft_strlen((char *)*dst);
	}
	return (*dst == 0 ? 0 : 1);
}

int				parse_header(char const *file_content, char const *part, void **dst, t_ull *dst_size)
{
	t_ull const	len = ft_strlen(file_content);
	t_ull		after_part_index;
	char		*line;
	int			ret;

	ret = get_br(0, 1);
	get_line_from_src(file_content, 0, 1);
	while ((line = get_line_from_src(file_content, len, 0)))
	{
		get_br(line, 0);
		if (line[0] != '#' && !is_white_space_only(line))
		{
			if ((after_part_index = is_part_command(line, part)))
			{
				ret = init_part_field(file_content, line + after_part_index, dst, dst_size);
				if (ret && 0)
				{
					ft_memdel((void **)&line);
					break;
				}
			}
		}
		ft_memdel((void **)&line);
	}
	return (ret);
}
