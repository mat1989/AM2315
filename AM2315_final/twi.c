/*
 * twi.c
 *
 *  Created on: 19.09.2015
 *      Author: matthias
 */

#include <avr/io.h>
#include <stdio.h>

//Quelle: http://www.embedds.com/programming-avr-i2c-interface/
void TWIInit(void) {
	//set SCL to 400kHz
//	TWSR = 0x00;
//	TWBR = 0x0C;
	TWBR = ~((1 << TWPS0) | (1 << TWPS1)); 	//Prescaler
	TWSR = 32;								// 8MHz 100kHz
	//enable TWI
	TWCR = (1 << TWEN);
}

void TWIStart(void) {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0) {
	}
}
//send stop signal
void TWIStop(void) {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWIWrite(uint8_t u8data) {
	TWDR = u8data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0) {
	}
}

uint8_t  TWIReadACK(void) {//uint8_t
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while ((TWCR & (1 << TWINT)) == 0) {
	}
	return TWDR;
}

//read byte with NACK
uint8_t  TWIReadNACK(void) { //uint8_t
	TWCR = (1 << TWINT) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0) {
	}
	return TWDR;
}

uint8_t TWIGetStatus(void) {
	uint8_t status;
	//mask status
	status = TWSR & 0xF8;
	return status;
}

