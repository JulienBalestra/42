NAME = libfts.a
CFLAGS = -f
LFLAGS = ar rc
CC = nasm
RM = rm -f
INC_DIR = includes
OBJ_DIR = .objects
SRC_DIR = srcs

SRCS = 	   \
ft_isalnum.s \
ft_isalpha.s \
ft_isascii.s \
ft_isblank.s \
ft_isdigit.s \
ft_islower.s \
ft_isupper.s \
ft_toupper.s \
ft_tolower.s \
ft_isprint.s \
ft_strlen.s	\
ft_bzero.s \
ft_puts.s \
ft_memset.s \
ft_memalloc.s \
ft_strcat.s \
ft_memcpy.s \
ft_strdup.s \
ft_cat.s	\
ft_abs.s \
ft_square.s

OBJS = $(patsubst %.s, $(OBJ_DIR)/%.o, $(SRCS))

PREFIX =

UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
	CFLAGS += elf64
	PREFIX = -dLINUX=1
else
	CFLAGS += macho64
	PREFIX = --prefix _ -dOSX=1
endif

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(LFLAGS) $(NAME) $(OBJS)

$(OBJ_DIR)/%.o	:	$(addprefix $(SRC_DIR)/, %.s)
	$(CC) $(CFLAGS) -o $@ $(PREFIX) $^

$(OBJ_DIR)	:
	mkdir -p $(OBJ_DIR)

test:
	gcc -o test main.c $(NAME) -I $(INC_DIR)

.phony: clean re fclean

fclean: clean
	rm -rf $(OBJ_DIR)
	$(RM) $(NAME)

clean:
	$(RM) $(OBJS) test

re: fclean all

fre: fclean all test
