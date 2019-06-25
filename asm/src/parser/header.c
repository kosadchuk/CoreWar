/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:06:56 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/15 14:06:56 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"
#include "../../inc/op.h"

#include <stdlib.h>
#include <stdio.h>

#define SKIP(x) ft_memdel((void **)&(x)); continue;
#define TRY_SKIP(x) if (is_skipable((x))) { SKIP(x); }

#define STREQU(x, y) ft_strequ((x), (y))

#define PARSE_NAME(x) try_parse_header(file_content, line, x, &dst->name);
#define PROCESS_NAME() PARSE_NAME(".name");
#define TRY_PARS_NAME(x) if (STREQU(x, ".name")){ PROCESS_NAME(); }

#define PARSE_COMMENT(x) try_parse_header(file_content, line, x, &dst->comment);
#define PROCESS_COMMENT() PARSE_COMMENT(".comment");
#define TRY_PARS_COMMENT(x) if (STREQU(x, ".comment")){ PROCESS_COMMENT(); }

extern t_err_manager_storage g_on_error;

static int			has_errors(char const* str)
{
	char const		*end;

	if (!(end = ft_strchr(str, '\"')))
		return (0);
	end += 1;
	skip_whitespaces(&end);
	if (*end == COMMENT_CHAR || *end == '\0')
		return (0);
	return (1);
}

static char const	*get_header_part(char const *line)
{
	skip_whitespaces(&line);
	if (ft_strlen(line) > 5 && !ft_memcmp((void *)line, (void *)".name", 5))
	{
		line += 5;
		skip_whitespaces(&line);
		return (*line == '\"' ? ".name" : 0);
	}
	if (ft_strlen(line) > 8 && !ft_memcmp((void *)line, (void *)".comment", 8))
	{
		line += 8;
		skip_whitespaces(&line);
		return (*line == '\"' ? ".comment" : 0);
	}
	return (0);
}

static char			*get_full_field(char const *file_content, char const *curr)
{
	t_ull const		len = ft_strlen(file_content);
	char			*line;
	char			*ret;
	char			*tmp;
	char			*end;

	ret = ft_strdup(curr);
	while ((line = get_line_from_src(file_content, len, 0)))
	{
		if (has_errors(line))
			break;
		if ((end = ft_strchr(line, '\"')))
		{
			tmp = ft_strsub(line, 0, end - line);
			end = ft_strjoin(ret, tmp);
			mass_memdel((void *)ret, (void *)tmp, (void *)line, 0);
			return (end);
		}
		tmp = ret;
		ret = ft_strjoin(ret, line);
		mass_memdel((void *)tmp, (void *)line, 0, 0);
	}
	mass_memdel((void *)ret, (void *)line, 0, 0);
	return (0);
}

void				try_parse_header(char const *file_content, char const *curr, char const *part, void **dst)
{
	char			*end;

	if (*dst)
	{
		ft_memdel((void **)&curr);
		wrong_header_in_file(1);
	}
	skip_whitespaces(&curr);
	curr += ft_strlen(part);
	skip_whitespaces(&curr);
	curr += 1;
	if (has_errors(curr))
		return;
	if ((end = ft_strchr(curr, '\"')))
		*dst = ft_strsub(curr, 0, ft_strlen(curr) - ft_strlen(end));
	else
		*dst = get_full_field(file_content, curr);
	if (!*dst)
		wrong_header_in_file(2);
	//printf("%s = [%s]\n", part, (char *)*dst);
}

int					parse_header(char const *file_content, t_asm *dst, t_ull len)
{
	char			*line;
	char const		*header_part;
	int				breaker;

	breaker = 0;
	while ((line = get_line_from_src(file_content, len, 0)))
	{
		g_on_error.index_line++;
		g_on_error.curr_line = line;
		TRY_SKIP(line);
		header_part = get_header_part(line);
		++breaker;
		TRY_PARS_NAME(header_part);
		TRY_PARS_COMMENT(header_part);
		ft_memdel((void **)&line);
		if (breaker == 2)
			break;
	}
	return (dst->name && dst->comment);
}
