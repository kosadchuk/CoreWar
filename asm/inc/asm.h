/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:17:08 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/02 16:11:36 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/inc/libft.h"

typedef struct	s_asm
{
	t_ull		name_size;
	t_ull		comment_size;
	t_ull		code_size;
	void		*name;
	void		*comment;
	void		*code;
}				t_asm;

char		*pre_run_validation(int const ac, char **av);
char		*parse(char const *file_content, t_asm *dst);
/*
**				reader.c
*/
char		*read_file(char const* file_name);
char		*get_line_from_src(char const *src, t_ull src_len, int flag_reset);
/*
**				writer.c
*/
void		write_file(char const* file_name, t_asm *content);
/*
**				error.c
*/
void		not_enough_args();
void		wrong_file_extension();
void		wrong_asm_in_file();

#endif