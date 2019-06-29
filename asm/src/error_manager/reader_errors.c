/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:07:27 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/28 18:23:27 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <stdlib.h>

extern t_err_manager_storage g_on_error;

void	fail_to_open_file(void)
{
	ft_memdel((void **)&g_on_error.file_name);
	ft_putendl("Error: failed to open the file.");
	ft_putendl("Probably you have not enough rights, or file doesn't exist.");
	exit(3);
}

void	missed_new_line(void)
{
	ft_memdel((void **)&g_on_error.file_name);
	ft_memdel((void **)&g_on_error.file_content);
	ft_putendl("missed new line at the end of file");
	exit(4);
}
