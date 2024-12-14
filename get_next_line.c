#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#define BUFF_SIZE 1

#include "get_next_line.h"

char *_fill_line_buffer(int fd, char *reminder, char *buffer)
{
  ssize_t bytes_read;

  while((bytes_read = read(fd, buffer, BUFF_SIZE)) > 0 ) {
  buffer[bytes_read] = '\0';
  if(reminder) { 
    char *tmp = reminder;
    reminder = ft_strjoin(tmp, buffer);
    free(tmp);
  }else{
    reminder = ft_strdup(buffer);
  }
  if (ft_strchr(buffer, '\n'))
    break;
  }

  if (bytes_read == 0){
        return reminder;
  }
  
  return reminder;
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
    line = ft_substr(line_buffer,i+1, ft_strlen(line_buffer)+1);
    line_buffer[i+1] = '\0';
  } else {
    return NULL;
  }

  return line; //　戻り値としては改行文字以降の文字列
}


char *get_next_line(int fd) //全ての読み込みを行う
{
    static char *reminder;
    char *buffer;
    char *line; //戻り値として返す一行分の文字列

    if (fd < 0 || BUFF_SIZE <= 0)
        return NULL;
    buffer = malloc(BUFF_SIZE + 1);
    if (!buffer)
      return NULL;
    reminder = _fill_line_buffer(fd, reminder, buffer);
    free(buffer);
    if(!reminder || reminder[0] == '\0' ) {
      free(reminder);
      reminder = NULL;
      return NULL;
    }
    line = ft_strdup(reminder); //reminderのコピー
    reminder = _set_line(line);
    return line;
}

// int main(void)
// {
//     int fd;
//     char *line;
//     int i;
//     i = 1;
//     fd = open("./test.txt", O_RDONLY);
//     while((line = get_next_line(fd)) != NULL ) {
//       printf("%d回目の結果: %s\n",i, line);
//       i++;
//       free(line);
//     }
//     close(fd);
// }