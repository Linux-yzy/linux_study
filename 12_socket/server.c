/**
 * @file server.c
 * @brief 
 * @version
 * @copyright Copyright (c) 2022
 * @history:
 * Date                         Author      Version    Description
 * 2022-03-11 09-03-07          Byron
 */
#include <sys/types.h>      
#include <sys/socket.h>     //man 2 socket

#include <string.h>         //man 3 memset

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>      //man 2 bind

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>     //man 2 listen


#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>     //man 2 accept


#include <sys/socket.h>  //man 3 inet_aton
#include <netinet/in.h>
#include <arpa/inet.h>


#include <sys/types.h>   //man 2 recv
#include <sys/socket.h>

#include <unistd.h>  //man 2 close

#include <stdio.h> //man 3 printf

#define SERVER_PORT 8888
#define BACKLOG     10
/**
 * @brief 
 * @param  argc 
 * @param  argv 
 * @return int 
 * @note:
 */
int main(int argc, char **argv)
{
    int iSocketServer;
    int iSocketClient;
    struct sockaddr_in tSocketServerAddr;
    struct sockaddr_in tSocketClientAddr;
    int iRet;
    int iAddrLen;

    int iClientNum = -1;
    int iRecvLen;
    unsigned char ucRecvBuf[1000];

    iSocketServer = socket(AF_INET, SOCK_STREAM, 0);
    if(iSocketServer == -1)
    {
        printf("socket error!\n");
        return -1;
    }

    tSocketServerAddr.sin_family      = AF_INET;
    tSocketServerAddr.sin_port        = htons(SERVER_PORT);
    tSocketServerAddr.sin_addr.s_addr = INADDR_ANY;
    memset(tSocketServerAddr.sin_zero, 0, sizeof(tSocketServerAddr.sin_zero));
    
    iRet = bind(iSocketServer, (const struct sockaddr *)&tSocketServerAddr,
                sizeof(struct sockaddr));
    if(-1 == iRet)
    {
		printf("bind error!\n");
		return -1;
    }

	iRet = listen(iSocketServer, BACKLOG);
	if (-1 == iRet)
	{
		printf("listen error!\n");
		return -1;
	}

    while(1)
    {
        iAddrLen = sizeof(struct sockaddr);
        iSocketClient = accept(iSocketServer, (struct sockaddr *)&tSocketClientAddr, &iAddrLen);
        if(-1 != iSocketClient)
        {
            iClientNum++;
            printf("Get connect from client %d : %s\n",  iClientNum, inet_ntoa(tSocketClientAddr.sin_addr));
            if(!fork())
            {

                /* 子进程的源码 */
                while (1)
                {        
                    iRecvLen = recv(iSocketClient, ucRecvBuf, 999, 0);
                    if(iRecvLen <= 0)
                    {
                            close(iSocketClient);
                            return -1;                   
                    }
                    else
                    {
                            ucRecvBuf[iRecvLen] = '\0';
                            printf("Get Msg From Client %d: %s\n", iClientNum, ucRecvBuf);
                    }
                }

            }
        }
    }

}
