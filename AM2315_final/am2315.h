/*
 * am2315.h
 *
 *  Created on: 23.09.2015
 *      Author: matthias
 */

#ifndef AM2315_H_
#define AM2315_H_

void am2315_init();
char am2315_readSensor();
float am2315_computeTemp();
float am2315_computeHumid();

#endif /* AM2315_H_ */
