#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "pwm.h"

int enablePWMpin(int pwm_module, char pwm_part)
{
        std::fstream fs;
        string pwm_path = PWM_PATH + to_string(pwm_module);
        if (pwm_part == 'A')
        {
            fs.open(pwm_path + "/export",std::fstream::out);
            fs << "0";
            fs.close();
            return 1;
        }
        else if (pwm_part == 'B')
        {
            fs.open(pwm_path + "/export",std::fstream::out);
            fs << "1";
            fs.close();
            return 1;
        }        
}
int disablePWMpin(int pwm_module, char pwm_part)
{
    std::fstream fs;
    string pwm_path = PWM_PATH + to_string(pwm_module);
        if (pwm_part == 'A')
        {
            fs.open(pwm_path +"/unexport",std::fstream::out);
            fs << "0";
            fs.close();
            return 1;
        }
        else if (pwm_part == 'B')
        {
            fs.open(pwm_path +"/unexport",std::fstream::out);
            fs << "1";
            fs.close();
            return 1;
        }    
}
void setPWM(int pwm_module,char pwm_part, long int period, long int duty)
{
    std::fstream fs;
    string pwm_path = PWM_PATH + to_string(pwm_module);
    if (pwm_part == 'A')
    {
        pwm_path += "/pwm0/";
    }
    else
    {
        pwm_path += "/pwm1/";
    }
    cout << pwm_path << endl;
        fs.open ( pwm_path +"enable", std::fstream::out);
	    fs << "1";
	    fs.close();

        fs.open (pwm_path +"duty_cycle", std::fstream::out);
	    fs << "0";
	    fs.close();

        fs.open (pwm_path +"period", std::fstream::out);
	    fs << to_string(period);
	    fs.close();

        fs.open (pwm_path +"duty_cycle", std::fstream::out);
	    fs << to_string(duty);
	    fs.close();
    
}
void info(void)
{
    printf("\n 2A -> P9.14 \t 2B -> P9.16 \n");
    printf("\n 4A -> P8.19 \t 4B -> P8.13 \n");
}


//chip2 A P9.14 - EHRPWM1A
//chip2 B P9.16 - EEHPWM1B



