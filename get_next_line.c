#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

char *get_next_line(int fd)
{

}

int main(void)
{
    int fd;
    fd = open("./test.txt", O_RDONLY);

    /* ループ内でget_next_lineを使用していくことで各行の文字列が読み込まれるような動作になる。*/
}