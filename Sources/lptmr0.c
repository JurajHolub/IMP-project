/**
 * @author Juraj Holub <xholub40>
 * @brief LPTMR0 interrupt handle.
 * @date December 2019
 * @project VUT FIT - IMP
 */

#include "lptmr0.h"
#include "display.h"
#include "buttons.h"
#include "MK60D10.h"

State state = Idle;
unsigned sec[5] = {0};
unsigned ms[5] = {0};
unsigned idx = {0};

void setState(State s)
{
	if (s == Stop && state == Idle) return;
	if (s == Idle && state == Start) return;

	state = s;
}

void showNextSave()
{
	if (state == Stop)
	{
		while (1)
		{
			idx = (idx + 1) % 5;
			if (idx == 0) break;
			if (sec[idx] && ms[idx]) break;
		}
	}
}

void clearTimers()
{
	for (int i=0; i < 5; i++)
	{
		sec[i] = ms[i] = 0;
	}
}

void saveTime()
{
	static unsigned timer_index = 0;

	if (state != Start) return;

	timer_index++;
	if (timer_index == 5) timer_index = 1;

	sec[timer_index] = sec[0];
	ms[timer_index] = ms[0];
}

void LPTMR0Init()
{
    SIM_SCGC5 |= SIM_SCGC5_LPTIMER_MASK; // Enable clock to LPTMR
    LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;   // Turn OFF LPTMR to perform setup
    LPTMR0_PSR = ( LPTMR_PSR_PRESCALE(0x01) // 1KHz clock
                 | LPTMR_PSR_PBYP_MASK   // LPO feeds directly to LPT
                 | LPTMR_PSR_PCS(1)) ;   // use the choice of clock
    LPTMR0_CMR = 0;                  // Set compare value
    LPTMR0_CSR =(  LPTMR_CSR_TCF_MASK    // Clear any pending interrupt (now)
                 | LPTMR_CSR_TIE_MASK    // LPT interrupt enabled
                );
    NVIC_EnableIRQ(LPTMR0_IRQn);         // enable interrupts from LPTMR0
    LPTMR0_CSR |= LPTMR_CSR_TEN_MASK;;    // Turn ON LPTMR0 and start counting
}

void LPTMR0_IRQHandler(void)
{
	if (state == Start)
	{
		LPTMR0_Start();
	}
	else if (state == Stop)
	{
		LPTMR0_Stop();
	}
	else
	{
		LPTMR0_Idle();
	}

    LPTMR0_CMR = 0;                // !! the CMR reg. may only be changed while TCF == 1
    LPTMR0_CSR |=  LPTMR_CSR_TCF_MASK;   // writing 1 to TCF tclear the flag
}

void LPTMR0_Idle(void)
{
	static unsigned swap = 0;
	static unsigned swap_counter = 0;
    swap_counter = (swap_counter + 1) % 3;

    if (!swap_counter)
	{
		GPIOA_PDOR = ~get_number_mask(0);
		if (swap == 0)
		{
			GPIOA_PDOR |= PANEL_1;
			GPIOA_PDOR &= ~PANEL_2;
			GPIOA_PDOR &= ~PANEL_3;
			GPIOA_PDOR &= ~PANEL_4;
		}
		else if (swap == 1)
		{
			GPIOA_PDOR &= ~PANEL_1;
			GPIOA_PDOR |= PANEL_2;
			GPIOA_PDOR &= ~PANEL_3;
			GPIOA_PDOR &= ~PANEL_4;
			GPIOA_PDOR &= ~SEG_H;
		}
		else if (swap == 2)
		{
			GPIOA_PDOR &= ~PANEL_1;
			GPIOA_PDOR &= ~PANEL_2;
			GPIOA_PDOR |= PANEL_3;
			GPIOA_PDOR &= ~PANEL_4;
		}
		else if (swap == 3)
		{
			GPIOA_PDOR &= ~PANEL_1;
			GPIOA_PDOR &= ~PANEL_2;
			GPIOA_PDOR &= ~PANEL_3;
			GPIOA_PDOR |= PANEL_4;
		}
		swap = (swap + 1) % 4;
	}
}

void LPTMR0_Start()
{
	static unsigned sec_counter = 0;
	static unsigned ms_counter = 0;
	static unsigned swap = 0;
	static unsigned swap_counter = 0;

    sec_counter = (sec_counter + 1) % 1000;
    ms_counter = (ms_counter + 1) % 100;
    //swap_counter = (swap_counter + 1) % 2;

    if (!ms_counter)
    {
    	ms[idx] = (ms[idx] + 1) % 100;
    }
    if (!sec_counter)
    {
    	sec[idx] = (sec[idx] + 1) % 100;
    }

    //if (!swap_counter)
	{
		if (swap == 0)
		{
			GPIOA_PDOR = ~get_number_mask((sec[idx] / 10) % 10);
			GPIOA_PDOR |= PANEL_1;
			GPIOA_PDOR &= ~PANEL_2;
			GPIOA_PDOR &= ~PANEL_3;
			GPIOA_PDOR &= ~PANEL_4;
		}
		else if (swap == 1)
		{
			GPIOA_PDOR = ~get_number_mask(sec[idx] % 10);
			GPIOA_PDOR &= ~PANEL_1;
			GPIOA_PDOR |= PANEL_2;
			GPIOA_PDOR &= ~PANEL_3;
			GPIOA_PDOR &= ~PANEL_4;
			GPIOA_PDOR &= ~SEG_H;
		}
		else if (swap == 2)
		{
			GPIOA_PDOR = ~get_number_mask((ms[idx] / 10) % 10);
			GPIOA_PDOR &= ~PANEL_1;
			GPIOA_PDOR &= ~PANEL_2;
			GPIOA_PDOR |= PANEL_3;
			GPIOA_PDOR &= ~PANEL_4;
		}
		else if (swap == 3)
		{
			GPIOA_PDOR = ~get_number_mask(ms[idx] % 10);
			GPIOA_PDOR &= ~PANEL_1;
			GPIOA_PDOR &= ~PANEL_2;
			GPIOA_PDOR &= ~PANEL_3;
			GPIOA_PDOR |= PANEL_4;
		}
		swap = (swap + 1) % 4;
	}
}

void LPTMR0_Stop(void)
{
	static unsigned swap = 0;
	static unsigned swap_counter = 0;
    swap_counter = (swap_counter + 1) % 3;

    if (!swap_counter)
	{
		if (swap == 0)
		{
			GPIOA_PDOR = ~get_number_mask((sec[idx] / 10) % 10);
			GPIOA_PDOR |= PANEL_1;
			GPIOA_PDOR &= ~PANEL_2;
			GPIOA_PDOR &= ~PANEL_3;
			GPIOA_PDOR &= ~PANEL_4;
		}
		else if (swap == 1)
		{
			GPIOA_PDOR = ~get_number_mask(sec[idx] % 10);
			GPIOA_PDOR &= ~PANEL_1;
			GPIOA_PDOR |= PANEL_2;
			GPIOA_PDOR &= ~PANEL_3;
			GPIOA_PDOR &= ~PANEL_4;
			GPIOA_PDOR &= ~SEG_H;
		}
		else if (swap == 2)
		{
			GPIOA_PDOR = ~get_number_mask((ms[idx] / 10) % 10);
			GPIOA_PDOR &= ~PANEL_1;
			GPIOA_PDOR &= ~PANEL_2;
			GPIOA_PDOR |= PANEL_3;
			GPIOA_PDOR &= ~PANEL_4;
		}
		else if (swap == 3)
		{
			GPIOA_PDOR = ~get_number_mask(ms[idx] % 10);
			GPIOA_PDOR &= ~PANEL_1;
			GPIOA_PDOR &= ~PANEL_2;
			GPIOA_PDOR &= ~PANEL_3;
			GPIOA_PDOR |= PANEL_4;
		}
		swap = (swap + 1) % 4;
	}
}
