#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string>


#include "../lib/pwm/pwm.h"
#include "../lib/adc/adc.h"
#include "../lib/uart/uart.h"
#include "../lib/gpio/SimpleGPIO.h"

int main(void)
{
  int gi_gpioLED[4]={72,74,76,78};
  int gi_getNum[2];
  u_int8_t gi_getNumIdx = 2;
  int gi_numPort = 1, gi_numFlag;
  char gc_readBuffer[100];
  int gi_bytesRead = 0;
  int gi_status = 1; 

  // Init GPIO.
  gpio_export(72);
  gpio_export(74);
  gpio_export(76);
  gpio_export(78);
  gpio_set_dir(72,OUTPUT_PIN);
  gpio_set_dir(74,OUTPUT_PIN);
  gpio_set_dir(76,OUTPUT_PIN);
  gpio_set_dir(78,OUTPUT_PIN);

  // Init serial.
  openSerial(gi_numPort);
  setBaudrate(gi_numPort,B9600);

  while(gi_status) // gi_status = 0 when recieve 'x'.
  { 
    gi_bytesRead = readUART(gi_numPort, gc_readBuffer ,100);
    if (gi_bytesRead > 0) // Do nothing if recieve nothing.
    {
      if (gc_readBuffer[0] == 'x') // Close pwm pin and program if 'x' is the first byte.
      {
        printf("\n ------------- Close port ----------- \n");
        closeUART(gi_numPort);
        gi_status=0;
        printf("\n ------------- Close port -----------\n");
      }
      else
	    {
        gi_getNumIdx = 0;
        gi_numFlag = 0;
        string gstr_getNum = "";
        string::size_type sz;
        for (int l_count = 0; l_count < gi_bytesRead ; l_count++)
        {
          // Collect numbers.
          if ((gc_readBuffer[l_count] >= '0') && (gc_readBuffer[l_count] <= '9'))
          {
            gstr_getNum += gc_readBuffer[l_count];
            gi_numFlag = 1;
          }
          else
          {
            if (gi_numFlag == 1)
            {
              gi_getNum[gi_getNumIdx] = std::stoi(gstr_getNum,&sz,10);
              gi_getNumIdx = (gi_getNumIdx + 1 ) % 2;
              gi_numFlag = 0;
              gstr_getNum = "";
            }
            // Export numbers from A to B through 4 pins.
            for (int gi_tempCount = gi_getNum[0]; gi_tempCount <= gi_getNum[1]; gi_tempCount++)
            {
            setLED_4bits(gi_gpioLED,gi_tempCount);
            // Print to check.
            printf("Exported %d \n",gi_tempCount);
            clock_t g_timeStart = clock();
            while(clock() < g_timeStart + 2000000);
            }

          }
        }
	    }
    }
  }
}
