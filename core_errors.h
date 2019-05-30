/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_errors.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 17:10:21 by kosadchu          #+#    #+#             */
/*   Updated: 2019/05/28 17:10:22 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_ERRORS_H
# define CORE_ERRORS_H

#include "core.h"

# define FLAG_ERR		"ERROR! After flag \"-n\" wrong player number : "
# define FLAG_ERR_2		"Please, try again from 1 to "
# define USAGE			"Usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n"
# define WRONG_N_NUM	"ERROR! The player number can't be more then their count!\n"
# define UNC_COMND		"is unknown command!\n"
# define ERR_FILE_READ	"ERROR in reading champion file!\n"
# define ERR_MG_HEADER	"ERROR! Didn't find or incorrect magic header!\n"
# define NAME_COMM_ERR	"ERROR! Champion's name/comment size so small!\n"
# define MISS_NULL		"ERROR! After name/comment miss NULL bytes!\n"
# define BOT_SIZE		"ERROR! Champion size is too big!\n"

#endif
