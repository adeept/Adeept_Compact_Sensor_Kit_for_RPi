#include "ds18b20.h"

extern float ds18b20Read(void)
{
	float temp;
	int i, j;
    int fd;
	int ret;

	char buf[BUFSIZE];
	char tempBuf[5];
	
	fd = open("/sys/bus/w1/devices/28-8000000178d0/w1_slave", O_RDONLY);

	if(-1 == fd){
		perror("open device file error\n");
		return -1;
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
			perror("read()\n");
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

//	printf("%.3f C\n",temp);

	close(fd);

	return temp;
}
