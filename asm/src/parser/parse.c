/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:39:31 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/28 13:40:06 by apavlyuc         ###   ########.fr       */
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

extern t_err_manager_storage g_on_error;

void			print_all_parsed(t_code *code)
{
	t_list	*lst;
	t_command	*tmp;

	printf("marks:\n");
	{
		lst = code->marks;
		while (lst)
		{
			printf("[%s] = %zu\n", ((t_mark *)lst->content)->name, (size_t)((t_mark *)lst->content)->location);
			lst = lst->next;
		}
	}
	printf("commands:\n");
	{
		lst = code->commands;
		while (lst)
		{
			tmp = (t_command *)lst->content;
			printf("%zu\t%zu\t[%s]\t\t[%s]\t[%s]\t%zu\n", (size_t)tmp->id_in_stack, (size_t)tmp->id_type,\
					tmp->arg1, tmp->arg2, tmp->arg3, (size_t)tmp->bytes);
			lst = lst->next;
		}
	}
	printf("end printing.\n");
}

static void		init_code(t_code **code)
{
	*code = (t_code *)ft_memalloc(sizeof(t_code));
	(*code)->marks = 0;
	(*code)->curr_location = 0;
	(*code)->commands = 0;
}

static int		parse_code(char const *file_content, t_asm *dst, t_ull len)
{
	char		*line;
	t_ull		mark_len;

	init_code(&dst->code);
	while ((line = get_line_from_src(file_content, len, 0)))
	{
		g_on_error.index_line++;
		g_on_error.curr_line = line;
		TRY_SKIP(line);
		mark_len = parse_mark(line, dst->code);
		ANALYZE_MARK(mark_len);
		ANALYZE_COMMAND(parse_command(mark_len ? line + mark_len : line, dst));
		ft_memdel((void **)&line);
	}
	//print_all_parsed(dst->code);
	return (1);
}

int				parse(char const *file_content, t_asm *dst)
{
	t_ull const	len = ft_strlen(file_content);

	get_line_from_src(file_content, 0, 0);
	if (!parse_header(file_content, dst, len))
		wrong_header_in_file(3);
	if (!parse_code(file_content, dst, len))
		wrong_asm_in_file(4);
	return (1);
}
