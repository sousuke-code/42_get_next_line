#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#define BUFF_SIZE 246

int find_next_line(char *buff, int size)
{
  int i;
  i = 0;
  while (i < size)
  {
    if (buff[i] == '\n')
      return i;
    i++;
  }
  return -1; //次の改行が見つからない場合
}



char *get_next_line(int fd) //全ての読み込みを行う
{
    size_t buff_end;
    char *buff;
    int i;
    i = 0;
    buff = malloc(BUFF_SIZE);
    if (!buff)
      return NULL;
    read(fd, buff, BUFF_SIZE); //buffにBUFF_SIZE分だけが読み込まれている状態
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