# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/02 14:45:37 by apavlyuc          #+#    #+#              #
#    Updated: 2019/06/02 14:47:59 by apavlyuc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET			:= asm

SRC_DIR			:= src
INC_DIR			:= inc
OBJ_DIR			:= build

CC				:= gcc
CFLAGS			:= -Wall -Werror -Wextra -Ofast -I./$(INC_DIR) -I./../libft/

NORM_CHECK		:= $(shell command -v norminette)

DIRS			:= $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(shell find $(SRC_DIR) -type d))
SRCS			:= $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS			:= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
LIBS			:= ../libft/libft.a

all: libft $(TARGET)

#		Block			#
#	creating $(TARGET)	#
$(TARGET): $(OBJS)
	@$(CC) $(shell find $(OBJ_DIR) -type f -name "*.o") $(LIBS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ_DIR):
	@mkdir -p $(DIRS)

#		Block			#
#	creating libft		#
libft:
	@make -C ../libft

#		Block			#
#	describing commands	#
clean:
	@make clean -C ../libft
	@rm -fR $(OBJ_DIR)

fclean: clean
	@make fclean -C ../libft
	@rm -fR $(TARGET)

re: fclean all

norm:
ifeq (,$(NORM_CHECK))
	@echo "DEUS VULT!!1"
else
	@find . -type f -name "*.[ch]" -exec norminette {} \+
endif
#		end block		#

n: norm
c: clean
f: fclean

.PHONY: all libft clean fclean re norm n c f