/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:01:36 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/28 18:10:55 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libft.h"
#include "../inc/asm.h"

t_err_manager_storage	g_on_error;

static void		init_main_vars(t_asm *asmm, char const **file_name,\
				char const **file_content)
{
	asmm->code = 0;
	asmm->comment = 0;
	asmm->comment_size = 0;
	asmm->name = 0;
	asmm->name_size = 0;
	*file_name = 0;
	*file_content = 0;
	g_on_error.to_del = asmm;
	g_on_error.curr_line = 0;
	g_on_error.curr_line = 0;
	g_on_error.file_name = 0;
	g_on_error.file_content = 0;
}

static void		clean_main_vars(t_asm *asmm, char const **file_name,\
				char const **file_content)
{
	ft_memdel((void **)&(asmm->name));
	ft_memdel((void **)&(asmm->comment));
	ft_lstdel(&asmm->code->commands, command_deleter);
	ft_lstdel(&asmm->code->marks, mark_deleter);
	ft_memdel((void **)&(asmm->code));
	ft_memdel((void **)file_name);
	ft_memdel((void **)file_content);
}

int				main(int ac, char **av)
{
	t_asm		asmm;
	char const	*file_name;
	char const	*file_content;

	init_main_vars(&asmm, &file_name, &file_content);
	file_name = pre_run_validation(ac, av);
	file_content = read_file(av[1]);
	if (is_good_end_of_file(file_content) && parse(file_content, &asmm))
	{
		write_file(ft_strjoin(file_name, ".cor"), &asmm);
	}
	clean_main_vars(&asmm, &file_name, &file_content);
	return (0);
}
