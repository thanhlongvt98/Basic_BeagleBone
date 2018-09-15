#ifndef UART_H_
#define UART_H_

#define HARDWARE_PATH "/sys/devices/platform/bone_capemgr/slots"

using namespace std;
static int g_fd[5];

void openSerial(int num);
void enableUART(int num);
void setBaudrate(int num,int baud);
int readUART(int num, char *buffer,int buffSize);
void closeUART(int num);

#endif /* UART_H_ */
