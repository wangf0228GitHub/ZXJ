#include "HardwareProfile.h"

#define EM350AT_file "/dev/ttyUSB0"
int file_EM350AT;
#define EM350AT_BUF_LEN_MAX	2048
#define CR_CHAR  0x0D
#define LF_CHAR  0x0A
int at_send_command(char *cmd)
{
	int len;
	tcflush(file_EM350AT, TCIFLUSH);
	len = write(file_EM350AT, cmd, strlen(cmd));
	printf("[SEND][%2d] %s\n", len, cmd);
	return len;
}
int EM350_RecvAT(int fd, char * waitbuf, int wblen, int timeout)
{
	int select_re = 0;
	fd_set read_set, all_set;
	int max_fd = 0;
	char buff[EM350AT_BUF_LEN_MAX + 1] = { 0 };
	int nread = 0;
	int ret = 0;
	struct timeval tTimeItval;
	if (!waitbuf) 
		return -1;
	FD_ZERO(&all_set);
	FD_SET(file_EM350AT, &all_set);
	//FD_SET(STDIN_FILENO, &all_set);
	max_fd = file_EM350AT;//> STDIN_FILENO?file_EM350AT:STDIN_FILENO;
	tTimeItval.tv_sec = timeout / 1000;
	tTimeItval.tv_usec = (timeout % 1000) * 1000;//  100ms
	while (1)
	{
		read_set = all_set;
		nread = 0;
		select_re = select(max_fd + 1, &read_set, NULL, NULL, &tTimeItval);
		if (select_re > 0)
		{
			if (FD_ISSET(file_EM350AT, &read_set))
			{
				if ((nread = read(file_EM350AT, buff, EM350AT_BUF_LEN_MAX - 1)) > 0)
				{
					int i, j;
					buff[nread] = '\0';
					i = 0;
					char *ack_ptr = NULL;
					while (i < nread)
					{
						while (i < nread && (buff[i] == CR_CHAR || buff[i] == LF_CHAR || buff[i] == ' '))
						{
							i++;
						}
						j = i;
						while (j < nread && buff[j] != CR_CHAR && buff[j] != LF_CHAR)
						{
							j++;
						}
						buff[j] = 0;
						if (j > i)
						{
							ack_ptr = &buff[i];
							printf("[R] %s\n", ack_ptr);
							//single_command(ack_ptr);						
							if (0 == strncasecmp(ack_ptr, waitbuf, strlen(waitbuf)))
							{
								if (wblen > 0)
								{
									strncpy(waitbuf, ack_ptr, wblen);
								}
								ret = 1;
							}
						}
						i = j + 1;
					}
					if (ret == 1)
						return ret;
				}
				else
				{
					//log_err("read data error\n");
					return -1;
				}
			}
		}
		else if (select_re < 0)
		{
			//log_err("select failed\n");
			return select_re;
		}
		else if (select_re == 0)// 100ms timeout
		{//周期处理
		 //恢复定时
			//tTimeItval.tv_sec = 0;
			//tTimeItval.tv_usec = TIMETICKMS * 1000;//  100ms	
			//log_warn("%s timeout\n", __FUNCTION__);
			return 0;
		}
	}
}

void single_command(char *cmd)
{
	if (!strncmp(cmd, "^RSSI", 5)) 
		return;
	printf("[RECV] %s\n", cmd);
}

void Init_EM350AT(void)
{
	int status;
	struct termios options;
	file_EM350AT = open(EM350AT_file, O_RDWR | O_NOCTTY);// | O_NDELAY);   
	if (-1 == file_EM350AT)
	{
		printf("Can't Open Serial Port: %s !\n",EM350AT_file);
		return;
	}
	tcgetattr(file_EM350AT, &options);
	tcflush(file_EM350AT, TCIOFLUSH);
	cfsetispeed(&options, B19200);
	cfsetospeed(&options, B19200);

	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	
	options.c_cflag &= ~CRTSCTS;//不进行硬件流控制

	options.c_cflag &= ~PARENB;  /* Clear parity enable */
	options.c_iflag &= ~INPCK;   /* Enable parity checking */
	//options.c_iflag |= INPCK;/* Set input parity option */

	options.c_cflag &= ~CSTOPB;

	/* Set input parity option */
	options.c_cc[VTIME] = 150; // 15 seconds
	options.c_cc[VMIN] = 0;

	tcflush(file_EM350AT, TCIFLUSH); /* Update the options and do it NOW */
	status = tcsetattr(file_EM350AT, TCSANOW, &options);
	if (status != 0) 
	{
		perror("tcsetattr fd1");
		return;
	}
	tcflush(file_EM350AT, TCIOFLUSH);
	printf("Open %s successfully\n", EM350AT_file);
}