#ifndef PWM_H_
#define PWM_H_

 /****************************************************************
 * Constants
 ****************************************************************/

#define PWM_PATH "/sys/class/pwm/pwmchip"
using namespace std;

/****************************************************************
 * pwm
 ****************************************************************/
int enablePWMpin(int pwm_module, char pwm_part);
int disablePWMpin(int pwm_module, char pwm_part);
void setPWM(int pwm_module,char pwm_part, long int period, long int duty);
void info(void);


#endif /* SIMPLEGPIO_H_ */