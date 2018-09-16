#ifndef PWM_H_
#define PWM_H_

 /****************************************************************
 * Constants
 ****************************************************************/

#define PWM_PATH "/sys/class/pwm/pwmchip"
using namespace std;

/****************************************************************
 *  Export pin.
 ****************************************************************/
int enablePWMpin(int pwm_module, char pwm_part);

/****************************************************************
 *  Unexport pin.
 ****************************************************************/
int disablePWMpin(int pwm_module, char pwm_part);

/****************************************************************
 *  set PWM period and duty for chosen pwm pin.
 ****************************************************************/
void setPWM(int pwm_module,char pwm_part, long int period, long int duty);

/****************************************************************
 *  Print infomation about pwm modules and their pins.
 ****************************************************************/
void info(void);


#endif /* PWM_H_ */