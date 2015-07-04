#include "libftasm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void    ok(void)
{
    printf("\033[0;32m\033[1m.\033[0m");
}

void ko(void)
{
    printf("\033[0;31m\033[1mF\033[0m");
}

int	check_is(int ret, int (*f)(int c), int c, int result)
{
    if (f(c) == result)
    {
        ok();
        return (ret);
    }
    else
    {        
        ko();
        printf("(%i != %i)", f(c), result);
        return (ret + 1);
    }
}

int is_to_something(int ret)
{
    char str[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c";
    char low[] = "abcdefghijklmnopqrstuvwxyz";
    char upp[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    
    printf("\n\nft_isalpha\n");
    for (i = 0 ; i < strlen(str) ; i++)
        ret = check_is(ret, ft_isalpha, str[i], isalpha(str[i]));
            
    printf("\n\nft_isdigit\n");
    for (i = 0 ; i < strlen(str) ; i++)
        ret = check_is(ret, ft_isdigit, str[i], isdigit(str[i]));

    printf("\n\nft_isalnum\n");
    for (i = 0 ; i < strlen(str) ; i++)
        ret = check_is(ret, ft_isalnum, str[i], isalnum(str[i]));

    printf("\n\nft_isblank\n");
    for (i = 0 ; i < strlen(str) ; i++)
        ret = check_is(ret, ft_isblank, str[i], isblank(str[i]));

    printf("\n\nft_isascii\n");
    for (i = 0 ; i < strlen(str) ; i++)
        ret = check_is(ret, ft_isascii, str[i], isascii(str[i]));

    printf("\n\nft_isprint\n");
    for (i = 0 ; i < strlen(str) ; i++)
        ret = check_is(ret, ft_isprint, str[i], isprint(str[i]));

    printf("\n\nft_islower\n");
    for (i = 0 ; i < strlen(low) ; i++)
        ret = check_is(ret, ft_islower, low[i], 1);
    for (i = 0 ; i < strlen(upp) ; i++)
        ret = check_is(ret, ft_islower, upp[i], 0);
                
    printf("\n\nft_isupper\n");
    for (i = 0 ; i < strlen(low) ; i++)
        ret = check_is(ret, ft_isupper, low[i], 0);
    for (i = 0 ; i < strlen(upp) ; i++)
        ret = check_is(ret, ft_isupper, upp[i], 1);
    
    printf("\n\nft_toupper\n");
    for (i = 0 ; i < strlen(low) ; i++)
        ret = check_is(ret, ft_toupper, low[i], low[i] - 32);    
    for (i = 0 ; i < strlen(upp) ; i++)
        ret = check_is(ret, ft_toupper, upp[i], upp[i]);  
          
    printf("\n\nft_tolower\n");
    for (i = 0 ; i < strlen(low) ; i++)
        ret = check_is(ret, ft_tolower, low[i], low[i]);
    for (i = 0 ; i < strlen(upp) ; i++)
        ret = check_is(ret, ft_tolower, upp[i], upp[i] + 32);    
    
    return (ret);
}

int check_strlen(int ret)
{
    char one[] = "123";
    char two[] = "";
    char three[] = "1234567890";
 
    printf("\n\nft_strlen\n");
    if (ft_strlen(one) == 3)
    {
        ok();        
    }
    else
    {
        ko();
        ret++;
    }
    if (ft_strlen(two) == 0)
    {
        ok();        
    }
    else
    {
        ko();
        ret++;
    }
    if (ft_strlen(three) == 10)
    {
        ok();        
    }
    else
    {
        ko();
        ret++;
    }
    return (ret);
}

int check_bzero(int ret)
{
    char *ptr;
    int i = 50;
    
    ptr = NULL;
    printf("\n\nft_bzero\n");    
    ptr = (char *)malloc(sizeof(char) * i);
    ft_bzero(ptr, i);
    while (--i >= 0)
    {
        if (ptr[i] == 0)
            ok();
        else
        {
            ko();
            ret++;
        }
    }    
    return (ret);
}

int check_memset(int ret)
{
    char *ptr;
    int i = 50;
    
    ptr = NULL;
    printf("\n\nft_memset\n");
    ptr = (char *)malloc(sizeof(char) * i);
    ft_memset(ptr, 0, i);
    while (--i >= 0)
    {
        if (ptr[i] == 0)
            ok();
        else
        {
            ko();
            ret++;
        }
    }    
    return (ret);
}

int check_memalloc(int ret)
{
    char *ptr;
    int i = 50;
    int j = 0;
    
    ptr = NULL;
    printf("\n\nft_memalloc\n");
    ptr = ft_memalloc(i);
    while (j < i)
    {
        if (ptr[j] == 0)
            ok();
        else
        {
            ko();
            ret++;
        }
        j++;
    }
    return (ret);
}

int check_strcat(int ret)
{
    char *src;
    char *dest;
    int i = 5;
    int j = 0;
    
    printf("\nft_strcat\n");
    src = (char *)malloc(sizeof(char) * i);
    dest = (char *)malloc(sizeof(char) * (i * 2));
    while (j < i)
    {
        src[j] = 'z';
        dest[j] = 'a';
        j++;
    }
    dest = ft_strcat(dest, src);
    j = 0;
    while (j < i * 2)
    {
        if (j < i && dest[j] == 'a')
            ok();
        else if (dest[j] == 'z')
            ok();
        else
        {
            ko();
            ret++;
        }
        j++;
    }
    return (ret);
}

int check_memcpy(int ret)
{
    char src[] = "abc";
    char dest[] = "rst";
    int i = 0;
    
    printf("\n\nft_memcpy\n");
    ft_memcpy(dest, src, ft_strlen(src));
    while (i < ft_strlen(src))
    {
        if (dest[i] == src[i])
            ok();
        else
        {
            ko();
            ret++;
        }
        i++;
    }
    return (ret);
}

int check_strdup(int ret)
{
    char *src;
    char *dest;
    int i = 3;
    int j = 0;
    
    src = (char *)malloc(sizeof(char) * i);
    while (j < i)
    {
        src[j] = 'a';
        j++;
    }
    dest = NULL;
    printf("\n\nft_strdup\n");
    dest = ft_strdup(src);
    j = 0;
    while (j < i)
    {
        if (dest[j] == src[j])
            ok();
        else
        {
            ko();
            ret++;
        }
        j++;
    }
    return (ret);
}

void check_puts(void)
{
    printf("\n");
    ft_puts("\nft_puts");
    ft_puts("\033[0;32m\033[1m.\033[0m");
    ft_puts(NULL);
    printf("(null) == OK\n");
}

void call_cat(void)
 {
    int fd = 0;
    
    printf("\n\nft_cat\nHello World !");
    fd = open("hello.world", O_RDONLY);
    ft_cat(fd);    
 }
 
int check_power(int ret)
{
    int i = 5;
    int j = 0;
    
    printf("\n\nft_square\n");
    j = ft_square(i);
    if (j == (i * i))
        ok();
    else
    {
        ko();
        ret++;
    }
    return (ret);
}

int main(void)
{
    int ret;    

    ret = 0;
    printf("Start testing :");
    ret = is_to_something(ret);
    ret = check_strlen(ret);
    ret = check_bzero(ret);
    ret = check_memset(ret);
    ret = check_memalloc(ret);
    check_puts();
    ret = check_strcat(ret);
    ret = check_memcpy(ret);
    ret = check_strdup(ret);
    call_cat();
    check_power(ret);

    printf("\n\nfailed: %i\n", ret);
    return (ret > 0 ? 1 : 0);
}