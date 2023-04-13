* 
 * File:   pwm.h
 * Author: Luis Antunez
 *
 * Created on 12 de abril de 2023, 12:23 AM
 */

#ifndef pwm_H
#define pwm_H 

#include <xc.h>

void PWM_Init(void);
void PWM_dc(unsigned int duty_cycle);

#endif
