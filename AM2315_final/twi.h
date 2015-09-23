/*
 * twi.h
 *
 *  Created on: 19.09.2015
 *      Author: matthias
 */

#ifndef TWI_H_
#define TWI_H_

void TWIInit(void);

void TWIStart(void);

//send stop signal
void TWIStop(void);

void TWIWrite(uint8_t u8data);

uint8_t TWIReadACK(void);

//read byte with NACK
uint8_t TWIReadNACK(void);

uint8_t TWIGetStatus(void);

#endif /* TWI_H_ */
