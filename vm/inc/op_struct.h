/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <kosadchu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 10:25:13 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 15:35:27 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_STRUCT_H
# define OP_STRUCT_H

# include "core.h"
# include "stdint.h"

typedef struct s_op			t_op;
typedef struct s_arg		t_arg;
typedef struct s_prcs		t_pr;

struct				s_arg
{
	t_arg_type		tp;
	int				sz;
	int32_t			value;
	int32_t			reg_num;
};

struct				s_op
{
	char			*name;
	int				types_num;
	t_arg			args[3];
	int				cycles;
	int				codage;
	int				lable_size;
	void			(*f)(t_pr *, t_op, uint32_t);
};

void				op_live(t_pr *pr, t_op op, uint32_t codage);
void				op_ld(t_pr *pr, t_op op, uint32_t codage);
void				op_st(t_pr *pr, t_op op, uint32_t codage);
void				op_add(t_pr *pr, t_op op, uint32_t codage);
void				op_sub(t_pr *pr, t_op op, uint32_t codage);
void				op_and(t_pr *pr, t_op op, uint32_t codage);
void				op_or(t_pr *pr, t_op op, uint32_t codage);
void				op_xor(t_pr *pr, t_op op, uint32_t codage);
void				op_zjmp(t_pr *pr, t_op op, uint32_t codage);
void				op_ldi(t_pr *pr, t_op op, uint32_t codage);
void				op_sti(t_pr *pr, t_op op, uint32_t codage);
void				op_fork(t_pr *pr, t_op op, uint32_t codage);
void				op_lld(t_pr *pr, t_op op, uint32_t codage);
void				op_lldi(t_pr *pr, t_op op, uint32_t codage);
void				op_lfork(t_pr *pr, t_op op, uint32_t codage);
void				op_aff(t_pr *pr, t_op op, uint32_t codage);

# define RRR	84
# define RDR	100
# define RIR	116
# define RDD	104
# define RID	120
# define RRD	88
# define DRR	148
# define DDR	164
# define DIR	180
# define IRR	212
# define IDR	228
# define IIR 	244
# define DR		144
# define IR		208
# define RR		80
# define RI		112
# define R 		64

static t_op		g_op_tab[] =
{
	{0, 0, {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 0, 0, 0, 0},
	{"live", 1, {{T_DIR, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},\
		10, 0, 4, &op_live},
	{"ld", 2, {{T_DIR | T_IND, 0, 0, 0}, {T_REG, 0, 0, 0}},\
		5, 1, 4, &op_ld},
	{"st", 2, {{T_REG, 0, 0, 0}, {T_IND | T_REG, 0, 0, 0}},\
		5, 1, 4, &op_st},
	{"add", 3, {{T_REG, 0, 0, 0}, {T_REG, 0, 0, 0},\
			{T_REG, 0, 0, 0}}, 10, 1, 4, &op_add},
	{"sub", 3, {{T_REG, 0, 0, 0}, {T_REG, 0, 0, 0},\
			{T_REG, 0, 0, 0}}, 10, 1, 4, &op_sub},
	{"and", 3, {{T_REG | T_DIR | T_IND, 0, 0, 0}, {T_REG | T_IND | T_DIR,\
				0, 0, 0}, {T_REG, 0, 0, 0}}, 6, 1, 4, &op_and},
	{"or", 3, {{T_REG | T_IND | T_DIR, 0, 0, 0}, {T_REG | T_IND | T_DIR,\
				0, 0, 0}, {T_REG, 0, 0, 0}}, 6, 1, 4, &op_or},
	{"xor", 3, {{T_REG | T_IND | T_DIR, 0, 0, 0}, {T_REG | T_IND | T_DIR,\
				0, 0, 0}, {T_REG, 0, 0, 0}}, 6, 1, 4, &op_xor},
	{"zjmp", 1, {{T_DIR, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},\
		20, 0, 2, &op_zjmp},
	{"ldi", 3, {{T_REG | T_DIR | T_IND, 0, 0, 0}, {T_DIR | T_REG, 0, 0, 0},\
			{T_REG, 0, 0, 0}}, 25, 1, 2, &op_ldi},
	{"sti", 3, {{T_REG, 0, 0, 0}, {T_REG | T_DIR | T_IND, 0, 0, 0},\
			{T_DIR | T_REG, 0, 0, 0}}, 25, 1, 2, &op_sti},
	{"fork", 1, {{T_DIR, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},\
		800, 0, 2, &op_fork},
	{"lld", 2, {{T_DIR | T_IND, 0, 0, 0}, {T_REG, 0, 0, 0}}, 10, 1, 4, &op_lld},
	{"lldi", 3, {{T_REG | T_DIR | T_IND, 0, 0, 0}, {T_DIR | T_REG, 0, 0, 0},\
			{T_REG, 0, 0, 0}}, 50, 1, 2, &op_lldi},
	{"lfork", 1, {{T_DIR, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},\
		1000, 0, 2, &op_lfork},
	{"aff", 1, {{T_REG, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},\
		2, 1, 4, &op_aff}
};

#endif
