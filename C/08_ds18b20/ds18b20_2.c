#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

#define  BUFSIZE  128

int main(void)
{
	float temp;
	int i, j;
    int fd;
	int ret;

	char buf[BUFSIZE];
	char tempBuf[5];

	while(1){	
		fd = open("/sys/bus/w1/devices/28-8000000178d0/w1_slave", O_RDONLY);

		if(-1 == fd){
			perror("open device file error");
			return 1;
		}

		while(1){
			ret = read(fd, buf, BUFSIZE);
			if(0 == ret){
				break;	
			}
			if(-1 == ret){
				if(errno == EINTR){
					continue;	
				}
				perror("read()");
				close(fd);
				return 1;
			}
		}

		for(i=0;i<sizeof(buf);i++){
			if(buf[i] == 't'){
				for(j=0;j<sizeof(tempBuf);j++){
					tempBuf[j] = buf[i+2+j]; 	
				}
			}	
		}

		temp = (float)atoi(tempBuf) / 1000;

		printf("%.3f C\n",temp);

		close(fd);

		delay(500);

	}

	return 0;
}
