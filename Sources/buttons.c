/**
 * @author Juraj Holub <xholub40>
 * @brief Handle of button push interrupts.
 * @date December 2019
 * @project VUT FIT - IMP
 */

#include "buttons.h"
#include "display.h"
#include "lptmr0.h"
#include "MK60D10.h"

#define BTN_SW2 0x400     // Port E, bit 10
#define BTN_SW3 0x1000    // Port E, bit 12
#define BTN_SW4 0x8000000 // Port E, bit 27
#define BTN_SW5 0x4000000 // Port E, bit 26
#define BTN_SW6 0x800     // Port E, bit 11

void delay(long long bound)
{
  long long i;
  for(i=0;i<bound;i++);
}

void ButtonsInit()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	int buttons[] = {
		10,//SW2
		12,//SW3
		27,//SW4
		26,//SW5
		11//SW6
	};

	for (int i=0; i < 5; i++)
	{
		PORTE->PCR[buttons[i]] = ( PORT_PCR_ISF(0x01) /* Nuluj ISF (Interrupt Status Flag) */
							| PORT_PCR_IRQC(0x0A) /* Interrupt enable on failing edge */
							| PORT_PCR_MUX(0x01) /* Pin Mux Control to GPIO */
							| PORT_PCR_PE(0x01) /* Pull resistor enable... */
							| PORT_PCR_PS(0x01)); /* ...select Pull-Up */
	}
	NVIC_EnableIRQ(PORTE_IRQn);       /* Povol preruseni od portu B */
}

unsigned get_number_mask(unsigned num)
{
	switch (num)
	{
	case 0:
		return SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F;
	case 1:
		return SEG_B |SEG_C;
	case 2:
		return SEG_A | SEG_B | SEG_G | SEG_E | SEG_D;
	case 3:
		return SEG_A | SEG_B | SEG_C | SEG_D | SEG_G;
	case 4:
		return SEG_F | SEG_G | SEG_B | SEG_C;
	case 5:
		return SEG_A | SEG_F | SEG_G | SEG_C | SEG_D;
	case 6:
		return SEG_A | SEG_F | SEG_G | SEG_C | SEG_D | SEG_E;
	case 7:
		return SEG_A | SEG_B | SEG_C;
	case 8:
		return SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G;
	case 9:
		return SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G;
	default:
		return 0;
	}
}

void PORTE_IRQHandler(void)
{
	unsigned BUTTON_MASK = BTN_SW2 | BTN_SW3 | BTN_SW4 | BTN_SW5 | BTN_SW6;
	delay(60000);
    if (PORTE_ISFR & BTN_SW5 && !(GPIOE_PDIR & BTN_SW5))
    {
    	//handle
    	setState(Start);

    	PORTE_ISFR = BTN_SW5;
    }
    else if (PORTE_ISFR & BTN_SW3 && !(GPIOE_PDIR & BTN_SW3))
    {
    	//handle
		setState(Stop);

    	PORTE_ISFR = BTN_SW3;
    }
    else if (PORTE_ISFR & BTN_SW2 && !(GPIOE_PDIR & BTN_SW2))
    {
    	//handle
    	showNextSave();

    	PORTE_ISFR = BTN_SW2;
    }
    else if (PORTE_ISFR & BTN_SW4 && !(GPIOE_PDIR & BTN_SW4))
    {
    	//handle
    	saveTime();

    	PORTE_ISFR = BTN_SW4;
    }
    else if (PORTE_ISFR & BTN_SW6 && !(GPIOE_PDIR & BTN_SW6))
    {
    	//handle
    	setState(Idle);
    	clearTimers();

    	PORTE_ISFR = BTN_SW6;
    }
    else if (PORTE_ISFR & BUTTON_MASK && !(GPIOE_PDIR & BUTTON_MASK))
    {
    	PORTE_ISFR = BUTTON_MASK;
    }
}
