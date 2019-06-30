# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/30 14:50:43 by apavlyuc          #+#    #+#              #
#    Updated: 2019/06/30 14:53:32 by apavlyuc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	make -C asm all
	make -C vm all
clean:
	make -C asm clean
	make -C vm clean
fclean:
	make -C asm fclean
	make -C vm fclean
