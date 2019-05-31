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
typedef struct	s_kar		t_kar;
typedef struct	s_karlist	t_karlist;
typedef struct	s_op_tab	t_op_tab;
typedef struct	s_virt		t_virt;

typedef enum	e_b
{
	TRUE,
	FALSE
}				t_b;

struct				s_player // структура игрока
{
	unsigned int	id;	// его уникальный идентификационный номер
	unsigned int	n_id; // это надо для корректного присвоения id, больше не понадобиться
	char 			name[PROG_NAME_LENGTH + 1]; // имя игрока, для вывода в консоль или визуализатор
	char 			comment[COMMENT_LENGTH + 1]; // его коммент
	int32_t 		size; // размер бота
	unsigned char 	*code; // его executable code для битвы
	int 			last_live;
};

struct				s_kar // структура каретки (еще в стадии разработки)
{
	int 			id; // уникальный номер каретки
	t_b				carry; // флаг, который могут изменять некоторые операции. Изначально иниц. false;
	int 			parrent_id; // номер игрока который породил эту дичь (каретку)
	int				cur_op; // код операции на которой стоит каретка
	int 			last_live_cycle; // цикл, в котором в последний раз была выполнена операция live
	int 			cycle_count; // колличество циклов, оставшиеся до выполнения операции на которой стоит каретка
	int 			cur_pos; // текущая позиция каретки
	int 			byte_step; //колл. байт которые нужно будет перешагнуть, чтобы оказаться на следующей операции
	unsigned int	reg[REG_NUMBER]; // структура со всеми командами
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
	uint8_t 		types_num; // сколько разных типов агрументов может принимать
	uint8_t			args[3]; // всякие аргументы которые поддерживает эта команда
	uint32_t 		num; // идентификационный номер команды (он и записан в executable code для чемпиона)
	uint32_t 		cycles; // колличество циклов до выполнения этой команды
	char 			*comment; // комментарий
	uint8_t 		args_code;
	uint8_t			mod_carry;
//	uint8_t 		dir_size;
};

struct 				s_virt
{
	uint8_t			map[MEM_SIZE]; // арена размером 4096 байт
	int				last_alive; // последний игрок, подавший признаки жизни
	int 			cycles_count; // колличество циклов начиная с начала битвы
	int 			count_live_op; // колл. выполненых операций live за последний период длиной в cycles_to_die
	int 			cycles_to_die; // длительность периода до проверки
	int 			check_count; // колл. проведенных проверок
};

struct 				s_karlist
{
	t_kar			**kars;
	ssize_t 		len;
	ssize_t 		full;
};

t_players			*g_players;
t_virt				*g_virt;
t_kar				*g_karlist;
void				pars_av(int ac, char **av);
void				pars_champs(char *file, t_player *player);
void				make_map(void);
void				init_virt(void);

//static t_op_tab    g_op_tab[17] = {
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
