/*
 * am2315.c
 *
 *  Created on: 24.09.2015
 *      Author: matthias
 */

#include <avr/io.h>
#include <util/delay.h>
#include "twi.h"
#include "am2315.h"
//#include "uart.h"

uint8_t reply[10];
uint8_t n_Byte = 8;

void am2315_init() {
	TWI_Init();
}

char am2315_readSensor() {
	if (TWI_Start() == 0) {
	}
	if (TWI_Write_Addr(SLA_W) == 0) {
	}
	if (TWI_Write_Func(0x03) == 0) {
	}
	if (TWI_Write_Func(0x00) == 0) {
	}
	if (TWI_Write_Func(0x04) == 0) {
	}
	TWI_Stop();
	_delay_ms(50);

	if (TWI_Start() == 0) {
//		uart_writeString("TWI Error Start");
//		uart_writeAbsatz();
		return 0;
	}
	if (TWI_Write_Addr(SLA_W) == 0) {
//		uart_writeString("TWI Error SLA_W");
//		uart_writeAbsatz();
		return 0;
	}
	if (TWI_Write_Func(0x03) == 0) {
//		uart_writeString("TWI Error 0x03");
//		uart_writeAbsatz();
		return 0;
	}
	if (TWI_Write_Func(0x00) == 0) {
//		uart_writeString("TWI Error 0x00");
//		uart_writeAbsatz();
		return 0;
	}
	if (TWI_Write_Func(0x04) == 0) {
//		uart_writeString("TWI Error 0x04");
//		uart_writeAbsatz();
		return 0;
	}
	TWI_Stop();

	if (TWI_Start() == 0) {
		return 0;
	}
	if (TWI_Write_Addr(SLA_R) == 0) {
		return 0;
	}
	if (TWI_Read(reply, n_Byte) == 0) {
		return 0;
	}
	TWI_Stop();

	return 1;
}

float am2315_computeTemp() {
	if (reply[0] != 0x03) {
		return 0;
	}
	if (reply[1] != 4) {
		return 0;
	}
	char tempHi = reply[4];
	char tempLow = reply[5];
	char tempLow1 = tempLow & 0x0F;			// erste 4 Bit werden verwendet
	char tempLow2 = (tempLow & 0xF0) >> 4;	// letzte 4 Bit werden verwendet

	float temp = (float) (tempHi * 256 + tempLow2 * 16 + tempLow1) / 10;
	return temp;
}

float am2315_computeHumid() {
	if (reply[0] != 0x03) {
		return 0;
	}
	if (reply[1] != 4) {
		return 0;
	}
	char humidHi = reply[2];
	char humidLow = reply[3];
	char humidLow1 = humidLow & 0x0F;			// erste 4 Bit werden verwendet
	char humidLow2 = (humidLow & 0xF0) >> 4;	// letzte 4 Bit werden verwendet

	float humid = (float) (humidHi * 256 + humidLow2 * 16 + humidLow1) / 10;
	return humid;
}
