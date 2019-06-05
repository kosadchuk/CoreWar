/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:15:09 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/02 14:55:12 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"
#include "../../libft/libft.h"

void		not_enough_args()
{
	ft_putendl("usage: ./asm file.cor");
}

void		wrong_file_extension()
{
	ft_putendl("file must have a name with at least 1 character and .cor extension");
}

void		wrong_asm_in_file()
{
	ft_putendl("is seems like there is a faggot in front of monitor");
}