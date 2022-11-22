#include <display.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
const char led[2] = {0x06,0x06};
const char status[2] = {0x03,0x03};
const char anologCmd[2] = {0x04,0x04};
const char digitalCmd[2] = {0x05,0x05};
unsigned char analogBuffer[2];
unsigned char digitalBuffer[2];
const char inicio[12] = "iniciando...";
const char erroini[21] = "erro na inicianizacao";
const char strAnalogValue[26] = "Valor do sensor analogico ";
char analogValue[3];
cha digitalValue[3];
char string[30];
char *portname = "/dev/ttys0"

void main(){
    lcdInit();
    analogValue = 0;
    digitalValue = 0;
    print(inicio,12);
    int fd = open(portname,O_RDWR | O_NOCTTY | O_SYNC);
    
    if(fd < 0){
    	print(erroini,21);
    }
    
    struct termios tty;
    
    
    if(tcgetattr(fd,&tty) != 0){
    	print(erroini,21);
    }
    
    cfsetospeed(&tty,B9600);
    cfsetispeed(&tty,B9600);
    tty.c_cflag = (tty.c_flag & ~CSIZE) | CS8;
    tty.c_iflag&= ~IGNBRK;
    tty.c_lflag = 0;
    tty.tty.c_oflag = 0;
    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 5;    
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);  
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    if(tcsetattr (fd, TCSANOW, &tty) != 0)
    {
    	print(erroini,21);
            
    }
    
    set_blocking (fd, 0);   
    while(1){
        write(fd,anologCmd,2);
        usleep(10);
        read(fd,analogBuffer,2);
        print(strAnalogValue,26);
        sprinf(analogValue,"%d",analogBuffer[1]);
        print(analogValue,2);
        clear();
        usleep(3000);
    }
}

void print(char string[],int size){
    for(i=0;i<size;i++){
        lcdWrite(string[size]);
    }
}

void set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                error_message ("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                error_message ("error %d setting term attributes", errno);
}
