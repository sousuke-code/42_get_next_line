#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#include "get_next_line.h"


int ft_strlen(const char *c)
{
    size_t count;

    count = 0;
    
    while(*c != '\0')
    {
     count++;
     c++;
    }

    return count;
}

char *ft_strchr(const char *s, int c)
{
   if (s == NULL)
      return NULL;
    while (*s != '\0')
    {
        if ((unsigned char)*s == (unsigned char)c)
        {
            return (char *)s;
        }
        s++;
    }

    if(c == '\0')
    {
        return (char *)s;
    }
    
    return NULL;
    
}

char *ft_strdup(const char *s1)
{
    char *p;
    int i;
    int len;
    len = 0;
    i = 0;

    len = ft_strlen((char *)s1);
    p = (char *)malloc(len+1);
    if (p ==NULL){
        return NULL;
    }

    while(*s1 != '\0'){
        p[i] = *s1;
        i++;
        s1++;
    }
    p[len] = '\0';
    return p;
}

size_t ft_strlcat(char *dst, const char *src, size_t dstsize)
{
    
    //dstの末尾に最大dstsize - strlen(dst) -1 文字を追加する
    //オリジナルのdst文字列がdstsizeより長くなかったなら、ヌル文字で終了させる。
    size_t dst_len; 
    size_t src_len; 
    size_t max_cpy;
    size_t n;
    n = 0 ;

    dst_len = ft_strlen(dst);
    src_len = ft_strlen((char *)src);
    if (dstsize <= dst_len)
     return (dstsize + src_len);

    max_cpy = dstsize - dst_len -1;
    while ( n < max_cpy && src[n] != '\0'){
        dst[dst_len+n] = src[n];
        n++;
    }

    dst[dst_len + n] = '\0';

    return (dst_len + src_len);

}

size_t ft_strlcpy(char *dst, const char *src, size_t size)
{
    size_t n;
    n = 0;
    while (src[n])
    { 
      n++;  
    }
    if (size == 0) {
      return n;
    }
    size_t i = 0; 
    while (i  < size -1 && *src != '\0')
    {
        *dst = *src;
        dst++;
        src++;
        i++;
    }

    *dst = '\0'; 
    return n;
}


char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *ans;
    ans = malloc(len+1);
    if (ans == NULL) {
        return NULL;
    }
    unsigned int s_len;
    unsigned int index;
    unsigned int  i;
    i = 0;
    index = 0;
    s_len = ft_strlen((char *)s);


    if (len <= 0){
        return NULL;
    }

    if (start >= s_len) {
        return ft_strdup("");
    }

    while (*s != '\0' && index <= start + len -1)
    {
        if (index >= start)
        {
            ans[i] = *s;
            i++;
        }
        index++;
        s++;
    }
    ans[i] = '\0';
    return ans;

}




char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = malloc(len);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, (char *)s1, ft_strlen((char *)s1) + 1);
	ft_strlcat(str, (char *)s2, len);
	return (str);
}

