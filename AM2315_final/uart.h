/*
 * uart.h
 *
 *  Created on: 03.09.2015
 *      Author: matthias
 */

#ifndef UART_H_
#define UART_H_

void uart_init();
void uart_backspace(char n);
void uart_del(char n);
void uart_lineBack();
void uart_tab();
char uart_readChar();
void uart_readLine(char x[], char size);
void uart_writeChar(unsigned char buffer);
void uart_writeString(const char *s);
void uart_writeAbsatz();
void uart_writeInt8(char zahl);
void uart_writeInt16(short zahl);
void uart_writeFloat(float zahl2);
char uart_stringToInt8(char s[]);
short uart_stringToInt16(short s[]);

#endif /* UART_H_ */
