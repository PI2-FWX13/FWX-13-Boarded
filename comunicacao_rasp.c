#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringSerial.h>


#define TTY "/dev/ttyAMA0"

int uart0_fd;
void ctrl_c(int sig)
{

        close(uart0_fd);
        exit(-1);
}

int main(void)
{
        int user_input = 1;
        int freq = 0;
	float input_test = 200.053079;

        signal(SIGINT, ctrl_c);
        uart0_fd = serialOpen(TTY, 9600);
        if(uart0_fd==-1)
        {
                     
                return -1;
        }

        serialFlush(uart0_fd);
        if(serialDataAvail(uart0_fd)!=0) puts("Oh oh");
        char *pointer = (char *) &input_test;
   	for(int i = 0; i < sizeof(float); i++)
              serialPutchar(uart0_fd, *(pointer + i));

        serialClose(uart0_fd);

}
