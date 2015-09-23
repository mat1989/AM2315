/*
 * main.c
 *
 *  Created on: 06.09.2015
 *      Author: matthias
 */

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "am2315.h"

float humid;
float temp;

int main() {
	//Uart INIT
	uart_init();
	for (int i = 0; i < 3; i++) {
		uart_writeAbsatz();
	}
	uart_writeString("AM2315 Test");
	uart_writeAbsatz();

	am2315_init();
	_delay_ms(200);

	while (1) {
		if(am2315_readSensor()){
			humid = am2315_computeHumid();
			temp =am2315_computeTemp();
			uart_writeString("Humid: ");
			uart_writeFloat(humid);
			uart_writeString("%RH Temp: ");
			uart_writeFloat(temp);
			uart_writeString("°C");
			uart_writeAbsatz();
		} else {
			uart_writeString("Fehler");
			uart_writeAbsatz();
		}
		_delay_ms(500);
	}
	return 0;
}
