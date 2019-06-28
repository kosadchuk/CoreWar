/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_run_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:07:30 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/28 18:22:07 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"

#include <stdlib.h>

void	not_enough_args(void)
{
	ft_putendl("Error: not enough arguments.");
	ft_putendl("usage: ./asm file.cor");
	exit(1);
}

void	wrong_file_extension(void)
{
	ft_putendl("Error: file must have a name with "
				"at least 1 character and .cor extension");
	exit(2);
}
