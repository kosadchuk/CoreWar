/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:56:51 by kosadchu          #+#    #+#             */
/*   Updated: 2019/05/29 14:56:52 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	pars_champs(char *file)
{
	int				fd;
	unsigned char	*buf;

	fd = open(file, O_RDWR);
//	check_magic_header(fd);
}