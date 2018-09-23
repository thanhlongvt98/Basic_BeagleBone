#ifndef ADC_H_
#define ADC_H_
 /*
 "P9.39", // AIN0
 "P9.40", // AIN1
 "P9.37", // AIN2
 "P9.38", // AIN3
 "P9.33", // AIN4
 "P9.36", // AIN5
 "P9.35", // AIN6
 */

#define ADC_HARDWARE_PATH "/sys/devices/platform/bone_capemgr/slots"
#define ADC_READ_PATH "/sys/bus/iio/devices/iio:device0/"

using namespace std;

/*
    Add BBB-ADC Overlay to slots file
*/
int enableADCHardware(void);
/**
 * @Brief Discription: read value from ADCx.
 * 
 * @param ADC_num : idex x of ADC.
 * @return float : value of ADCx
 */
float ADCRead(int ADC_num);

#endif /* ADC_H_ */
