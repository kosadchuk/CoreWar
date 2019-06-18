/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:01:36 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/02 16:11:40 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/asm.h"
#include "../../libft/inc/libft.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void		write_file(char const* file_name, t_asm *content)
{
	int		fd;

	if (!validate_parsed_data(content))
	{
		ft_memdel((void **)file_name);
		return;
	}
	if ((fd = open(file_name, O_WRONLY | O_CREAT, S_IRWXU)) < 0)
	{
		ft_putendl("Error: can't create file");
		return;
	}
	write_header_in_binary(fd, content);
	write_commands_in_binary(fd, content);
}
