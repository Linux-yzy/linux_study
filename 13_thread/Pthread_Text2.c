/**
 * @file Pthread_Text2.c
 * @brief 
 * @version
 * @copyright Copyright (c) 2022
 * @history:
 * Date                         Author      Version    Description
 * 2022-03-12 10-04-18          Byron
 */
#include <stdio.h> //man 3 printf
#include <pthread.h> //man 3 pthread_self
#include <errno.h> //man 3 perror
#include <unistd.h>//man 3 sleep

void *fun(void *arg)
{
	printf("pthread_New = %lu\n",(unsigned long)pthread_self());
}
/**
 * @brief 
 * @param  argc 
 * @param  argv 
 * @return int 
 * @note:
 */
int main(int argc, char **argv)
{
    pthread_t tid1 = 0;
    int ret = 0;

    ret = pthread_create(&tid1, NULL,
                                fun, NULL);
    if(ret != 0)
    {
		perror("pthread_create");
		return -1;
    }

    printf("tid_main = %lu tid_new = %lu \n",(unsigned long)pthread_self(),(unsigned long)tid1);

    sleep(1);
    return 0;
}
