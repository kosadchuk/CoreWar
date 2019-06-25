/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:07:02 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/15 14:07:02 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/asm.h"
#include "../../../libft/inc/libft.h"

t_command		*create_command(t_ull id_in_stack, t_ull id_type, char const *args[3], t_ull bytes)
{
	t_command	*ret;

	ret = (t_command *)ft_memalloc(sizeof(t_command));
	ret->id_in_stack = id_in_stack;
	ret->id_type = id_type;
	ret->arg1 = args[0];
	ret->arg2 = args[1];
	ret->arg3 = args[2];
	ret->bytes = bytes;
	return (ret);
}

int				append_command(t_asm *dst, t_command *to_append)
{
	if (!dst || !dst->code || !to_append)
		return (0);
	to_append->starting_byte_index = dst->code->curr_location;
	if (dst->code->commands)
		ft_lstadd_before(&dst->code->commands, ft_lstnew(to_append, sizeof(t_command)));
	else
		dst->code->commands = ft_lstnew(to_append, sizeof(t_command));
	ft_memdel((void **)&to_append);
	return (1);
}
