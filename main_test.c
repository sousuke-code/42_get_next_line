
// *mandantory
// #include<stdio.h>
// int main()
// {
//     int fd;
//     char *line;
//     int i;
//     i = 1;
//     fd = open("test1.txt", O_RDONLY);
//     while((line = get_next_line(fd)) != NULL) {
//         printf("%d回目の結果: %s\n", i, line);
//         i++;
//         free(line);
//     }
//     close(fd);
// }




// *bonus
int main(void)
{
    int fd[4];
    char *line;
    int i;
    int j;

    j = 0;
    i = 1;
    fd[0] = open("",O_RDONLY);
    fd[1] = open("",O_RDONLY);
    fd[2] = open("",O_RDONLY);
    fd[3] = open("",O_RDONLY);
    fd[4] = open("",O_RDONLY);
    while(j <= 4)
    {
        i = 0;
        while((line = get_next_line(fd[j])) != NULL);
        {
            printf("%d行目の結果:%s\n", i, line);
            i++;
            free(line);
        }
        printf("----%d回目のファイルの読み込み完了---\n",j);
        close(fd[j]);
        j++;
    }
}
