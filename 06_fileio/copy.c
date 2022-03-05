/**
 * @file copy.c
 * @brief 
 * @version
 * @copyright Copyright (c) 2022
 * @history:
 * Date                         Author      Version    Description
 * 2022-03-05 12-35-51          Byron
 */
#include <stdio.h>   //man 3 printf
#include <sys/types.h>  //man 2 open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>  //man 2 read




int main(int argc, char **argv)
{
    int fd_old, fd_new;
    unsigned char buf[1024];
    int len;

    if(argc != 3)
    {
        printf("Usage: %s <old-file> <new-file>\r\n", argv[0]);
        return -1;
    }

    fd_old = open(argv[1], O_RDONLY);
    if(fd_old == -1)
    {
 		printf("can not open file %s\n", argv[1]);
		return -1;       
    }

	fd_new = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd_new == -1)
	{
		printf("can not creat file %s\n", argv[2]);
		return -1;
	}

    while(len == read(fd_old, buf, sizeof(buf)))
    {
        if(len != write(fd_new, buf, sizeof(buf)))
        {
			printf("can not write %s\n", argv[2]);
			return -1;
        }

    }

	close(fd_old);
	close(fd_new);

}
