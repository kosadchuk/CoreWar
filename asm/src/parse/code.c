#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdio.h>

#define SKIP(x) ft_memdel((void **)&(x)); continue;
#define TRY_SKIP(x) if (is_skipable((x))) { SKIP(x); }

#define ANALYZE_MARK(x) if ((x) == 1) SKIP(line);
#define ANALYZE_COMMAND(x) if ((x) == 0) { ft_memdel((void **)&line); return (0); }

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

static int		parse_mark(char const *line, t_code *code)
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

static void	print_all_marks(t_code *code)
{
	t_list	*lst;

	lst = code->marks;
	printf("marks:\n");
	while (lst)
	{
		printf("[%s] = %zu\n", ((t_mark *)lst->content)->name, (size_t)((t_mark *)lst->content)->location);
		lst = lst->next;
	}
}

static int	parse_command(char const *line, t_asm *dst)
{
	(void)line;
	(void)dst;
	return (0);
}

int			parse_code(char const *file_content, t_asm *dst, t_ull len)
{
	char	*line;
	t_ull	mark_len;
	t_ull	command_memory;
	t_code	code;

	code.curr_location = 0;
	code.marks = 0;
	while ((line = get_line_from_src(file_content, len, 0)))
	{
		TRY_SKIP(line);
		mark_len = parse_mark(line, &code);
		ANALYZE_MARK(mark_len);
		command_memory = parse_command(mark_len ? line + mark_len - 1 : line, dst);
		ANALYZE_COMMAND(command_memory);
		ft_memdel((void **)&line);
	}
	print_all_marks(&code);
	return (dst->code != 0);
}
