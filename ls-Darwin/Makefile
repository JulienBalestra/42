# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubalest <jubalest@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/20 11:34:39 by jubalest          #+#    #+#              #
#    Updated: 2015/03/11 12:50:57 by jubalest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libls
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
INC_DIR = includes/
SRC_DIR = srcs/
OBJ_DIR = .objects/
OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
TARGET = $(NAME).a
BIN = ft_ls
ENV = $(shell uname -s)


CL_CYAN = \033[0;36m
CL_GREED = \033[0;32m
CL_RED = \033[0;31m
CL_WHITE = \033[0m


SRC =               \
build_children.c	\
get_args.c			\
get_options.c		\
get_items.c			\
goodies.c			\
create_link.c		\
del_link.c			\
manage_link.c		\
matrix.c			\
matrix_tools.c			\
mini_sort.c             \
recursive.c			\
recursive_in_directory.c			\
display_date.c		\
display_date_tools.c		\
display_hard_link.c	\
display_id.c		\
display_indent.c		\
display_protection.c	\
display_size.c		\
sort.c				\
sort_tools.c				\
indent_date.c		\
long_display.c		\
long_display_misc.c		\
long_display_props.c		\
replay_dir.c            \
short_display.c		\
short_display_misc.c		\
compare.c			\
error.c				\
clean.c				\
terminal_sizing.c	\
find_options.c      \
verbose_error.c

MAIN = srcs/main.c


.PHONY: all clean fclean re

default: all

all: $(NAME)
	@echo " # ls : Job done  $(shell pwd)/$(CL_GREED)$(TARGET)$(CL_WHITE)"
	@echo " # ls : Job done  $(shell pwd)/$(CL_GREED)$(BIN)$(CL_WHITE)"

$(NAME): $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJS)
	@make -C libft/ -j -s
	@echo " + ls : Creating  $(CL_GREED)$@$(CL_WHITE) $(shell sleep 0.1)"
	@ar -rcv $(TARGET) $(OBJS) > /dev/null
	@ranlib $(TARGET)	
	@$(CC) $(CFLAGS) srcs/main.c libls.a libft/libft.a -I $(INC_DIR) -I libft/includes  -o $(BIN)

clean:
	@echo " $(shell\
				if [ -d $(OBJ_DIR) ];\
				then\
					echo "- ls : Removing $(CL_RED)$(OBJ_DIR)$(CL_WHITE) with$(CL_RED)";\
					ls $(OBJ_DIR) | wc -w; echo "$(CL_WHITE)*.o";\
					rm -Rf $(OBJ_DIR);\
				else\
					echo "# ls : Nothing to clean";\
				fi)"
	@make -C libft/ clean -s


fclean: clean
	@echo " $(shell\
					if [ -f libft/libft.a ];\
    					then\
    						echo "- ft : Removing  $(CL_RED)$ libft.a $(CL_WHITE)";\
    						rm -f libft/libft.a;\
					else\
							echo "";\
					fi)"
	@echo " $(shell\
    				if [ -f $(TARGET) ];\
    				then\
    					echo "- ls : Removing  $(CL_RED)$(TARGET)$(CL_WHITE)";\
    					rm -f $(TARGET);\
    				else\
    					echo "# ls : Nothing to fclean";\
    				fi)"
	@echo " $(shell\
					if [ -f $(BIN) ];\
						then\
							echo "- ls : Removing  $(CL_RED)$ $(BIN) $(CL_WHITE)";\
							rm -f $(BIN);\
					else\
							echo "# ft : Nothing to fclean";\
					fi)"

re: fclean all 

$(addprefix $(OBJ_DIR), %.o): $(addprefix $(SRC_DIR), %.c)
	@echo " + ls : Compiling $(CL_CYAN)$(OBJ_DIR) < $^$(CL_WHITE)"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I libft/includes -o $@ -c $<

$(OBJ_DIR):
	@echo " # ls : $(ENV) kernel"
	@echo " + ls : Creating $(CL_GREED)$(OBJ_DIR)$(CL_WHITE)$(CL_WHITE)"
	@mkdir -p $(OBJ_DIR)
