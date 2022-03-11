/**
 * @file 05_input_read_fasync.c
 * @brief 
 * @version
 * @copyright Copyright (c) 2022
 * @history:
 * Date                         Author      Version    Description
 * 2022-03-11 03-12-37          Byron
 */
#include <linux/input.h> 

#include <sys/types.h>// man 2 openq
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ioctl.h>//man 2 ioctl

#include <stdio.h>  //man 3 printf
#include <string.h> //man 3 strcmp

#include <unistd.h>//man 2 read
#include <signal.h>//man 2 signal
int fd;

void my_sig_handler(int sig)
{
	struct input_event event;
	while (read(fd, &event, sizeof(event)) == sizeof(event))
	{
		printf("get event: type = 0x%x, code = 0x%x, value = 0x%x\n", event.type, event.code, event.value);		
	}
}

/**
 * @brief 
 * @param  argc 
 * @param  argv 
 * @return int 
 * @note:
 */
/* ./01_get_input_info /dev/input/event1*/
int main(int argc, char **argv)
{
    int err;
    struct input_id id;
	int len;
	int i;
    unsigned char byte;
    int bit;
	unsigned int evbit[2];
    struct input_event event;
    unsigned int flags;
	int count = 0;

	char *ev_names[] = {
		"EV_SYN ",
		"EV_KEY ",
		"EV_REL ",
		"EV_ABS ",
		"EV_MSC ",
		"EV_SW	",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"EV_LED ",
		"EV_SND ",
		"NULL ",
		"EV_REP ",
		"EV_FF	",
		"EV_PWR ",
	};

    if(argc < 2)
    {
		printf("Usage: %s <dev> [noblock]\n", argv[0]);
		return -1;
    }

    /*注册信号处理函数*/
    signal(SIGIO, my_sig_handler);

    fd = open(argv[1], O_RDWR | O_NONBLOCK);  
    if(fd < 0)
    {
		printf("open %s err\n", argv[1]);
		return -1;
    }

	err = ioctl(fd, EVIOCGID, &id);
	if (err == 0)
	{
		printf("bustype = 0x%x\n", id.bustype );
		printf("vendor	= 0x%x\n", id.vendor  );
		printf("product = 0x%x\n", id.product );
		printf("version = 0x%x\n", id.version );
	}

	len = ioctl(fd, EVIOCGBIT(0, sizeof(evbit)), &evbit);
	if (len > 0 && len <= sizeof(evbit))
	{
		printf("support ev type: ");
		for (i = 0; i < len; i++)
		{
			byte = ((unsigned char *)evbit)[i];
			for (bit = 0; bit < 8; bit++)
			{
				if (byte & (1<<bit)) {
					printf("%s ", ev_names[i*8 + bit]);
				}
			}
		}
		printf("\n");
	}

	fcntl(fd, F_SETOWN, getpid());

	flags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flags | FASYNC);

	while (1)
	{
		printf("main loop count = %d\n", count++);
		sleep(2);
	}

   return 0;
}
