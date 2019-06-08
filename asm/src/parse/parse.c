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

int		parse(char const *file_content, t_asm *dst)
{
	if (!parse_header(file_content, ".name", &(dst->name), &dst->name_size))
	{
		ft_putendl("Error while parse header (probably .name)");
		return (0);
	}
	printf(".name = [%s]\n", (char *)dst->name);
	if (!parse_header(file_content, ".comment", &(dst->comment), &dst->comment_size))
	{
		ft_putendl("Error while parse header (probably .comment)");
		return (0);
	}
	printf(".comment = [%s]\n", (char *)dst->comment);
	if (!parse_code(file_content, &(dst->code), &dst->code_size))
	{
		ft_putendl("Error while parse code");
		return (0);
	}
	return (1);
}
