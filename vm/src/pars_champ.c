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

#include "../includes/core.h"

void			save_norm_players(void)
{
	int			i;
	int			id;

	i = 0;
	id = 1;
	g_players = new_array(4);
	while (i < g_save_pl->len)
	{
		if (g_save_pl->team[i]->id == id)
		{
			push_array(g_players, g_save_pl->team[i]);
			i = -1;
			id++;
		}
		i++;
	}
}

int32_t			take_magic_header(int fd)
{
	int			size;
	uint8_t		buf[4];
	int32_t		res;

	size = read(fd, &buf, 4);
	if (size == -1 || size < 4)
		ft_error(ERR_FILE_READ);
	res = (unsigned char)buf[0] << 24;
	res |= (unsigned char)buf[1] << 16;
	res |= (unsigned char)buf[2] << 8;
	res |= (unsigned char)buf[3];
	return (res);
}

char			*save_chars(int fd, int str_size)
{
	int			size;
	char		*buff;

	buff = (char*)ft_memalloc(sizeof(char) * str_size + 1);
	size = read(fd, buff, str_size);
	if (size == -1)
		ft_error(ERR_FILE_READ);
	if (size < str_size)
		ft_error(NAME_COMM_ERR);
	buff[str_size + 1] = '\0';
	return (buff);
}

void			pars_champs(char *file, t_player *player)
{
	int			fd;
	int32_t		res;
	char		*tmp;

	fd = open(file, O_RDONLY);
	if ((res = take_magic_header(fd)) != COREWAR_EXEC_MAGIC)
		ft_error(ERR_MG_HEADER);
	ft_strcpy(player->name, tmp = save_chars(fd, PROG_NAME_LENGTH));
	ft_strdel(&tmp);
	if ((res = take_magic_header(fd)) != 0)
		ft_error(MISS_NULL);
	if ((res = take_magic_header(fd)) > CHAMP_MAX_SIZE)
		ft_error(BOT_SIZE);
	player->size = res;
	ft_strcpy(player->comment, tmp = save_chars(fd, COMMENT_LENGTH));
	ft_strdel(&tmp);
	if ((res = take_magic_header(fd)) != 0)
		ft_error(MISS_NULL);
	player->code = ft_memalloc(sizeof(unsigned char*) * player->size);
	ft_memcpy(player->code, tmp = save_chars(fd, player->size),\
	player->size + 1);
	ft_strdel(&tmp);
	close(fd);
}
