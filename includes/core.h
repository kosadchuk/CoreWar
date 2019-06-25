/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:57:47 by kosadchu          #+#    #+#             */
/*   Updated: 2019/05/28 12:57:49 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "op.h"
# include "op_struct.h"
# include "../libft/libft.h"
# include <stdint.h>
# include <stdio.h>
# include "defines.h"
# include <sys/uio.h>
# include <fcntl.h>

typedef struct s_player	t_player;
typedef struct s_players	t_players;
typedef struct s_prcs		t_prcs;
typedef struct s_vm		t_vm;

struct				s_player
{
	unsigned int	id;
	unsigned int	n_id;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	int32_t			size;
	unsigned char	*code;
	int				last_live;
	int				lives_in_cur;
};

struct				s_prcs
{
	int				pr_id;
	int				carry;
	int				parent_id;
	int				cur_op;
	int				last_live_cycle;
	int				cycle_count;
	int				cur_pos;
	int				prev_pos;
	int				reg[REG_NUMBER];
	int				reg_err;
};

struct				s_players
{
	t_player		**team;
	ssize_t			len;
	ssize_t			full;
};

struct				s_vm
{
	uint8_t			map[MEM_SIZE];
	t_player		*last_alive;
	int				cycles;
	int				check_cycle;
	int				count_live_op;
	int				ctd;
	int				prev_ctd;
	int				checks;
};

t_players			*g_players;
t_players			*g_save_pl;
t_vm				*g_vm;
t_list				g_list;
int					g_prc_id;
int					g_dump;
int					g_flag_v;
int					g_flag_v2;
int					g_flag_v3;
void				pars_av(int ac, char **av);
void				pars_champs(char *file, t_player *player);
void				make_map(void);
void				init_vm(void);
void				start_war(void);
void				init_start_positions(void);
int32_t				bytes_in_int(t_prcs *pr, int size);
void				handle_position(t_pr *pr, int step);
void				save_norm_players(void);
void				copy_prcs(t_pr *pr, int32_t pos);
void				pars_process(t_list_elem *prcs);
void				int_to_byte(int32_t nbr, uint8_t *buf);
void				write_in_map(int32_t pos, uint8_t *buf);
int32_t				read_bytes(int32_t pos);
void				validate_champ_name(char *str);
void				save_players(char *pl, int pl_id);
void				check_flag(char **av, int *i);
void				del_ptr(void *content, size_t content_size);
void				print_dump(void);
void				valid_op_args(t_prcs *pr);

#endif
