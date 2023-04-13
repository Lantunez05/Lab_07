#include "pwm.h"
#include <xc.h> // incluir archivo de cabecera para los registros de PIC16F887
#define valPR2 194 // valor para 20Hz y prescaler de 16

void PWM_Init(void)
{
    TRISC = 0X02;     // Configura el Puerto C como salida
    CCP1CON = 0X1C;   // Configura CCP1 para PWM
    CCP2CON = 0b1100;   // Configura CCP2 para PWM
    T2CON = 0b00000111;     // Configura Timer2 para PWM
    PR2 = valPR2;             // Configura el periodo del PWM
    
    PWM_dc(0);  // Inicializa el ciclo de trabajo en 0%
}

void PWM_dc(unsigned int duty_cycle)
{
    CCPR1L = duty_cycle >> 2;   // Configura el ciclo de trabajo de CCP1
    CCP1CONbits.DC1B1 = (duty_cycle & 0b10) >> 1;
    CCP1CONbits.DC1B0 = duty_cycle & 0b01;
    
    CCPR2L = duty_cycle >> 2;   // Configura el ciclo de trabajo de CCP2
    CCP2CONbits.DC2B1 = (duty_cycle & 0b10) >> 1;
    CCP2CONbits.DC2B0 = duty_cycle & 0b01;
}
