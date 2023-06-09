/*
 * h_bridge.h - XvR 2020
 */

#ifndef _H_BRIDGE_2_H_
#define _H_BRIDGE_2_H_

// These pins are available on the shield via the header:
//
//		Mega	Uno
// digital 5	PE3	PD5
// digital 6	PH3	PD6
// digital 9	PH6	PB1
// analog 5	PF5	PC5

// The settings below are for the Mega, modify
// in case you want to use other pins
#define PORT_RPWM_2	PORTH
#define PIN_RPWM_2	PH3
#define DDR_RPWM_2	DDRH

#define PORT_LPWM_2	PORTH
#define PIN_LPWM_2	PH4
#define DDR_LPWM_2	DDRH

void init_h_bridge(void);
void h_bridge_set_percentage_2(signed char percentage);

#endif /* _H_BRIDGE_2_H_ */
