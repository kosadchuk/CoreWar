/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:17:08 by apavlyuc          #+#    #+#             */
/*   Updated: 2019/06/28 18:03:42 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/inc/libft_types.h"

# define T_REG 1
# define T_DIR 2
# define T_IND 4

typedef struct	s_cm_desc {
	int		code;
	char	*name;
	int		arg1_type;
	int		arg2_type;
	int		arg3_type;
	int		has_type_code;
	int		t_dir_size;
}				t_cm_desc;

typedef struct	s_command
{
	t_ull		id_in_stack;
	t_ull		id_type;
	char const	*arg1;
	char const	*arg2;
	char const	*arg3;
	t_ull		bytes;
	t_ull		starting_byte_index;
}				t_command;

typedef struct	s_mark
{
	char const	*name;
	t_ull		location;
}				t_mark;

typedef struct	s_code
{
	t_list		*marks;
	t_ull		curr_location;
	t_list		*commands;
}				t_code;

typedef struct	s_asm
{
	t_ull		name_size;
	t_ull		comment_size;
	void		*name;
	void		*comment;
	t_code		*code;
}				t_asm;

typedef struct	s_err_manager_storage
{
	char const	*file_name;
	char const	*file_content;
	t_ull		index_line;
	char const	*curr_line;
	t_asm		*to_del;
}				t_err_manager_storage;

char			*pre_run_validation(int const ac, char **av);
/*
**				parser/
*/
int				parse(char const *file_content, t_asm *dst);
int				parse_header(char const *file_content, t_asm *dst, t_ull len);
int				parse_mark(char const *line, t_code *code);
/*
**				parser/command/
*/
int				parse_command(char const *line, t_asm *dst);
/*
**				parser/command/arg_validation.c
*/
int				is_valid_t_reg(char const *arg);
int				is_valid_t_dir(char const *arg);
int				is_valid_t_ind(char const *arg);
int				compare_arg_types(int command_type_id, int arg_type, int index);
/*
**				parser/command/arg_geters.c
*/
char const		*get_arg(char const *line);
int				get_arg_type(char const *arg);
t_ull			get_arg_size_in_bytes(int arg_type, t_ull command_type_id);
/*
**				parser/command/utility.c
*/
t_command		*create_command(t_ull id_in_stack, t_ull id_type,\
							char const *args[3], t_ull bytes);
int				append_command(t_asm *dst, t_command *to_append);
/*
**				reader.c
*/
char			*read_file(char const *file_name);
char			*get_line_from_src(char const *src, t_ull src_len,\
				int flag_reset);
int				is_good_end_of_file(char const *file_content);
/*
**				writer/writer.c
*/
void			write_file(char const *file_name, t_asm *content);
/*
**				writer/write_header.c
*/
void			write_header_in_binary(int fd, t_asm const *content);
/*
**				writer/write_commands.c
*/
void			write_commands_in_binary(int fd, t_asm const *content);
/*
**				writer/validator.c
*/
int				validate_parsed_data(t_asm const *data);
/*
**				writer/utility.c
*/
t_mark			*find_mark(t_list const *marks, char const *label);
void			int_to_bytecode(char *data, int value, int bytes);
/*
**				utility.c
*/
int				is_skipable(char const *line);
void			skip_whitespaces(char const **str);
void			mass_memdel(void *a, void *b, void *c, void *d);
/*
**				error_manager/pre_run_errors.c
*/
void			not_enough_args();
void			wrong_file_extension();
/*
**				error_manager/reader_errors.c
*/
void			fail_to_open_file();
void			missed_new_line();
/*
**				error_manager/parsing_header_errors.c
*/
void			wrong_header_in_file(int type);
/*
**				error_manager/parsing_command_errors.c
*/
void			wrong_asm_in_file(int type);
void			wrong_command_name(char const *command);
void			wrong_arg_type(int valid_type, int current_type, int index);
/*
**				deletors.c
*/
void			command_deleter(void *content, t_ull size);
void			mark_deleter(void *content, t_ull size);
void			on_error_deleter();
#endif
