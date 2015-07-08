#ifndef LIBFTASM_H
# define LIBFTASM_H
# include <strings.h>

/* part one */
void ft_bzero(void *s, size_t n);
char *ft_strcat(char *dest, const char *src);
int	ft_isalpha(int c);
int	ft_isdigit(int c);
int	ft_isalnum(int c);
int	ft_isascii(int c);
int	ft_isprint(int c);
int	ft_toupper(int c);
int	ft_tolower(int c);
int ft_puts(const char *s);

/* part two */
size_t ft_strlen(char *str);
void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
char *ft_strdup(const char *s);

/* Bonus */
void ft_cat(int fd);

/* Extra */
int	ft_isblank(int c);
int	ft_islower(int c);
int	ft_isupper(int c);
void *ft_memalloc(size_t size);
int ft_abs(int i);
int ft_square(int i);

#endif
