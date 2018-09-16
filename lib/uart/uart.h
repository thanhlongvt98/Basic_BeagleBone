#ifndef UART_H_
#define UART_H_

#define HARDWARE_PATH "/sys/devices/platform/bone_capemgr/slots"

using namespace std;

/*
    Global variable for opening 5 serial port.
*/
static int g_fd[5];

void openSerial(int num);

/*
    Add BB-UARTx overlay to slots file
*/
void enableUART(int num);

void setBaudrate(int num,int baud);

/*
    Save read bytes into buffer from shosen serial port.
*/
int readUART(int num, char *buffer,int buffSize);

void closeUART(int num);

#endif /* UART_H_ */
