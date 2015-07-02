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

NAME = libft
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
INC_DIR = includes/
SRC_DIR = srcs/
OBJ_DIR = .objects/
OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
TARGET = $(NAME).a
ENV = $(shell uname -s)


CL_CYAN = \033[0;36m
CL_GREED = \033[0;32m
CL_RED = \033[0;31m
CL_WHITE = \033[0m


SRC =               \
ft_absint.c			\
ft_atoi.c           \
ft_bubble_sort.c	\
ft_bzero.c			\
ft_isalnum.c        \
ft_isalpha.c        \
ft_isascii.c        \
ft_isblank.c        \
ft_isdigit.c        \
ft_isprint.c        \
ft_itoa.c			\
ft_lstiter.c		\
ft_lstmap.c			\
ft_lstadd_end.c		\
ft_lstdel.c			\
ft_lstdelone.c		\
ft_lstadd.c			\
ft_lstnew.c			\
ft_lstsplit.c		\
ft_memalloc.c		\
ft_memccpy.c		\
ft_memchr.c			\
ft_memcmp.c			\
ft_memcpy.c			\
ft_memdel.c			\
ft_memmove.c		\
ft_memset.c			\
ft_nbrlen.c			\
ft_putchar.c        \
ft_putchar_fd.c		\
ft_putendl.c		\
ft_putnbr.c         \
ft_putnbr_fd.c		\
ft_putstr.c         \
ft_putstr_fd.c		\
ft_strcasestr.c		\
ft_strcat.c			\
ft_strchr.c			\
ft_strclr.c			\
ft_strcmp.c			\
ft_strcpy.c			\
ft_strdel.c			\
ft_strnew.c			\
ft_strdup.c			\
ft_strequ.c			\
ft_striter.c		\
ft_striteri.c		\
ft_strjoin.c		\
ft_strlcat.c		\
ft_putendl_fd.c		\
ft_strlen.c         \
ft_strmap.c			\
ft_strmapi.c		\
ft_strncat.c		\
ft_strncmp.c		\
ft_strncpy.c		\
ft_strndup.c		\
ft_strnequ.c		\
ft_strnstr.c		\
ft_strrchr.c		\
ft_strsplit.c		\
ft_strstr.c			\
ft_strsub.c			\
ft_strtrim.c		\
ft_tolower.c        \
ft_toupper.c        


.PHONY: all clean fclean re

default: all

all: $(NAME)
	@echo " # ft : Job done  $(shell pwd)/$(CL_GREED)$(TARGET)$(CL_WHITE)"

$(NAME): $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJS)
	@echo " + ft : Creating  $(CL_GREED)$@$(CL_WHITE) $(shell sleep 0.1)"
	@ar -rcv $(TARGET) $(OBJS) > /dev/null
	@ranlib $(TARGET)

clean:
	@echo " $(shell\
				if [ -d $(OBJ_DIR) ];\
				then\
					echo "- ft : Removing  $(CL_RED)$(OBJ_DIR)$(CL_WHITE) with$(CL_RED)";\
					ls $(OBJ_DIR) | wc -w; echo "$(CL_WHITE)*.o";\
					rm -Rf $(OBJ_DIR);\
				else\
					echo "# ft : Nothing to clean";\
				fi)"


fclean: clean
	@echo " $(shell\
    				if [ -f $(TARGET) ];\
    				then\
    					echo "- ft : Removing  $(CL_RED)$(TARGET)$(CL_WHITE)";\
    					rm -f $(TARGET);\
    				else\
    					echo "# ft : Nothing to fclean";\
    				fi)"


re: fclean all 

$(addprefix $(OBJ_DIR), %.o): $(addprefix $(SRC_DIR), %.c)
	@echo " + ft : Compiling $(CL_CYAN)$(OBJ_DIR) < $^$(CL_WHITE)"
	@$(CC) -I $(INC_DIR) $(CFLAGS) -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	$(shell sleep 0.1 ; cp $(SRC_DIR)/$(ENV)/* $(SRC_DIR) ; sleep 0.1)
	@echo " # ft : $(ENV) kernel"
	@echo " + ft : Creating  $(CL_GREED)$(OBJ_DIR)$(CL_WHITE)$(CL_WHITE)"
