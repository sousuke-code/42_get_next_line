#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#define BUFF_SIZE 246

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






char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = malloc(len);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, (char *)s1, len);
	ft_strlcat(str, (char *)s2, len);
	return (str);
}



char *extra_line(char *buff) //余分な行を取り除く
{
    int i;
    char *buff_line;
    i = 0;
    while (buff[i] != '\n')
    {
        i++;
    }
    buff_line = malloc(i+1);
    ft_strlcpy(buff_line, buff, i+1);
    return buff_line;
}


char *get_next_line(int fd) //全ての読み込みを行う
{
    static char *reminder;
    char *buff;
    char *line;
    ssize_t bytes_read;
    char *return_buff;

    buff = malloc(BUFF_SIZE + 1);
    if (!buff)
      return NULL;

    if(!reminder) reminder = ft_strdup("");

    while( (bytes_read = read(fd, buff, BUFF_SIZE)) > 0) {
      buff[bytes_read] = '\0';
      char *tmp = reminder;
      reminder = ft_strjoin(reminder, buff);
      free(tmp);
    }
    free(buff);
    
    line = extra_line(reminder);
    return line;
}

int main(void)
{
    int fd;
    char *line;
    fd = open("./test.txt", O_RDONLY);
    while((line = get_next_line(fd)) != NULL) {
      printf("%s", line);
      free(line);
    }
    close(fd);
    /* ループ内でget_next_lineを使用していくことで各行の文字列が読み込まれるような動作になる。*/
    /* 戻り値がファイルから読み取った一行分になる*/
    /* 一行の区切りを\nで認識させてそこまで一文字ずつループで読み込んでいけば行けるような気がする。*/
}