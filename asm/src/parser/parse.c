/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:39:31 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/30 14:46:29 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdlib.h>

#define SKIP(x) ft_memdel((void **)&(x)); continue;
#define TRY_SKIP(x) if (is_skipable((x))) { SKIP(x); }

#define ANALYZE_MARK(x) if ((x) == 1) { SKIP(line); }
#define ANALYZE_COMMAND(x) if ((x) == 0) {ft_memdel((void **)&line);return(0);}

extern t_err_manager_storage g_on_error;

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
