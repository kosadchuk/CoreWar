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

#include "../libft/inc/libft.h"
#include "../inc/asm.h"

// static void	show_file_line_by_line(char const *file_content)
// {
// 	t_ull	len;
// 	char	*line;

// 	len = ft_strlen(file_content);
// 	while ((line = get_line_from_src(file_content, len, 0)))
// 	{
// 		ft_putendl(line);
// 		ft_memdel((void **)&line);
// 	}
// 	get_line_from_src(0, 0, 0);
// }

static void	init_main_vars(t_asm *_asm, char **file_name, char **file_content)
{
	_asm->code = 0;
	_asm->comment = 0;
	_asm->comment_size = 0;
	_asm->name = 0;
	_asm->name_size = 0;
	*file_name = 0;
	*file_content = 0;
}

static void	clean_main_vars(t_asm *_asm, char **file_name, char **file_content)
{
	ft_memdel((void **)&(_asm->name));
	ft_memdel((void **)&(_asm->comment));
	ft_memdel((void **)&(_asm->code));
	ft_memdel((void **)file_name);
	ft_memdel((void **)file_content);
}

int			main(int ac, char **av)
{
	t_asm	_asm;
	char	*file_name;
	char	*file_content;

	init_main_vars(&_asm, &file_name, &file_content);
	file_name = pre_run_validation(ac, av);
	file_content = read_file(av[1]);
	if (is_good_end_of_file(file_content) && parse(file_content, &_asm))
	{
		write_file(file_name, &_asm);
	}
	clean_main_vars(&_asm, &file_name, &file_content);
	return (0);
}
