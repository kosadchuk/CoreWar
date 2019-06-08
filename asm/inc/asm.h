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

typedef struct	s_pair
{
	char		*start;
	char		*end;
}				t_pair;

char		*pre_run_validation(int const ac, char **av);
/*
**				parser/
*/
int			parse(char const *file_content, t_asm *dst);
int			parse_name(char const *file_content, void **name, t_ull *name_size);
int			parse_comment(char const *file_content, void **comment, t_ull *comment_size);
int			parse_code(char const *file_content, void **code, t_ull *code_size);
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
**				utility.c
*/
int			is_white_space_only(char const *line);
/*
**				error.c
*/
void		not_enough_args();
void		wrong_file_extension();
void		wrong_asm_in_file();

#endif