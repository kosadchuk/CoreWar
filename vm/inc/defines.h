/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:10:21 by kosadchu          #+#    #+#             */
/*   Updated: 2019/05/28 17:10:22 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "core.h"

# define ERRR			"ERROR! "
# define USAGE			"Usage: ./corewar "
# define FLAG_ERR ERRR	"After flag \"-n\" wrong player number : "
# define FLAG_ERR_2		"Please, try again from 1 to "
# define USG_TITLE USAGE"[-dump N] || [-v N] || [-n N] || [-p] <champ.cor> ..\n"
# define USG_D USG_TITLE"	-dump N : Dumps memory after N cycles then exits\n"
# define USG_P USG_D	"	-p		: Visualisation\n"
# define USG_N USG_P	"	-n N    : Сhange the order of champions\n"
# define USG_V USG_N	"	-v N    : Shows information\n"
# define USG_V1 USG_V	"		 1 : Show operations\n"
# define USG_V2 USG_V1	"		 2 : Show cycles\n"
# define USG_V3 USG_V2	"		 3 : Show deaths\n"
# define WRONG_N_NUM ERRR"The player number can't be more then their count!\n"
# define UNC_COMND		"is unknown command!\n"
# define ERR_FILE_READ ERRR"in reading champion file!\n"
# define ERR_MG_HEADER ERRR"Didn't find or incorrect magic header!\n"
# define NAME_COMM_ERR ERRR"Champion's name/comment size so small!\n"
# define MISS_NULL ERRR	"After name/comment miss NULL bytes!\n"
# define BOT_SIZE ERRR	"Champion size is too big!\n"
# define ERR_CHAMP_NAME ERRR"-> %s <- is invalid champion name!\n"
# define ERR_DUMP_NUM	"Wrong dump cycles number!\n"
# define ERR_FLAG_V ERRR	"Wrong flag number\n"
# define WINNER			"Contestant %d, \"%s\", has won !\n"
# define DEAD	"cycle : %d Process %d hasn't lived for %d cycles (CTD %d)\n"
# define INTRDC "* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n"
# define OP_LDI "       | -> load from %d + %d = %d (with pc and mod %d)\n"
# define OP_LLDI "       | -> load from %d + %d = %d (with pc and mod %d)\n"
# define STI "P%5d | %s r%d %d %d\n"
# define OP_STI2 STI "       | -> store to %d + %d = %d (with pc and mod %d)\n"

#endif
