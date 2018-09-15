#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <fstream>
#include "uart.h"

void openSerial(int num)
{
  g_fd[num] = open("/dev/ttyO1",O_RDWR | O_NOCTTY);
  if (g_fd[num]==1)
    printf("\n Error! in Opening ttyO1 \n");
  else 
    printf("\n ttyO1 Opened! \n");
}

void enableUART(int num)
{
  std::fstream uart_fs;
  uart_fs.open(HARDWARE_PATH,std::fstream::out);
  uart_fs << "BB-UART"+to_string(num);
  uart_fs.close();
}

void setBaudrate(int num,int baud)
{
  static struct termios SerialPortSettings[5];
  tcgetattr(g_fd[num], &SerialPortSettings[num]);
  cfsetispeed(&SerialPortSettings[num],baud);
  cfsetospeed(&SerialPortSettings[num],baud);
  SerialPortSettings[num].c_cflag &= ~PARENB;   // No Parity
  SerialPortSettings[num].c_cflag &= ~CSTOPB; //Stop bits = 1 
  SerialPortSettings[num].c_cflag &= ~CSIZE; /* Clears the Mask */
  SerialPortSettings[num].c_cflag |=  CS8;   /* Set the data bits = 8 */
  SerialPortSettings[num].c_cflag &= ~CRTSCTS;
  SerialPortSettings[num].c_cflag |= CREAD | CLOCAL;
  SerialPortSettings[num].c_iflag &= ~(IXON | IXOFF | IXANY);
  SerialPortSettings[num].c_cc[VMIN]  = 1; /* Read 1 characters */  
  SerialPortSettings[num].c_cc[VTIME] = 0;  /* Wait indefinitely   */
  tcsetattr(g_fd[num],TCSANOW,&SerialPortSettings[num]);
}

int readUART(int num, char* buffer,int buffSize)
{
  return read(g_fd[num], buffer ,buffSize);
}
void closeUART(int num)
{
  close(g_fd[num]);
}
/*

int num=1;
int main(void)
{
  char read_buffer[100];
  int g_bytes_read = 0;
  openSerial(num);
  int g_status = 1;
  while(g_status)
  { 
    g_bytes_read = read(g_fd[num], &read_buffer,100);

    if (g_bytes_read > 0)
    {
      //printf("Read \n");
      if (read_buffer[0] == 'x') 
      {
        printf("\n ------------- Close port ----------- \n");
        close(g_fd[num]);
        g_status=0;
        printf("\n ------------- Close port -----------\n");
      }
      else
	    {
        for (int l_count = 0; l_count < g_bytes_read ; l_count++)
        {
          printf("%c", read_buffer[l_count]);
          
        }
        
	      
          //printf("%f    %f \n", d1,d2);
          //int d2 = std::stoi(read_buffer);
          //printf("%f \n", float(d2));
	      
          //setPWM(1,'A',100000,f);
	    }
    }
  }
}
*/

