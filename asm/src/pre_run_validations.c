/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_run_validations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:30:30 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/28 18:11:40 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libft.h"
#include "../inc/asm.h"

extern t_err_manager_storage g_on_error;

static char		*get_file_name_without_extension(char const *file_name)
{
	char		*ret;
	char const	*last_dot = ft_strrchr(file_name, '.');

	if (last_dot == file_name || !ft_strequ(last_dot, ".s"))
		wrong_file_extension();
	ret = ft_strsub(file_name, 0, last_dot - file_name);
	g_on_error.file_name = ret;
	return (ret);
}

char			*pre_run_validation(int const ac, char **av)
{
	if (ac < 2)
		not_enough_args();
	return (get_file_name_without_extension(av[1]));
}
