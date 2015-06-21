#include "libftasm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int    ok(void)
{
    printf("\033[0;32m\033[1m.\033[0m");
    return (0);
}

int ko(void)
{
    printf("\033[0;31m\033[1mF\033[0m");
    return (1);
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
    int i = 3;
    
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


int main(void)
{
    int ret;

    ret = 0;
    printf("Start testing :");
    ret = is_to_something(ret);
    ret = check_strlen(ret);
    ret = check_bzero(ret);
    printf("\n");
    ft_puts("\nft_puts");
    ft_puts("\033[0;32m\033[1m.\033[0m");
    

    printf("\n\n\nfailed: %i\n", ret);
    return (ret > 0 ? 1 : 0);
}