#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#define BUFF_SIZE 245

#include "get_next_line.h"

char *_fill_line_buffer(int fd, char *left_c, char *buffer)
{
  ssize_t bytes_read;

  while((bytes_read = read(fd, buffer, BUFF_SIZE)) > 0 ) {
  buffer[bytes_read] = '\0';

  if(left_c) { //前回の呼び出し時に文字列の余があった場合
    char *tmp = left_c;
    left_c = ft_strjoin(tmp, buffer);
    free(tmp);
  }else {
    left_c = ft_strdup(buffer);
  }

  if (ft_strchr(buffer, '\n'))
    break;
  }

  if (bytes_read == 0 && (!left_c || left_c[0] == '\0')) {
        free(left_c);
        return NULL;
    }

  if(bytes_read < 0) {
    free(left_c);
    left_c = NULL;
  }
  return left_c;
}

char *_set_line(char *line_buffer)
{
  if(!line_buffer || !line_buffer[0])
    return NULL;
  char *line;
  int i;
  i = 0;

  while(line_buffer[i] != '\n' && line_buffer[i] != '\0'){
    i++;
  }
  
  if (line_buffer[i] == '\n') {
    line = ft_strdup(line_buffer + i +1);
    line_buffer[i] = '\0';
  } else {
    return NULL;
  }

  return line;
}


char *get_next_line(int fd) //全ての読み込みを行う
{
    static char *reminder;
    char *buffer;
    char *line;

    if (fd < 0 || BUFF_SIZE <= 0){
        return NULL;
    }

    buffer = malloc(BUFF_SIZE + 1);
    if (!buffer)
      return NULL;

    reminder = _fill_line_buffer(fd, reminder, buffer);
    free(buffer);

    if(!reminder || reminder[0] == '\0') {
      free(reminder);
      reminder = NULL;
      return NULL;
    }

    line = ft_strdup(reminder);
    char *new_reminder = _set_line(reminder);
    free(reminder);
    reminder = new_reminder;

    return line;
}

int main(void)
{
    int fd;
    char *line;
    fd = open("./test.txt", O_RDONLY);
    while((line = get_next_line(fd)) != NULL ) {
      printf("%s\n", line);
      free(line);
    }
    close(fd);
}