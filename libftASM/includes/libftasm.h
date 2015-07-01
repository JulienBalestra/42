#ifndef LIBFTASM_H
# define LIBFTASM_H
# include <strings.h>
# include <stdlib.h>


int	ft_isalpha(int c);
int	ft_isdigit(int c);
int	ft_isalnum(int c);
int	ft_isascii(int c);
int	ft_isblank(int c);
int	ft_isprint(int c);
int	ft_islower(int c);
int	ft_isupper(int c);
int	ft_toupper(int c);
int	ft_tolower(int c);

size_t ft_strlen(char *str);
void ft_bzero(void *s, size_t n);
int ft_puts(const char *s);
void    *memset(void *s, int c, size_t n);
void		*ft_memalloc(size_t size);
char		*ft_strcat(char *dest, const char *src);
void *memcpy(void *dest, const void *src, size_t n);





#endif
