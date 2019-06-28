/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 17:16:07 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/28 13:32:38 by apavlyuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/core.h"

int32_t			read_bytes(int32_t pos)
{
	int32_t		res;
	uint8_t		buf[4];
	int			i;

	i = -1;
	while (++i < 4)
	{
		if (pos >= MEM_SIZE)
			pos %= MEM_SIZE;
		else if (pos < 0)
			pos += MEM_SIZE;
		buf[i] = g_vm->map[pos];
		pos++;
	}
	res = 0;
	res |= (unsigned char)buf[0] << 24;
	res |= (unsigned char)buf[1] << 16;
	res |= (unsigned char)buf[2] << 8;
	res |= (unsigned char)buf[3];
	return (res);
}

void			int_to_byte(int32_t nbr, uint8_t *buf)
{
	int8_t		i;
	int32_t		j;
	int32_t		size;

	i = 0;
	j = 3;
	size = 4;
	while (size > 0)
	{
		buf[j] = (uint8_t)((nbr >> i) & 0xFF);
		i += 8;
		j--;
		size--;
	}
}

int32_t			conv_bytes(int size, uint8_t *buf)
{
	int32_t		res;

	res = 0;
	if (size == 4)
	{
		res = (unsigned char)buf[0] << 24;
		res |= (unsigned char)buf[1] << 16;
		res |= (unsigned char)buf[2] << 8;
		res |= (unsigned char)buf[3];
		return ((int32_t)res);
	}
	else if (size == 2)
	{
		res |= (unsigned char)buf[0] << 8;
		res |= (unsigned char)buf[1];
		return ((short)res);
	}
	else if (size == 1)
		return ((unsigned char)buf[0]);
	return (0);
}

int32_t			bytes_in_int(t_prcs *pr, int size)
{
	int			i;
	uint8_t		buf[4];

	i = -1;
	while (++i < size)
	{
		if (pr->cur_pos + 1 >= MEM_SIZE)
			pr->cur_pos = (pr->cur_pos + 1) % MEM_SIZE;
		else if (pr->cur_pos + 1 < 0)
			pr->cur_pos = (pr->cur_pos + 1) + MEM_SIZE;
		else
			pr->cur_pos++;
		buf[i] = g_vm->map[pr->cur_pos];
	}
	return (conv_bytes(size, &(*buf)));
}
