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

int				parse(char const *file_content, t_asm *dst)
{//printf("%s\n", __func__);
	t_ull const	len = ft_strlen(file_content);

	get_line_from_src(file_content, 0, 0);
	if (!parse_header(file_content, dst, len))
	{
		wrong_asm_in_file(-1);
		exit(4);
	}
	return (1);
}
