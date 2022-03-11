#define _GNU_SOURCE 
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>


int Num = 1;

void *fun1(void *arg)
{
	while(Num < 3){
		printf("%s:Num = %d",__FUNCTION__,Num);
		Num++;
		printf(";Num++ = %d\n",Num);
		sleep(1);
	}
	pthread_exit(NULL);
}

void *fun2(void *arg)
{
	while(Num > -3){
		printf("%s:Num = %d",__FUNCTION__,Num);
		Num--;
		printf(";Num-- = %d\n",Num);
		sleep(1);
	}
	pthread_exit(NULL);
}

int main()
{
	int ret;
	pthread_t tid1,tid2;
	ret = pthread_create(&tid1,NULL,fun1,NULL);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	ret = pthread_create(&tid2,NULL,fun2,NULL);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}
