/*
 * twi.c
 *
 *  Created on: 24.09.2015
 *      Author: matthias
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <util/twi.h>
#include "twi.h"
//#include "uart.h"

/*
 * Low Level Funktionen
 * *************************************************************
 */
//Quelle: http://www.embedds.com/programming-avr-i2c-interface/
void TWI_Write_(uint8_t u8data) {
	TWDR = u8data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0) {
	}
}

uint8_t TWI_ReadACK_(void) {	//uint8_t
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while ((TWCR & (1 << TWINT)) == 0) {
	}
	return TWDR;
}

//read byte with NACK
uint8_t TWI_ReadNACK_(void) { //uint8_t
	TWCR = (1 << TWINT) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0) {
	}
	return TWDR;
}

uint8_t TWI_GetStatus_(void) {
	uint8_t status;
	//mask status
	status = TWSR & 0xF8;
	return status;
}

/*
 * Oeffentliche Funktionen
 * *************************************************************
 */
void TWI_Init(void) {
	//set SCL to 400kHz
//	TWSR = 0x00;
//	TWBR = 0x0C;
	TWBR = ~((1 << TWPS0) | (1 << TWPS1)); 	//Prescaler
	TWSR = 32;								// 8MHz 100kHz
	//enable TWI
	TWCR = (1 << TWEN);
}

char TWI_Start(void) {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0) {
	}
	_delay_ms(10);
	char twi_status = TWI_GetStatus_();
	if ((twi_status != TW_START) && (twi_status != TW_REP_START)) {
		//Error
		return 0;
	} else {
		return 1;
	}
}

void TWI_Stop(void) {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	_delay_ms(10);
}

char TWI_Write_Addr(uint8_t u8data) {
	TWI_Write_(u8data);
	_delay_ms(20);
	char twi_status = TWI_GetStatus_();
	if ((twi_status != TW_MR_SLA_ACK) && (twi_status != TW_MT_SLA_ACK)) {
		//Error
		return 0;
	} else {
		return 1;
	}
}

char TWI_Write_Func(uint8_t u8data) {
	TWI_Write_(u8data);
	_delay_ms(20);
	if (TWI_GetStatus_() != TW_MT_DATA_ACK) {
		//Error
		return 0;
	} else {
		return 1;
	}
}

char TWI_Read(uint8_t reply[], uint8_t n_Byte) {
	//TWI Read Data
	for (unsigned char i = 0; i < n_Byte; i++) {
		reply[i] = TWI_ReadACK_();
//		uart_writeInt8(reply[i]);
//		uart_writeString("-");
		_delay_ms(5);
		if (TWI_GetStatus_() != TW_MR_DATA_ACK) {
			//Error
			return 0;
		}
	}
	reply[n_Byte] = TWI_ReadNACK_();
//	uart_writeInt8(reply[n_Byte]);
//	uart_writeAbsatz();
	if (TWI_GetStatus_() != TW_MR_DATA_NACK) {
		//Error
		return 0;
	} else {
		return 1;
	}
}

