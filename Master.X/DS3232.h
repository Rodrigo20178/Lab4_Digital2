/* 
 * File:   DS3232.h
 * Author: rodri
 *
 * Created on 9 de agosto de 2023, 09:58 AM
 */

#ifndef DS3232_H
#define	DS3232_H

int BCD_A_DEC(int convertir);
int DEC_A_BCD(int convertir);
void setear_dia_tiempo();
void update_dia_tiempo();

#endif	/* DS3232_H */

