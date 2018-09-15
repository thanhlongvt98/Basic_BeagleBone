#include <stdio.h>
#include <unistd.h>
//#include <errno.h>
//#include <iostream>
//#include <fstream>
#include <termios.h>
#include <stdlib.h>
#include <string>


#include "pwm/pwm.h"
#include "adc/adc.h"
#include "uart/uart.h"
#include "gpio/SimpleGPIO.h"


int main(void)
{
  enablePWMpin(2,'A');
  enablePWMpin(4,'A');
  int getNum[4];
  u_int8_t getNumIdx = 0;
  double tempGetNumCount[4];
  int num=1, num_flag;
  char read_buffer[100];
  int g_bytes_read = 0;
  openSerial(num);
  setBaudrate(num,B9600);
  int g_status = 1;
  while(g_status)
  { 
    printf("Please type : \"FIRST_PERIOD FIRST_DUTY SECOND_PERIOD SECOND_DUTY \" \n");
    printf("            : \"P1 D1 P2 D2 \" \n");
    printf("By UART1 P9.24 (TX) P9.26 (RX) \n");
    g_bytes_read = readUART(num, read_buffer ,100);
    if (g_bytes_read > 0)
    {
      if (read_buffer[0] == 'x') 
      {
        printf("\n ------------- Close port ----------- \n");
        closeUART(num);
        g_status=0;
        printf("\n ------------- Close port -----------\n");
        disablePWMpin(2,'A');
        disablePWMpin(4,'A');
      }
      else
	    {
        getNumIdx = 0;
        num_flag = 0;
        string getNumString = "";
        string::size_type sz;
        for (int l_count = 0; l_count < g_bytes_read ; l_count++)
        {
          if ((read_buffer[l_count] >= '0') && (read_buffer[l_count] <= '9'))
          {
            getNumString += read_buffer[l_count];
            num_flag = 1;
          }
          else
          {
            if (num_flag == 1)
            {
              getNum[getNumIdx] = std::stoi(getNumString,&sz,10);
              getNumIdx = (getNumIdx + 1 ) % 4;
              num_flag = 0;
              getNumString = "";
            }
            
          }
        }
        printf("P1 = %i \t D1 = %i \t P2 = %i \t D2 = %i \n \n \n \n",getNum[0],getNum[1],getNum[2],getNum[3] );
        setPWM(2,'A',getNum[0],getNum[1]);
        setPWM(4,'A',getNum[2],getNum[3]);
	    }
    }
  }
}
