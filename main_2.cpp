#include <stdio.h>
#include <unistd.h>
//#include <errno.h>
//#include <iostream>
//#include <fstream>
#include <termios.h>
#include <stdlib.h>
#include <string>
#include <time.h>

#include "pwm/pwm.h"
#include "adc/adc.h"
#include "uart/uart.h"
#include "gpio/SimpleGPIO.h"


int main(void)
{
  int getNum;
  double tempGetNumCount;
  int num=1, num_flag;
  char read_buffer[100];
  int g_bytes_read = 0;
  openSerial(num);
  setBaudrate(num,B9600);
  int g_status = 1;
  while(g_status)
  { 
    g_bytes_read = readUART(num, read_buffer ,100);
    if (g_bytes_read > 0)
    {
      if (read_buffer[0] == 'x')
      {
        printf("\n ------------- Close port ----------- \n");
        closeUART(num);
        g_status=0;
        printf("\n ------------- Close port -----------\n");
      }
      else
	    {
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
              getNum = std::stoi(getNumString,&sz,10);
              num_flag = 0;
            }
            
          }
        }
        int times = 100;
        clock_t time_now;
        while(times)
        {
            time_now = clock();
            printf("%f \n",ADCRead(getNum));
            times--;
            while(100-(clock() - time_now)/1000);
        }
	    }
    }
  }
}
