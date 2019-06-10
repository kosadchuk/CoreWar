/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <kosadchu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 12:45:54 by kosadchu          #+#    #+#             */
/*   Updated: 2019/05/07 14:31:45 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LIBFT_H
# define _LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include "ft_printf/ft_printf.h"

typedef int8_t	t_bool;
enum			{ false, true };

typedef void	(*t_fatal_exit_func)(const char *message);
extern t_fatal_exit_func g_fef;

typedef struct s_list		t_list;
typedef struct s_gnl		t_gnl;
typedef struct s_ray		t_ray;

typedef struct s_list_elem	t_list_elem;

typedef void	(*t_lst_iter_f)(t_list_elem *elem);
typedef t_list_elem *(*t_lst_map_f)(t_list_elem *elem);
typedef t_bool	(*t_lst_sort_f)(const void *left_cnt, const void *right_cnt);
typedef void	(*t_delptr)(void *ptr, size_t ptr_size);

struct					s_list_elem
{
	void				*content;
	size_t				content_size;
	struct s_list_elem	*next;
	struct s_list_elem	*prev;
};

struct					s_list
{
	t_list_elem			*start;
	t_list_elem			*end;
	size_t				list_size;
	t_delptr			del;
};

struct				s_gnl
{
	int				fd;
	char			*st;
	t_gnl			*next;
};

struct				s_ray
{
	void			**arr;
	ssize_t			len;
	ssize_t			full;
};

void				ft_lstinit(t_list *lst, t_delptr del_list_func);
t_list_elem			*ft_lstnew(void const *content, size_t content_size);
t_list_elem			*ft_lstnew_ref(void *content, size_t content_size);
void				ft_lstpush_back(t_list *lst, t_list_elem *new_obj);
void				ft_lstpush_front(t_list *lst, t_list_elem *new_obj);
void				ft_lstpop_back(t_list *lst);
void				ft_lstpop_front(t_list *lst);
void				ft_lstdel(t_list *lst);
void				ft_lstdel_one(t_list_elem **elem, t_delptr f);
void				ft_lstdel_by_obj(t_list *lst, t_list_elem *obj);
void				ft_lstiter(t_list *lst, t_lst_iter_f f);
t_list				ft_lstmap(t_list *lst, t_lst_map_f f);
void				ft_lstrev(t_list *lst);
void				ft_lstsort(t_list *lst, t_lst_sort_f f);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
__int128_t			ft_atoi(const char *str);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_words_num(char const *s, char c);
void				ft_swap(int *a, int *b);
int					ft_sqrt(int nb);
void				ft_free_array(char **c);
int					ft_lenint(__int128_t n);
char				*ft_itoa_bs_pf(__int128_t d, uintmax_t u, int base);
int					ft_printf(const char *f, ...);
int					get_next_line(const int fd, char **line);
void				ft_error(char *errstr);
void				*new_array(size_t size);
void				*push_array(void *dst, void *src);
void				ft_err(int num);
void				ft_perror_exit(const char *message);

#endif
