/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:39:31 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/02 16:11:45 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdio.h>
#include <stdlib.h>

#define SKIP(x) ft_memdel((void **)&(x)); continue;
#define TRY_SKIP(x) if (is_skipable((x))) { SKIP(x); }

#define ANALYZE_MARK(x) if ((x) == 1) { SKIP(line); }
#define ANALYZE_COMMAND(x) if ((x) == 0) { ft_memdel((void **)&line); return (0); }

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

static int	parse_code(char const *file_content, t_asm *dst, t_ull len)
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
		command_memory = parse_command(mark_len ? line + mark_len : line, dst);
		ANALYZE_COMMAND(command_memory);
		code.curr_location += command_memory;
		ft_memdel((void **)&line);
	}
	print_all_marks(&code);
	return (dst->code != 0);
}

int				parse(char const *file_content, t_asm *dst)
{//printf("%s\n", __func__);
	t_ull const	len = ft_strlen(file_content);

	get_line_from_src(file_content, 0, 0);
	if (!parse_header(file_content, dst, len))
	{
		wrong_asm_in_file(4);
		exit(4);
	}
	if (!parse_code(file_content, dst, len))
	{
		wrong_asm_in_file(5);
		exit(5);
	}
	return (1);
}
