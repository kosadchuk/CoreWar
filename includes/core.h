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
# include "core_errors.h"
# include <sys/uio.h>
# include <fcntl.h>

typedef struct	s_player	t_player;
typedef struct	s_players	t_players;
typedef struct	s_prcs		t_prcs;
typedef struct	s_vm		t_vm;

struct				s_player // структура игрока
{
	unsigned int	id;	// его уникальный идентификационный номер
	unsigned int	n_id; // это надо для корректного присвоения id, больше не понадобиться
	char 			name[PROG_NAME_LENGTH + 1]; // имя игрока, для вывода в консоль или визуализатор
	char 			comment[COMMENT_LENGTH + 1]; // его коммент
	int32_t 		size; // размер бота
	unsigned char 	*code; // его executable code для битвы
	int 			last_live; // последняя жизнь
	int 			lives_in_cur; // колл жизней в текущий период
};

struct				s_prcs // структура каретки
{
	t_bool			carry; // флаг, который могут изменять некоторые операции. Изначально иниц. false;
	int 			parent_id; // номер игрока который породил эту дичь (каретку)
	int				cur_op; // код операции на которой стоит каретка
	int 			last_live_cycle; // цикл, в котором в последний раз была выполнена операция live
	int 			cycle_count; // колличество циклов, оставшиеся до выполнения операции на которой стоит каретка
	int 			cur_pos; // текущая позиция каретки
	int 			byte_step; //колл. байт которые нужно будет перешагнуть, чтобы оказаться на следующей операции
	int				reg[REG_NUMBER]; // структура со всеми командами
};

struct				s_players // глобальная структура для хранения массива игроков
{
	t_player		**team;
	ssize_t 		len;
	ssize_t 		full;
};

struct 				s_vm
{
	uint8_t			map[MEM_SIZE]; // арена размером 4096 байт
	t_player		*last_alive; // последний игрок, подавший признаки жизни
	int 			cycles; // колличество циклов начиная с начала битвы
	int 			count_live_op; // колл. выполненых операций live за последний период длиной в cycles_to_die
	int 			cycles_to_die; // длительность периода до проверки
	int 			checks; // колл. проведенных проверок
};

t_players			*g_players;
t_vm				*g_vm;
void				pars_av(int ac, char **av);
void				pars_champs(char *file, t_player *player);
void				make_map(void);
void				init_virt(void);
void				start_war(void);
void 				init_ops(void);
void				live(void);

#endif
