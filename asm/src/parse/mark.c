#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdio.h>

static void	add_to_marks(t_list	**lst, t_mark *mark)
{
	if (*lst)
		ft_lstadd_before(lst, ft_lstnew((void *)mark, sizeof(t_mark)));
	else
		*lst = ft_lstnew((void *)mark, sizeof(t_mark));
	ft_memdel((void **)&mark);
}

static t_mark	*create_mark(char const *name, t_ull curr_location)
{
	t_mark		*ret;

	ret = (t_mark *)ft_memalloc(sizeof(t_mark));
	ret->location = curr_location;
	ret->name = name;
	return (ret);
}

static int	contains_in_alphabet(char c)
{
	return (c != '\0' && c != ':');
}

static char const	*get_mark_name(char const *line)
{
	char const		*ret;

	skip_whitespaces(&line);
	ret = line;
	while (contains_in_alphabet(*line))
		line++;
	if (ret == line)
		return (0);
	if (*line == ':')
		ret = ft_strsub(ret, 0, line - ret);
	else
		ret = 0;
	return (ret);
}

int				parse_mark(char const *line, t_code *code)
{
	char const	*name;
	t_ull		name_len;

	if (!(name = get_mark_name(line)))
		return (0);
	add_to_marks(&code->marks, create_mark(name, code->curr_location));
	skip_whitespaces(&line);
	name_len = ft_strlen(name);
	line += name_len + 1;
	skip_whitespaces(&line);
	if (*line == '#' || *line == '\0')
		return (1);
	return (name_len + 1);
}
