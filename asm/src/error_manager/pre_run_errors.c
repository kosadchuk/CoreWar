/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_run_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:07:30 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/29 17:01:35 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"

#include <stdlib.h>

void	not_enough_args(void)
{
	ft_putendl("Error: not enough arguments.");
	ft_putendl("usage: ./asm file.s");
	exit(1);
}

void	wrong_file_extension(void)
{
	ft_putendl("Error: file must have a name with "
				"at least 1 character and .s extension");
	exit(2);
}
