/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:53:13 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/02 15:38:20 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"
#include "../../libft/libft.h"

#include <fcntl.h>

char				*get_line_from_src(char const *src, size_t src_len, int flag_reset)
{
	static size_t	start = 0;
	char			*ret;
	char			*new_line_char;

	if (flag_reset)
		start = 0;
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

char				*read_file(char const* file_name)
{
	char			*ret;
	char			*tmp;
	char			buffer[102400];
	size_t			var[2];
	int				fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (0);
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
	return (ret);
}