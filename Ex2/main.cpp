/**
 * @Brief Discription: program to read the voltage value from one of two ADC pins, 
 * user uses UART to select which ADC is used and get it's data display through Terminal.
 * 
 * @file main.cpp
 * @Author: Silent - thanhlongvt98@gmail.com
 * @date 2018-09-23
 */
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string>
#include <time.h>

#include "../lib/pwm/pwm.h"
#include "../lib/adc/adc.h"
#include "../lib/uart/uart.h"
#include "../lib/gpio/SimpleGPIO.h"

#define BYTESNEED 4
#define MAXBUFFERSIZE 100
#define EXITCHAR 'x'

/**
 * @Brief Discription: main function.
 * 
 * @return int 
 */

int main(void)
{
  int gi_getNum;
  int gi_numPort = 1, gi_numFlag;
  char gc_readBuffer[MAXBUFFERSIZE];
  int gi_bytesRead = 0;
  int gi_status = 1;

  // Init serial.
  openSerial(gi_numPort);
  setBaudrate(gi_numPort,B9600);

  while(gi_status) // gi_status = 0 when recieve 'x'.
  {
    gi_bytesRead = readUART(gi_numPort, gc_readBuffer ,MAXBUFFERSIZE);
    if (gi_bytesRead > 0) // Do nothing if recieve nothing.
    {
      if (gc_readBuffer[0] == EXITCHAR) // Close port
      {
        printf("\n ------------- Close port ----------- \n");
        closeUART(gi_numPort);
        gi_status=0;
        printf("\n ------------- Close port -----------\n");
      }
      else // Do things.
	    {
        gi_numFlag = 0;
        string getNumString = "";
        string::size_type sz;
        // Collect number.
        for (int l_count = 0; l_count < gi_bytesRead ; l_count++)
        {
          if ((gc_readBuffer[l_count] >= '0') && (gc_readBuffer[l_count] <= '9'))
          {
            getNumString += gc_readBuffer[l_count];
            gi_numFlag = 1;
          }
          else
          {
            if (gi_numFlag == 1)
            {
              gi_getNum = std::stoi(getNumString,&sz,10);
              gi_numFlag = 0;
            }

          }
        }


        int times = 100;
        clock_t time_now;

        // Delay.
        while(times)
        {
            time_now = clock();
            printf("%f \n",ADCRead(gi_getNum));
            times--;
            while(100-(clock() - time_now)/1000);
        }
	    }
    }
  }
}
