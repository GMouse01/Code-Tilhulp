/*
 * h_bridge.c - XvR 2020
 *
 * Use 8-bit timer. Uses interrupts in order to be able
 * to use the pins on the multifunction shield
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "h_bridge_2.h"

ISR(TIMER2_OVF_vect)
{
	if (OCR2A == 0 && OCR2B == 0)
	{
		PORT_RPWM_2 &= ~(1<<PIN_RPWM_2);
		PORT_LPWM_2 &= ~(1<<PIN_LPWM_2);
	}
	else if (OCR2A != 0)
	{
		PORT_LPWM_2 &= ~(1<<PIN_LPWM_2);
		PORT_RPWM_2 |= (1<<PIN_RPWM_2);
	}
	else if (OCR2B != 0)
	{
		PORT_RPWM_2 &= ~(1<<PIN_RPWM_2);
		PORT_LPWM_2 |= (1<<PIN_LPWM_2);
	}
}

ISR(TIMER2_COMPA_vect)
{
	if (OCR2A != 255)
	{
		PORT_RPWM_2 &= ~(1<<PIN_RPWM_2);
	}
}

ISR(TIMER2_COMPB_vect)
{
	if (OCR0B != 255)
	{
		PORT_LPWM_2 &= ~(1<<PIN_LPWM_2);
	}
}

void init_h_bridge_2(void)
{
	// Config pins as output
	DDR_RPWM_2 |= (1<<PIN_RPWM_2);
	DDR_LPWM_2 |= (1<<PIN_LPWM_2);

	// Output low
	PORT_RPWM_2 &= ~(1<<PIN_RPWM_2);
	PORT_LPWM_2 &= ~(1<<PIN_LPWM_2);

	// Use mode 0, clkdiv = 64
	TCCR2A = 0;
	TCCR2B = (0<<CS22) | (1<<CS21) | (1<<CS20);

	// Disable PWM output
	OCR2A = 0;
	OCR2B = 0;

	// Interrupts on OCA, OCB and OVF
	TIMSK2 = (1<<OCIE2B) | (1<<OCIE2A) | (1<<TOIE2);

	sei();
}

void h_bridge_set_percentage_2(signed char percentage)
{
	if (percentage >= -100 && percentage <= 100)
	{
		if (percentage >= 0)
		{
			// Disable LPWM, calculate RPWM
			OCR2B = 0;
			OCR2A = (255*percentage)/100;
		}
		else // percentage < 0
		{
			// Disable RPWM, calculate LPWM
			OCR2A = 0;
			OCR2B = (255*percentage)/-100;
		}
	}
}
