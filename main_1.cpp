
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string>

#include "pwm/pwm.h"
#include "adc/adc.h"
#include "uart/uart.h"
#include "gpio/SimpleGPIO.h"

#define BYTESNEED 4

int main(void)
{
  int gi_getNum[BYTESNEED];
  u_int8_t gui8_getNumIdx = 0;
  int gi_numPort = 1;
  int gi_numFlag;
  char gc_readBuffer[100];
  int gi_bytesRead = 0;
  int gi_status = 1;

  // Init PWM
  enablePWMpin(2, 'A');
  enablePWMpin(4, 'A');

  // Init serial port
  openSerial(gi_numPort);
  setBaudrate(gi_numPort, B9600);

  while (gi_status) // gi_status = 0 when recieve 'x'.
  {

    printf("Please type : \"FIRST_PERIOD FIRST_DUTY SECOND_PERIOD SECOND_DUTY \" \n");
    printf("            : \"P1 D1 P2 D2 \" \n");
    printf("By UART1 P9.24 (TX) P9.26 (RX) \n");
    gi_bytesRead = readUART(gi_numPort, gc_readBuffer, 100);
    if (gi_bytesRead > 0) // Do nothing if recieve nothing.
    {
      if (gc_readBuffer[0] == 'x') // Close pwm pin and program if 'x' is the first byte.
      {
        printf("\n ------------- Close port ----------- \n");
        closeUART(gi_numPort);
        gi_status = 0;
        printf("\n ------------- Close port -----------\n");
        disablePWMpin(2, 'A');
        disablePWMpin(4, 'A');
      }
      else // Do things.
      {
        gui8_getNumIdx = 0;
        gi_numFlag = 0;
        string getNumString = "";
        string::size_type sz;
        // Get numbers from receive bytes.
        for (int l_count = 0; l_count < gi_bytesRead; l_count++)
        {
          // Collect numbers.
          if ((gc_readBuffer[l_count] >= '0') && (gc_readBuffer[l_count] <= '9'))
          {
            getNumString += gc_readBuffer[l_count];
            gi_numFlag = 1;
          }
          else
          {
            if (gi_numFlag == 1)
            {
              gi_getNum[gui8_getNumIdx] = std::stoi(getNumString, &sz, 10);
              gui8_getNumIdx = (gui8_getNumIdx + 1) % BYTESNEED;
              gi_numFlag = 0;
              getNumString = "";
            }
          }
        }
        // Print to check.
        printf("P1 = %i \t D1 = %i \t P2 = %i \t D2 = %i \n \n \n \n",
               gi_getNum[0], gi_getNum[1], gi_getNum[2], gi_getNum[3]);
        // Set PWM
        setPWM(2, 'A', gi_getNum[0], gi_getNum[1]);
        setPWM(4, 'A', gi_getNum[2], gi_getNum[3]);
      }
    }
  }
}
