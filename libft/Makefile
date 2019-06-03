# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kosadchu <kosadchu@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/28 17:47:49 by kosadchu          #+#    #+#              #
#    Updated: 2019/05/07 15:27:45 by kosadchu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=		libft.a
INCLD :=	libft.h

CC :=		clang
CFLAGS :=	-c -Wall -Wextra -Werror

FILES :=	ft_strdup ft_putchar ft_strlen ft_putnbr ft_putstr ft_itoa ft_atoi \
			ft_strcpy ft_strncpy ft_strcat ft_strncat ft_strlcat ft_strchr \
			ft_strsplit ft_strrchr ft_strstr ft_strnstr ft_strcmp ft_strncmp \
			ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_toupper \
			ft_tolower ft_memset ft_bzero ft_memcpy ft_memccpy ft_memmove \
			ft_memchr ft_memcmp ft_memalloc ft_memdel ft_strnew ft_strdel \
			ft_strclr ft_striter ft_striteri ft_strmap ft_strmapi ft_strequ \
			ft_strnequ ft_strsub ft_strjoin ft_strtrim ft_putendl ft_putchar_fd \
			ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_lstnew ft_lstinit \
			ft_lstpop ft_lstpush ft_lstdel ft_lstiter ft_lstmap ft_lstrev ft_lstsort \
			ft_swap ft_words_num ft_sqrt ft_free_array \
			ft_lenint get_next_line ft_error ft_ray ft_printf/cast ft_printf/chars \
			ft_printf/decimal ft_printf/float ft_printf/float2 ft_printf/format \
			ft_printf/ft_itoa_bs_pf ft_printf/ft_printf ft_printf/other_func \
			ft_printf/parsing ft_printf/spec ft_err ft_perror_exit

OBJ :=		cast.o chars.o decimal.o float.o float2.o format.o ft_itoa_bs_pf.o \
			ft_printf.o other_func.o parsing.o spec.o

SRCS :=		$(addsuffix .c, $(FILES))
OBJS :=		$(SRCS:%.c=%.o)

all:		$(NAME)

$(NAME): 	$(OBJS)
	@$(CC) $(CFLAGS) $(SRCS) -I $(INCLD)
	@ar rc $(NAME) $(OBJS)

clean:
	@rm -rf $(OBJS) $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re
