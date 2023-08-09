/* 
 * File:   ADC.h
 * Author: rodri
 *
 * Created on 3 de agosto de 2023, 11:02 AM
 */

#ifndef ADC_H
#define	ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void adc_init(char Select);

void adc_change_channel(uint8_t canal);

int adc_get_channel(void);

int adc_read(void);

#endif	/* ADC_H */

