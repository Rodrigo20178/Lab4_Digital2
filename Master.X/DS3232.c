#include "DS3232.h"
#include "I2C.h"

int sec = 0;
int min = 0;
int hora = 0;
int dia = 1;
int mes = 1;
int year = 1;

//Configuración de DS3232
int BCD_A_DEC(int convertir){
    return (convertir >> 4) * 10 + (convertir & 0x0F);
}
int DEC_A_BCD(int convertir){
    return ((convertir / 10) << 4) + (convertir % 10);
}

//Lectura I2C del DS3232
void setear_dia_tiempo(){
    I2C_Master_Start();            
    I2C_Master_Write(0xD0);        
    I2C_Master_Write(0x00);        
    I2C_Master_Write(DEC_A_BCD(sec));         
    I2C_Master_Write(DEC_A_BCD(min));         
    I2C_Master_Write(DEC_A_BCD(hora));        
    I2C_Master_Write(0x01);        
    I2C_Master_Write(DEC_A_BCD(dia));         
    I2C_Master_Write(DEC_A_BCD(mes));         
    I2C_Master_Write(DEC_A_BCD(year));        
    I2C_Master_Stop();             
}

void update_dia_tiempo(){
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0);
    I2C_Master_Stop();
    
 
    I2C_Master_Start();
    I2C_Master_Write(0xD1);
    sec = BCD_A_DEC(I2C_Master_Read(1));
    min = BCD_A_DEC(I2C_Master_Read(1));
    hora = BCD_A_DEC(I2C_Master_Read(1));
    I2C_Master_Read(1);
    dia = BCD_A_DEC(I2C_Master_Read(4));
    mes = BCD_A_DEC(I2C_Master_Read(5));
    year = BCD_A_DEC(I2C_Master_Read(6));
    I2C_Master_Stop();
    
    I2C_Master_Start();
    I2C_Master_Write(0xD1);
    I2C_Master_Read(1);
    I2C_Master_Stop();
    
}
