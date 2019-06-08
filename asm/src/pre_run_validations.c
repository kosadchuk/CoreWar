/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_run_validations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:30:30 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/02 14:53:17 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/asm.h"

static char		*get_file_name_without_extension(char const *file_name)
{
	char		*ret;
	char const	*last_dot = ft_strrchr(file_name, '.');

	if (last_dot == file_name || !ft_strequ(last_dot, ".cor"))
	{
		wrong_file_extension();
		return (0);
	}
	ret = ft_strsub(file_name, 0, last_dot - file_name);
	return (ret);
}

char		*pre_run_validation(int const ac, char **av)
{
	char	*ret;

	if (ac < 2)
	{
		not_enough_args();
		exit(1);
	}
	if (!(ret = get_file_name_without_extension(av[1])))
		exit(2);
	return (ret);
}