NAME = libfts.a
CFLAGS = -f
LFLAGS = ar rc
CC = nasm
RM = rm -f
INCLUDES = includes
OBJSDIR = .objects
SRCSDIR = srcs

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
ft_memalloc.s


OBJS = $(patsubst %.s, $(OBJSDIR)/%.o, $(SRCS))

PREFIX =

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	CFLAGS += elf64
	PREFIX = -dLINUX=1
else
	CFLAGS += macho64
	PREFIX = --prefix _ -dOSX=1
endif

all: $(NAME)

$(NAME): $(OBJSDIR) $(OBJS)
	$(LFLAGS) $(NAME) $(OBJS)

$(OBJSDIR)/%.o	:	$(addprefix $(SRCSDIR)/, %.s)
	$(CC) $(CFLAGS) -o $@ $(PREFIX) $^

$(OBJSDIR)	:
	mkdir -p $(OBJSDIR)

test:
	gcc -o test main.c $(NAME) -I $(INCLUDES)

.phony: clean re fclean

fclean: clean
	rm -rf $(OBJSDIR)
	$(RM) $(NAME)

clean:
	$(RM) $(OBJS) test

re: fclean all
