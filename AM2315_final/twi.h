/*
 * twi.h
 *
 *  Created on: 24.09.2015
 *      Author: matthias
 */

#ifndef TWI_H_
#define TWI_H_

void TWI_Write_(uint8_t u8data);
uint8_t TWI_ReadACK_(void);
uint8_t TWI_ReadNACK_(void);
uint8_t TWI_GetStatus_(void);

void TWI_Init(void);
char TWI_Start(void);
void TWI_Stop(void);
char TWI_Write_Addr(uint8_t u8data);
char TWI_Write_Func(uint8_t u8data);
char TWI_Read(uint8_t reply[], uint8_t n_Byte);

#endif /* TWI_H_ */
