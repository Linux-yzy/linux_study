/**
 * @file Pthread_Text1.c
 * @brief 
 * @version
 * @copyright Copyright (c) 2022
 * @history:
 * Date                         Author      Version    Description
 * 2022-03-12 12-05-17          Byron
 */
#include <stdio.h> //man 3 printf
#include <pthread.h> //man 3 pthread_self

/**
 * @brief 
 * @param  argc 
 * @param  argv 
 * @return int 
 * @note:
 */
int main(int argc, char **argv)
{
    pthread_t tid = 0;

    tid = pthread_self();
    printf("tid = %lu\n",(unsigned long)tid);
    return 0;
}
