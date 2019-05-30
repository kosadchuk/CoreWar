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
#define CORE_H

# include "op.h"
# include "libft/libft.h"
# include <stdint.h>
# include <stdio.h>
# include "core_errors.h"
# include <sys/uio.h>
# include <fcntl.h>

typedef struct	s_player	t_player;
typedef struct	s_players	t_players;
typedef struct	s_carr		t_carr;
typedef struct	s_op		t_op;

struct				s_player // структура игрока
{
	unsigned int	id;	// его уникальный идентификационный номер
	unsigned int	n_id; // это надо для корректного присвоения id, больше не понадобиться
	char 			name[PROG_NAME_LENGTH + 1]; // имя игрока, для вывода в консоль или визуализатор
	char 			comment[COMMENT_LENGTH + 1]; // его коммент
	int32_t 		size; // размер бота
	unsigned char 	*code; // его executable code для битвы
};

struct				s_carr // структура каретки (еще в стадии разработки)
{
	int 			parrent_id; // номер игрока который породил эту дичь (каретку)
	int 			cur_pos; // текущая позиция каретки
	int				carry; // пока хер знает что
	unsigned int	reg[17]; // структура со всеми командами
	int 			live; // ну, типа жизнь, разберемся..
	int				cur_com; // текущая команда
	int 			cycle; // цикл, не помню для чего
};

struct				s_players // глобальная структура для хранения массива игроков
{
	t_player		**team;
	ssize_t 		len;
	ssize_t 		full;
};

struct				s_op // структура для той здоровой ереси, что находится в самом конце (пока разбираюсь)
{
	char 			*name; //имя команды
	int 			types_num; // сколько разных типов агрументов может принимать
	int				*args; // всякие аргументы которые поддерживает эта команда
	int 			num; // идентификационный номер команды (он и записан в executable code для чемпиона)
	int 			cycles; // колличество циклов до выполнения этой команды
	char 			*comment; // комментарий
	int 			ne_znayu; // название переменной говорит само за себя (еще не дошла)
	int 			tozhe_ne_znayu;
};

t_players			*g_players;
void				pars_av(int ac, char **av);
void				pars_champs(char *file, t_player *player);

//t_op    g_op_tab[] =
//		{
//				{0, 0, {0}, 0, 0, 0, 0, 0},
//				{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
//				{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
//				{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
//				{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
//				{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
//				{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
//				{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
//				{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
//				{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
//				{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},
//				{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
//				{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
//				{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
//				{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1},
//				{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
//				{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0}
//		};

#endif
