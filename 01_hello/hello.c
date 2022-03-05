/**
 * @file hello.c
 * @brief 
 * @version
 * @copyright Copyright (c) 2022
 * @history:
 * Date                         Author      Version    Description
 * 2022-03-01 11-01-23          Byron
 */
#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc >= 2)
    {
        printf("hello,%s!\r\n", argv[1]);

    }
    else
    {
        printf("Hello, world!\r\n");
    }
    
    return 0;
}