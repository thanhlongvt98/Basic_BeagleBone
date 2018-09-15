#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string>


#include "pwm/pwm.h"
#include "adc/adc.h"
#include "uart/uart.h"
#include "gpio/SimpleGPIO.h"


int main(void)
{
  int num_LED[4]={72,74,76,78};
  gpio_export(72);
  gpio_export(74);
  gpio_export(76);
  gpio_export(78);
  gpio_set_dir(72,OUTPUT_PIN);
  gpio_set_dir(74,OUTPUT_PIN);
  gpio_set_dir(76,OUTPUT_PIN);
  gpio_set_dir(78,OUTPUT_PIN);
  int getNum[2];
  u_int8_t getNumIdx = 2;
  double tempGetNumCount[4];
  int num=1, num_flag;
  char read_buffer[100];
  int g_bytes_read = 0;
  openSerial(num);
  setBaudrate(num,B9600);
  int g_status = 1; 
  while(g_status)
  { g_bytes_read = 12;
    //g_bytes_read = readUART(num, read_buffer ,100);
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
              getNumIdx = (getNumIdx + 1 ) % 2;
              num_flag = 0;
              getNumString = "";
            }

            for (int temp_count = 5; temp_count <= 15; temp_count++)
            {
            setLED_4bits(num_LED,temp_count);
            printf("Exported %d \n",temp_count);
            clock_t time_now = clock();
            while(clock() < time_now + 2000000);
            }

          }
        }
	    }
    }
  }
}
