#include <display.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

const char inicio[12] = "iniciando..."
const char erroini[21] = "erro na inicianizacao"
int analogValue;
int digitalValue;
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
    while(1){
    	
    }
}

void print(char string[],int size){
    for(i=0;i<size;i++){
        lcdWrite(string[size]);
    }
}
