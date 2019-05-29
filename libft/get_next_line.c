/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <kosadchu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:12:53 by kosadchu          #+#    #+#             */
/*   Updated: 2019/04/10 14:53:23 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFF_SIZE 5
#define DELIM '\n'
#include "libft.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <stdlib.h>

t_gnl				*nw_elem(int fd, t_gnl **st)
{
	t_gnl			*head;
	t_gnl			*out;

	if (!(*st))
	{
		(*st) = (t_gnl *)ft_memalloc(sizeof(t_gnl));
		(*st)->fd = fd;
	}
	head = (*st);
	while (st)
	{
		if ((*st)->fd == fd)
			break ;
		if ((*st)->next == NULL)
		{
			(*st)->next = (t_gnl *)ft_memalloc(sizeof(t_gnl));
			(*st) = (*st)->next;
			(*st)->fd = fd;
			break ;
		}
		(*st) = (*st)->next;
	}
	out = (*st);
	(*st) = head;
	return (out);
}

int					txt_read(t_gnl **lst)
{
	char			*buf;
	int				bytes;
	char			*tmp;

	if (!(buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (0);
	while ((bytes = read((*lst)->fd, buf, BUFF_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		tmp = (*lst)->st;
		(*lst)->st = ft_strjoin((*lst)->st, buf);
		free(tmp);
		if (ft_strchr(buf, DELIM))
			break ;
	}
	free(buf);
	if (bytes < 0)
		return (-1);
	if ((!(*lst)->st) || ((*lst)->st[0] == '\0' && bytes == 0))
		return (0);
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static t_gnl	*llst;
	t_gnl			*lst;
	int				i;
	int				s;
	char			*tmp;

	if (fd < 0 || !line || (read(fd, 0, 0) < 0))
		return (-1);
	lst = nw_elem(fd, &llst);
	s = txt_read(&lst);
	if (s == 0 || s < 0)
		return (s);
	i = 0;
	while (lst->st[i] && lst->st[i] != DELIM)
		i++;
	if (lst->st[i] == DELIM && (*line = ft_strsub(lst->st, 0, i)))
	{
		tmp = lst->st;
		lst->st = ft_strsub(lst->st, i + 1, ft_strlen(lst->st));
		free(tmp);
		return (1);
	}
	*line = ft_strdup(lst->st);
	ft_strdel(&(lst->st));
	return (1);
}
