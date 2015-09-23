/*
 * am2315.c
 *
 *  Created on: 23.09.2015
 *      Author: matthias
 */

#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include "twi.h"
#include "am2315.h"

#define SLA_W 0xB8 //7Bit Adresse 0x5C
#define SLA_R 0xB9

short errBuffer;
short buffer2;
uint8_t reply[10];

void am2315_init() {
	//TWI INIT
	TWIInit();
//	uart_writeString("TWI INIT");
//	uart_writeAbsatz();
}

char am2315_readSensor() {
	//TWI Start
	TWIStart();
	_delay_ms(20);
	if (TWIGetStatus() != TW_START) {
		//Error
//		uart_writeString("TWI Start Error");
//		uart_writeAbsatz();
//		return 0;
	} else {
//		uart_writeString("TWI Start");
//		uart_writeAbsatz();
	}

	//TWI Send Addr
	TWIWrite(SLA_W);
	_delay_ms(20);
	if (TWIGetStatus() != TW_MT_SLA_ACK) {
		//Error
		errBuffer = TWIGetStatus();
//		uart_writeString("TWI Send Addr Error: ");
//		uart_writeInt8(errBuffer);
//		uart_writeAbsatz();
//		return 0;
	} else {
//		uart_writeString("TWI Send Addr");
//		uart_writeAbsatz();
	}

	//TWI Write 0x03
	TWIWrite(0x03);
	_delay_ms(20);
	if (TWIGetStatus() != TW_MT_DATA_ACK) {
		//Error
		errBuffer = TWIGetStatus();
//		uart_writeString("TWI Send 0x03 Error: ");
//		uart_writeInt8(errBuffer);
//		uart_writeAbsatz();
//		return 0;
	} else {
//		uart_writeString("TWI Send 0x03");
//		uart_writeAbsatz();
	}

	//TWI Write 0x00
	TWIWrite(0x00);
	_delay_ms(20);
	if (TWIGetStatus() != TW_MT_DATA_ACK) {
		//Error
		errBuffer = TWIGetStatus();
//		uart_writeString("TWI Send 0x00 Error: ");
//		uart_writeInt8(errBuffer);
//		uart_writeAbsatz();
//		return 0;
	} else {
//		uart_writeString("TWI Send 0x00");
//		uart_writeAbsatz();
	}

	//TWI Write 0x04
	TWIWrite(0x04);
	_delay_ms(20);
	if (TWIGetStatus() != TW_MT_DATA_ACK) {
		//Error
		errBuffer = TWIGetStatus();
//		uart_writeString("TWI Send 0x04 Error: ");
//		uart_writeInt8(errBuffer);
//		uart_writeAbsatz();
//		return 0;
	} else {
//		uart_writeString("TWI Send 0x04");
//		uart_writeAbsatz();
	}

	//TWI Stop
	TWIStop();
//	uart_writeString("TWI Stop");
//	uart_writeAbsatz();
	_delay_ms(20);

	//TWI Start
	TWIStart();
	_delay_ms(20);
	if (TWIGetStatus() != TW_START) {
		//Error
//		uart_writeString("TWI Start Error");
//		uart_writeAbsatz();
		return 0;
	} else {
//		uart_writeString("TWI Start");
//		uart_writeAbsatz();
	}

	//TWI Send Addr
	TWIWrite(SLA_W);
	_delay_ms(20);
	if (TWIGetStatus() != TW_MT_SLA_ACK) {
		//Error
		errBuffer = TWIGetStatus();
//		uart_writeString("TWI Send Addr Error: ");
//		uart_writeInt8(errBuffer);
//		uart_writeAbsatz();
		return 0;
	} else {
//		uart_writeString("TWI Send Addr");
//		uart_writeAbsatz();
	}

	//TWI Write 0x03
	TWIWrite(0x03);
	_delay_ms(20);
	if (TWIGetStatus() != TW_MT_DATA_ACK) {
		//Error
		errBuffer = TWIGetStatus();
//		uart_writeString("TWI Send 0x03 Error: ");
//		uart_writeInt8(errBuffer);
//		uart_writeAbsatz();
		return 0;
	} else {
//		uart_writeString("TWI Send 0x03");
//		uart_writeAbsatz();
	}

	//TWI Write 0x00
	TWIWrite(0x00);
	_delay_ms(20);
	if (TWIGetStatus() != TW_MT_DATA_ACK) {
		//Error
		errBuffer = TWIGetStatus();
//		uart_writeString("TWI Send 0x00 Error: ");
//		uart_writeInt8(errBuffer);
//		uart_writeAbsatz();
		return 0;
	} else {
//		uart_writeString("TWI Send 0x00");
//		uart_writeAbsatz();
	}

	//TWI Write 0x04
	TWIWrite(4);
	_delay_ms(20);
	if (TWIGetStatus() != TW_MT_DATA_ACK) {
		//Error
		errBuffer = TWIGetStatus();
//		uart_writeString("TWI Send 0x04 Error: ");
//		uart_writeInt8(errBuffer);
//		uart_writeAbsatz();
		return 0;
	} else {
//		uart_writeString("TWI Send 0x04");
//		uart_writeAbsatz();
	}

	//TWI Stop
	TWIStop();
//	uart_writeString("TWI Stop");
//	uart_writeAbsatz();
	_delay_ms(20);

	//TWI Start
	TWIStart();
	_delay_ms(20);
	if (TWIGetStatus() != TW_START) {
		//Error
		errBuffer = TWIGetStatus();
//		uart_writeString("TWI ReStart Error: ");
//		uart_writeInt8(errBuffer);
//		uart_writeAbsatz();
		return 0;
	} else {
//		uart_writeString("TWI ReStart");
//		uart_writeAbsatz();
	}

	//TWI Send Addr
	TWIWrite(SLA_R);
	_delay_ms(20);
	if (TWIGetStatus() != TW_MR_SLA_ACK) {
		//Error
		errBuffer = TWIGetStatus();
//		uart_writeString("TWI Send Addr Error: ");
//		uart_writeInt8(errBuffer);
//		uart_writeAbsatz();
		return 0;
	} else {
//		uart_writeString("TWI Send Addr");
//		uart_writeAbsatz();
	}

	//TWI Read Data
	for (unsigned char i = 0; i < 7; i++) {
		reply[i] = TWIReadACK();
		_delay_ms(50);
		if (TWIGetStatus() != TW_MR_DATA_ACK) {
			//Error
			errBuffer = TWIGetStatus();
//			uart_writeString("TWI Receive Data Error: ");
//			uart_writeInt8(errBuffer);
//			uart_writeAbsatz();
			return 0;
		} else {
//		uart_writeInt8(reply[i]);
//		uart_writeChar('-');
		}
	}
	reply[7] = TWIReadNACK();
	if (TWIGetStatus() != TW_MR_DATA_NACK) {
		//Error
		errBuffer = TWIGetStatus();
//		uart_writeString("TWI Receive Data Error: ");
//		uart_writeInt8(errBuffer);
//		uart_writeAbsatz();
		return 0;
	} else {
//		uart_writeInt8(reply[7]);
//		uart_writeAbsatz();
	}

	//TWI Stop
	TWIStop();
//	uart_writeString("TWI Stop");
//	uart_writeAbsatz();
	return 1;
}

float am2315_computeTemp() {
	if (reply[0] != 0x03) {return 0;}
	if (reply[1] != 4) {return 0;}
	char tempHi  = reply[4];
	char tempLow = reply[5];
	char tempLow1 = tempLow & 0x0F;			// erste 4 Bit werden verwendet
	char tempLow2 = (tempLow & 0xF0) >> 4;	// letzte 4 Bit werden verwendet

	float temp =(float) (tempHi*256+tempLow2*16+tempLow1)/10;
	return temp;
}

float am2315_computeHumid() {
	if (reply[0] != 0x03) {return 0;}
	if (reply[1] != 4) {return 0;}
	char humidHi  = reply[2];
	char humidLow = reply[3];
	char humidLow1 = humidLow & 0x0F;			// erste 4 Bit werden verwendet
	char humidLow2 = (humidLow & 0xF0) >> 4;	// letzte 4 Bit werden verwendet

	float humid =(float) (humidHi*256+humidLow2*16+humidLow1)/10;
	return humid;
}
