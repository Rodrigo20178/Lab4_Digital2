/*
 * File:   Lab4_Master.c
 * Author: Rodrigo García
 *
 * Created on 3 de agosto de 2023, 10:32 AM
 */

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
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

//LIBRERÍAS
#include <stdint.h>
#include "I2C.h"
#include "LCD8bits.h"
#include "IOCB.h"
#include "DS3232.h"
#include <pic16f887.h>
#include <xc.h>
#include <stdio.h>
#include <stdint.h>

//CONSTANTES
#define _XTAL_FREQ 8000000
#define RS RE0
#define EN RE1

//VARIABLES
int sec = 0;
int min = 0;
int hora = 0;
int dia = 1;
int mes = 1;
int year = 1;
float pot;
char valor[20];

//PROTOTIPOS DE FUNCIONES
void setup(void);


//MAIN
void main(void) {
    setup();
    while(1){

        if (PORTBbits.RB0 == 0){
            while (!PORTBbits.RB0);
            dia++;                      // Si se apacha botón RB0, aumentar el valor de días
            if (dia > 31) dia = 1;      // Si el día es mayor a 31, reiniciar a 1
            I2C_Master_Start(); 
            I2C_Master_Write(0xD0);        
            I2C_Master_Write(4);  
            I2C_Master_Write(DEC_A_BCD(dia));      // Escribir valor de días  
            I2C_Master_Stop();  
        }
        
        if (PORTBbits.RB1 == 0){
            while (!PORTBbits.RB1);
            mes++;                      // Si se apacha botón RB1, aumentar valor de meses
            if (mes > 12) mes = 1;      // Si el mes es mayor a 12, reiniciar a 1
            I2C_Master_Start(); 
            I2C_Master_Write(0xD0);        
            I2C_Master_Write(5);  
            I2C_Master_Write(DEC_A_BCD(mes));     // Escribir valor de meses  
            I2C_Master_Stop();  
        }
        
        if (PORTBbits.RB2 == 0){
            while (!PORTBbits.RB2);
            year++;                     // Si se apacha botón RB2, aumentar valor de años
            if (year > 23) year = 0;    // Si el año es mayor a 23, reiniciar a 0
            I2C_Master_Start(); 
            I2C_Master_Write(0xD0);        
            I2C_Master_Write(6);  
            I2C_Master_Write(DEC_A_BCD(year));    // Escribir valor de años 
            I2C_Master_Stop();  
        }
        
   
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        pot = I2C_Master_Read(0);           // Leer valor del potenciómetro
        I2C_Master_Stop();
        __delay_ms(200); 

        char dia_0 = dia % 10;
        char dia_1 = dia / 10;
        char mes_0 = mes % 10;
        char mes_1 = mes / 10;
        char year_0 = year % 10;
        char year_1 = year / 10;
        
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("Fecha: ");
        Lcd_Write_Char(dia_1 + '0');
        Lcd_Write_Char(dia_0 + '0');
        Lcd_Write_String("/");
        Lcd_Write_Char(mes_1 + '0');
        Lcd_Write_Char(mes_0 + '0');
        Lcd_Write_String("/");
        Lcd_Write_Char(year_1 + '0');
        Lcd_Write_Char(year_0 + '0');
        
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("Temp: ");
        sprintf(valor, "%.2f", pot);
        Lcd_Write_String(valor);
        Lcd_Set_Cursor(2,13);
        Lcd_Write_String("C");
        
    }
    return;
}
//CONFIGURACIONES
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    PORTA = 0;
    TRISB = 0b00000111;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    TRISE = 0;
    PORTE = 0;
    
    //Configuración IOCB
    OPTION_REGbits.nRBPU = 0;
    ioc_int(0);
    ioc_int(1);
    ioc_int(2);
    
    //Configuración LCD
    Lcd_Init();
    
    //Configuración I2C
    I2C_Master_Init(100000);
    setear_dia_tiempo();
}




