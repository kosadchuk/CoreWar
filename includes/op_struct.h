/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 10:25:13 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/03 10:25:15 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_STRUCT_H
# define OP_STRUCT_H

#include <zconf.h>

typedef struct	s_op		t_op;
typedef struct	s_args		t_args;
typedef struct	s_arg		t_arg;
typedef struct	s_ops		t_ops;

struct				s_arg
{

};

struct 				s_args
{

};

//struct 				s_op
//{
//	int 			cycles;
//	int 			lable_size;
//};

//struct				s_ops
//{
//	t_op			**ops;
//	ssize_t 		len;
//	ssize_t 		full;
//};

//t_ops				*g_ops;
struct				s_op // структура для той здоровой ереси, что находится в самом конце (пока разбираюсь)
{
	char 			*name; //имя команды
	int		 		types_num; // сколько разных типов агрументов может принимать
	int				args[3]; // всякие аргументы которые поддерживает эта команда
	int		 		num; // идентификационный номер команды
	int		 		cycles; // колличество циклов до выполнения этой команды
	int				codage; // если codage 1, то у ф-я принимает более одного аргумента, если 0, то только один
	int				lable_size; //указывает на размер агрумента T_DIR (4 либо 2)
};

static t_op    g_op_tab[] =
{
	{0, 0, {0}, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, 0, 4},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, 1, 4},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, 1, 4},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 4},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 4},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, 1, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, 1, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, 1, 4},
	{"zjmp", 1, {T_DIR}, 9, 20, 0, 2},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 1, 2},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 1, 2},
	{"fork", 1, {T_DIR}, 12, 800, 0, 2},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, 1, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, 1, 2},
	{"lfork", 1, {T_DIR}, 15, 1000, 0, 2},
	{"aff", 1, {T_REG}, 16, 2, 1, 4}
};

#endif
