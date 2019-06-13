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
#include "../libft/inc/libft.h"

#include <stdio.h>
#include <stdlib.h>

#define T_REG 1
#define T_DIR 2
#define T_IND 4

void		not_enough_args()
{
	ft_putendl("usage: ./asm file.cor");
}

void		wrong_file_extension()
{
	ft_putendl("Error: file must have a name with at least 1 character and .cor extension");
}

void		wrong_asm_in_file(int type)
{
	if (type == 1)
		printf("Error: duplicate .name or .comment file\n");
	if (type == 2)
		printf("Error: .name or .commend without the value\n");
	if (type == 3)
		printf("Smth went wrong while header parsing\n");
	if (type == 4)
		printf("Smth went wrong while commands parsing\n");
	else
	{
		ft_putstr("Error: is seems like there is a faggot in front of monitor: ");
		ft_putnbr(type);
		ft_putendl("");
	}
}

static char const	*get_expected(int expected_arg_types)
{
	char const		*ret;
	char const		*tmp;

	ret = 0;
	if (expected_arg_types & T_REG)
		ret = ft_strdup("T_REG");
	if (expected_arg_types & T_DIR)
	{
		tmp = ft_strjoin(ret, ret == 0 ? "T_DIR" : " or T_DIR");
		ft_memdel((void **)&ret);
		ret = tmp;
	}
	if (expected_arg_types & T_IND)
	{
		tmp = ft_strjoin(ret, ret == 0 ? "T_IND" : " or T_IND");
		ft_memdel((void **)&ret);
		ret = tmp;
	}
	return (ret);
}

void				wrong_arg_type(char const *command, int valid_type, int current_type, int index)
{
	char const*		expected;

	expected = get_expected(valid_type);
	if (current_type == 0)
		printf("Command: %s\nUnknown type of argument %d\n", command, index);
	else
		printf("Command: %s\nWrong type of argument %d\n", command, index);
	if (current_type == T_REG)
		printf("Expected: %s\nReal one: T_REG\n", expected);
	else if (current_type == T_DIR)
		printf("Expected: %s\nReal one: T_DIR\n", expected);
	else if (current_type == T_IND)
		printf("Expected: %s\nReal one: T_IND\n", expected);
	exit(1);
}
