#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#define BUFF_SIZE 246

#include "get_next_line.h"

char *_fill_line_buffer(int fd, char *left_c, char *buffer)
{
  int bytes_read;

  while((bytes_read = read(fd, buffer, BUFF_SIZE)) >= 0 ) {
  if (bytes_read <= 0 )
   break;
  if(left_c) { //前回の呼び出し時に文字列の余があった場合
    left_c = ft_strjoin(left_c, buffer);
  }else {
    left_c = ft_strdup(buffer);
  }

  if (ft_strchr(buffer, '\n'))
    break;
  }
  return left_c;
}

char *_set_line(char *line_buffer)
{
  char *line;

  //次の読み込みに備えて改行文字以降にポインタを移動させる。
  int i;
  while(line_buffer[i] != '\n' && line_buffer[i] != '\0'){
    i++;
  }
  if (line_buffer[i] == '\n') {
    line = ft_strdup(line_buffer + i + 1);
    line_buffer[i] = '\0';
  }

  return line;
}


char *get_next_line(int fd) //全ての読み込みを行う
{
    static char *reminder;
    char *buffer;
    char *line;
    ssize_t bytes_read;
    char *return_buff;

    if (fd < 0 || BUFF_SIZE <= 0)
        return NULL;

    buffer = malloc(BUFF_SIZE + 1);
    if (!buffer)
      return NULL;

    reminder = _fill_line_buffer(fd, reminder, buffer);
    free(buffer);
    line = ft_strdup(reminder);
    reminder = _set_line(reminder);
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
}