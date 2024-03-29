/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_geters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:07:13 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/30 14:45:43 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/asm.h"
#include "../../../libft/inc/libft.h"
#include "../../../inc/op.h"

extern t_cm_desc const	g_comms[16];

char const		*get_arg(char const *line)
{
	char const	*ret;
	t_ull		copy_to;

	if (!line)
		return (0);
	copy_to = 0;
	while (line[copy_to] && line[copy_to] != SEPARATOR_CHAR &&
		line[copy_to] != COMMENT_CHAR && !ft_isspace(line[copy_to]))
		++copy_to;
	if (copy_to == 0)
		return (0);
	ret = ft_strsub(line, 0, copy_to);
	return (ret);
}

int				get_arg_type(char const *arg)
{
	if (!arg)
		return (0);
	if (is_valid_t_reg(arg))
		return (T_REG);
	if (is_valid_t_dir(arg))
		return (T_DIR);
	if (is_valid_t_ind(arg))
		return (T_IND);
	return (0);
}

t_ull			get_arg_size_in_bytes(int arg_type, t_ull command_type_id)
{
	if (arg_type == T_REG)
		return (1);
	if (arg_type == T_IND)
		return (2);
	if (arg_type == T_DIR)
		return (g_comms[command_type_id].t_dir_size);
	return (0);
}
