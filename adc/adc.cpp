

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "adc.h"


int enableADCHardware(void)
{
    std::fstream adc_fs;
    adc_fs.open(ADC_HARDWARE_PATH,std::fstream::out);
    adc_fs << "BB-ADC";
    adc_fs.close();
    return 1;
}

float ADCRead(int ADC_num)
{
    std::fstream adc_fs;
    string adcReadPath = ADC_READ_PATH "in_voltage"+to_string(ADC_num)+"_raw";
    adc_fs.open(adcReadPath,std::fstream::in);
    uint16_t n;
    adc_fs >> n;
    adc_fs.close();
    return 1.8*n/4096;
}
/*
int main()
{
    while(1)
    {
        printf("%f \n",ADCRead(0));
    }
}
*/
