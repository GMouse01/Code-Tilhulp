#include <avr/io.h>
#include <util/delay.h>
#include "h_bridge.h"
#include "h_bridge_2.h"

#define DEBOUNCE_PERIOD_MS 10

void init(void)
{
    init_h_bridge();
}

void Sta_Stil(void)
{
    h_bridge_set_percentage(0);
}
void Rij_Vooruit(void)
{
    h_bridge_set_percentage(30);
}

void Rij_Achteruit(void)
{
    h_bridge_set_percentage(-30);
}

void Omhoog(void)
{
    h_bridge_set_percentage_2(30);
}

void Omlaag(void)
{
    h_bridge_set_percentage_2(-30);
}


int knop_Vooruit(void)
{
    if (PINF &(1<<PF1))
    {
        _delay_ms (DEBOUNCE_PERIOD_MS);
        if (PINF &(1<<PF1)) return 1;
    }
    return 0;
}

int knop_Achteruit(void)
{
    if (PINF &(1<<PF2))
    {
        _delay_ms (DEBOUNCE_PERIOD_MS);
        if (PINF &(1<<PF2)) return 1;
    }
    return 0;
}

int knop_Omhoog(void)
{
    if (PINF &(1<<PF3))
    {
        _delay_ms (DEBOUNCE_PERIOD_MS);
        if (PINF &(1<<PF1)) return 1;
    }
    return 0;
}

int knop_Omlaag(void)
{
    if (PINF &(1<<PF4))
    {
        _delay_ms (DEBOUNCE_PERIOD_MS);
        if (PINF &(1<<PF1)) return 1;
    }
    return 0;
}

int nood_stop(void)
{
    if (PINF &(1<<PF7))
    {
        _delay_ms (DEBOUNCE_PERIOD_MS);
        if (PINH &(1<<PF7)) return 1;
    }
    return 0;
}


int main(void)
{
    init();
    DDRF &= ~(1<<PF1);  // A1 input knop Vooruit
    DDRF &= ~(1<<PF2);  // A2 input knop Achteruit
    DDRF &= ~(1<<PF3);  // A2 input knop Omhoog
    DDRF &= ~(1<<PF4);  // A2 input knop Omlaag
    DDRF &= ~(1<<PF7);  // A7 input noodknop

    while(1)
    {
        if(!nood_stop)
        {

            if(!knop_Vooruit())
            {
                Rij_Vooruit();
            }

            else if(!knop_Achteruit())
            {
                Rij_Achteruit();
            }

            else
            {
                Sta_Stil();
            }

            if(!knop_Omhoog())
            {
                Rij_Vooruit();
            }

            else if(!knop_Omlaag())
            {
                Rij_Achteruit();
            }
        }
        else
        {
            Sta_Stil();
        }
    }
}






