#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#define BUFF_SIZE 246


size_t ft_strlcpy(char *dst, const char *src, size_t size)
{
    // src からdistに対して、size - 1バイトを複写する。
    size_t n;
    n = 0;
    while (src[n])
    { 
      n++;  
    }
    if (size == 0) {
      return n;
    }
    size_t i = 0; //戻り地で返すsrcの長さ
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


char *extra_line(*buff) //余分な行を取り除く
{
    int i;
    char *buff_line;
    i = 0;
    while (buff[i] != '\n')
    {
        i++;
    }
    buff_line = malloc(i);
    ft_strlcpy(buff_line, buff, i);
    return buff;
}


char *get_next_line(int fd) //全ての読み込みを行う
{
    size_t buff_end;
    static *reminder;
    char *buff;
    char *return_buff;
    int i;
    i = 0;
    buff = malloc(BUFF_SIZE);
    if (!buff)
      return NULL;
    read(fd, buff, BUFF_SIZE); 
    return_buff = extra_line(buff);

    
    return return_buff;
}

int main(void)
{
    int fd;
    char *ans;
    fd = open("./test.txt", O_RDONLY);
    ans = get_next_line(fd);
    close(fd);
    printf("%s", ans);
    /* ループ内でget_next_lineを使用していくことで各行の文字列が読み込まれるような動作になる。*/
    /* 戻り値がファイルから読み取った一行分になる*/
    /* 一行の区切りを\nで認識させてそこまで一文字ずつループで読み込んでいけば行けるような気がする。*/
}