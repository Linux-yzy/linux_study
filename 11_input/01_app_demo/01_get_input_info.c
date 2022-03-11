/**
 * @file 01_get_input_info.c
 * @brief 
 * @version
 * @copyright Copyright (c) 2022
 * @history:
 * Date                         Author      Version    Description
 * 2022-03-11 01-09-02          Byron
 */
#include <linux/input.h> 

#include <sys/types.h>// man 2 openq
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ioctl.h>//man 2 ioctl

#include <stdio.h>  //man 3 printf

/**
 * @brief 
 * @param  argc 
 * @param  argv 
 * @return int 
 * @note:
 */
/* ./01_get_input_info /dev/input/event1 */
int main(int argc, char **argv)
{
    int fd,err;
    struct input_id id;
	int len;
	int i;
    unsigned char byte;
    int bit;
	unsigned int evbit[2];
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
		printf("Usage: %s <dev>\n", argv[0]);
		return -1;
    }

    fd = open(argv[1], O_RDWR);
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

   return 0;
}