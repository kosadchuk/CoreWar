/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:01:36 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/02 16:11:40 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../inc/asm.h"

static void	show_file_line_by_line(char const *file_content)
{
	size_t	len;
	char	*line;

	len = ft_strlen(file_content);
	while ((line = get_line_from_src(file_content, len, 0)))
	{
		ft_printf("%s$\n", line);
		ft_memdel((void **)&line);
	}
	get_line_from_src(0, 0, 0);
}

int			main(int ac, char **av)
{
	char	*file_name;
	char	*file_content;

	file_name = pre_run_validation(ac, av);
	ft_putendl(file_name);
	file_content = read_file(av[1]);
	show_file_line_by_line(file_content);
	parse(file_content);
	ft_memdel((void **)&file_name);
	ft_memdel((void **)&file_content);
	return (0);
}
