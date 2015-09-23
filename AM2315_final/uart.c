/*
 * uart.c
 *
 *  Created on: 03.09.2015
 *      Author: matthias
 */

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 8000000UL  // Systemtakt in Hz - Definition als unsigned long beachten
#endif

#define BAUD 9600UL      // Baudrate, muss in Hterm gleich eingestellt sein.

/*
 * BAUD 9600UL
 */
void uart_init() {
// Berechnungen
	short UBRR_VAL = ((F_CPU + BAUD * 8) / (BAUD * 16) - 1);	// clever runden

	// USART
	UCSRB = (1 << RXEN) | (1 << TXEN);  // enable receiver and transmitter
	UCSRB |= (1 << RXCIE);            //Interrupt ein
	UCSRC |= (1 << UCSZ0) | (1 << UCSZ1); // 8 bit (default: asynchronous, no parity,1stop-bit)
	UBRRH = UBRR_VAL >> 8;
	UBRRL = UBRR_VAL & 0x0FF;

	sei();
	//Schaltet den Interrupt ein
}

void uart_backspace(char n) {
	for (char i = 0; i < n; i++) {
		uart_writeChar('\b'); //Backspace
	}
}

void uart_del(char n) {
	for (char i = 0; i < n; i++) {
		uart_writeChar(0x7F); //Löschen
	}
}

void uart_lineBack() {
	uart_writeChar('\r');
}

void uart_tab() {
	uart_writeChar(11); //Tab
}

char uart_readChar() {
	while ((UCSRA & (1 << RXC)) == 0) {
	} //warten bis etwas empfangen wird
	char c = UDR;
	return c;
}

void uart_readLine(char x[], char size) {
	char n = 0;
	volatile char c;

	while (c != 13 && n < size) {
		c = uart_readChar();
		x[n] = c;
		n++;
	}
	x[(n - 1)] = '\0';
}

void uart_writeChar(unsigned char buffer) {
	while (!(UCSRA & (1 << UDRE)))
		;	//Warten bis Senden abgeschlossen
	UDR = buffer;                  //Daten senden
}

void uart_writeString(const char *s) {
	while (!(UCSRA & (1 << UDRE)))
		;   //Warten bis UDR leer ist für Senden
	//UDR ='!'; 						//Sendestart signalisieren

	while (*s) {
		uart_writeChar(*s);         //Zeichen senden
		s++;               //Adresse erhöhen
	}
}

void uart_writeAbsatz() {
	uart_writeChar('\r');
	uart_writeChar('\n');
}

void uart_writeInt8(char zahl) {
	char hunderter;
	char zehner;
	char einer;
	char showZero = 0;

	if (zahl < 0) {
		zahl = -zahl;
		uart_writeChar('-');
	}

	if (zahl >= 100) {
		hunderter = zahl / 100;
		zahl = zahl % 100;
		uart_writeChar('0' + hunderter);
		showZero = 1;
	}

	if (zahl >= 10 || showZero == 1) {
		zehner = zahl / 10;
		zahl = zahl % 10;
		uart_writeChar('0' + zehner);
	}

	einer = zahl;
	uart_writeChar('0' + einer);
}

void uart_writeInt16(short zahl) {
	char zehntausender;
	char tausender;
	char hunderter;
	char zehner;
	char einer;
	char showZero = 0;

	if (zahl < 0) {
		zahl = -zahl;
		uart_writeChar('-');
	}

	if (zahl >= 10000) {
		zehntausender = zahl / 10000;
		zahl = zahl % 10000;
		uart_writeChar('0' + zehntausender);
		showZero = 1;
	}

	if (zahl >= 1000 || showZero == 1) {
		tausender = zahl / 1000;
		zahl = zahl % 1000;
		uart_writeChar('0' + tausender);
		showZero = 1;
	}

	if (zahl >= 100 || showZero == 1) {
		hunderter = zahl / 100;
		zahl = zahl % 100;
		uart_writeChar('0' + hunderter);
		showZero = 1;
	}

	if (zahl >= 10 || showZero == 1) {
		zehner = zahl / 10;
		zahl = zahl % 10;
		uart_writeChar('0' + zehner);
		showZero = 1;
	}

	einer = zahl;
	uart_writeChar('0' + einer);
}

void uart_writeFloat(float zahl2) {
	long zahl = (long) (zahl2 * 100);
	char zehntausender;
	char tausender;
	char hunderter;
	char zehner;
	char einer;
	char showZero = 0;

	if (zahl < 0) {
		zahl = -zahl;
		uart_writeChar('-');
	}

	if (zahl >= 10000) {
		zehntausender = zahl / 10000;
		zahl = zahl % 10000;
		uart_writeChar('0' + zehntausender);
		showZero = 1;
	}

	if (zahl >= 1000 || showZero == 1) {
		tausender = zahl / 1000;
		zahl = zahl % 1000;
		uart_writeChar('0' + tausender);
		showZero = 1;
	}

	showZero = 1;
	if (zahl >= 100 || showZero == 1) {
		hunderter = zahl / 100;
		zahl = zahl % 100;
		uart_writeChar('0' + hunderter);
		showZero = 1;
	}

	uart_writeChar('.');

	if (zahl >= 10 || showZero == 1) {
		zehner = zahl / 10;
		zahl = zahl % 10;
		uart_writeChar('0' + zehner);
		showZero = 1;
	}

	einer = zahl;
	uart_writeChar('0' + einer);
}

char uart_stringToInt8(char s[]) {
	char resultat = 0;
	char i = 0;
	while (s[i] != '\0') {
		resultat = resultat * 10;
		resultat = resultat + s[i] - '0';
		i++;
	}
	return resultat;
}

short uart_stringToInt16(short s[]) {
	short resultat = 0;
	char i = 0;
	while (s[i] != '\0') {
		resultat = resultat * 10;
		resultat = resultat + s[i] - '0';
		i++;
	}
	return resultat;
}
