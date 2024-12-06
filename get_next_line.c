#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#define BUFF_SIZE 246


char *get_next_line(int fd) //一行分の読み込み
{
    size_t buff_end;
    char *buff;
    int i;
    i = 0;
    buff = malloc(BUFF_SIZE);
    if (!buff)
      return NULL;
    while(read(fd, &buff[i],1) > 0) //一文字読み込みではなく一行読み込みに変更する必要あり
    {
      if (buff[i] == '\n')
       break;
      i++;
    }

    buff[i+1] = '\0';
    return buff;
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