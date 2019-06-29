/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:53:13 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/28 18:15:47 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"
#include "../libft/inc/libft.h"
#include "../inc/op.h"

#include <unistd.h>
#include <fcntl.h>

extern t_err_manager_storage g_on_error;

int					is_good_end_of_file(char const *file_content)
{
	char const		*last_line;

	last_line = ft_strrchr(file_content, '\n');
	if (last_line)
		last_line++;
	skip_whitespaces(&last_line);
	if (*last_line == '\0' || *last_line == COMMENT_CHAR)
		return (1);
	missed_new_line();
	return (0);
}

char				*get_line_from_src(char const *src,\
					t_ull src_len, int flag_reset)
{
	static t_ull	start = 0;
	char			*ret;
	char			*new_line_char;

	if (flag_reset)
	{
		start = 0;
		return (0);
	}
	if (start >= src_len)
		return (0);
	new_line_char = ft_strchr(src + start, '\n');
	if (new_line_char)
	{
		ret = ft_strsub(src, start, new_line_char - src - start);
		start = new_line_char - src + 1;
	}
	else
	{
		ret = ft_strsub(src, start, src_len - start);
		start = src_len;
	}
	return (ret);
}

char				*read_file(char const *file_name)
{
	char			*ret;
	char			*tmp;
	char			buffer[102400];
	t_ull			var[2];
	int				fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		fail_to_open_file();
	ret = (char *)ft_memalloc(sizeof(char));
	var[0] = 0;
	while ((var[1] = read(fd, buffer, 102399)) > 0)
	{
		buffer[var[1]] = 0;
		tmp = ret;
		ret = (char *)ft_memalloc(sizeof(char) * (var[0] + var[1] + 1));
		ft_bzero(ret, var[0] + var[1] + 1);
		ft_memcpy(ret, tmp, var[0]);
		ft_memcpy(ret + var[0], buffer, var[1]);
		var[0] += var[1];
		ft_memdel((void **)&tmp);
	}
	ret[var[0]] = '\0';
	g_on_error.file_content = ret;
	return (ret);
}
