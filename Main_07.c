/* 
 * File:   Main_07.c
 * Author: Luis Antunez
 *
 * Created on 9 de abril de 2023, 11:37 PM
 */

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>
#include <pic16f887.h>
#include <stdlib.h>
#include <stdio.h>
#include "pwm.h"

#define _XTAL_FREQ 250000
#define valPR2 194 // valor para 20Hz y prescaler de 16

uint16_t i=0;

void setup (void);
//void pwm_ini(void);
//void pwm_dc(uint16_t DutyCycle);

void __interrupt() isr(void)
{
    if(ADIF)
    {
        if (ADCON0bits.CHS == 0b00000001)
            CCPR1L = (ADRESH>>1)+124;
            
        else if (ADCON0bits.CHS == 0b00000010)
            //CCPR2L = (ADRESH>>1)+124;
             
            ADIF=0;
        
    }
    return;
}

void main() {
    setup();
   PWM_Init();
    
    while (1)
    {
     ADCON0bits.CHS = 0b00000001; // Seleccion del canal AN1
     __delay_ms(10);
     ADCON0bits.GO =1;  // Habilita las conversiones de analogico a digital
     __delay_ms(10);
     while (ADCON0bits.GO_DONE); // Verificacion del canal AN1
     CCPR1L = ADRESH;           // Mueve el valor almacenado en ADRESH a adc
     __delay_ms(10);
     
     
     ADCON0bits.CHS = 0b00000010;  // Cambio al canal AN2
     __delay_ms(10);
     ADCON0bits.GO = 1; // Iniciar la conversión en el canal AN2
     __delay_ms(10);
     while (ADCON0bits.GO_DONE); // Verificacion del canal AN2
     CCPR2L = ADRESH;           // Mueve el valor almacenado en ADRESH a adc
     __delay_ms(10);   
    }
    return;
}

void setup(void)
{
    
    TRISC = 0;
    PORTC=0;
    OSCCON = 0x25;
    ANSEL = 0xFF;
    ANSELH= 0x00;
    
    OSCCONbits.IRCF =0b0110; 
    OSCCONbits.SCS = 1; 
    //configuración de la interrupcion del TMR0
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 0;
    INTCONbits.GIE = 0;
    
    // Configuracion del ADC
    ADCON0bits.ADCS = 0b01; // divisor de reloj de 32
    __delay_ms(1);
    ADCON1bits.ADFM = 0;    // Justificado a la izquierda 
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;    // Referencia de voltaje 0
    ADCON0bits.ADON = 1;   // habilitar el adc
    ADIF =0;
    return;
}
