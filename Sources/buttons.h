/**
 * @author Juraj Holub <xholub40>
 * @brief Handle of button push interrupts.
 * @date December 2019
 * @project VUT FIT - IMP
 */

#ifndef SOURCES_BUTTONS_H_
#define SOURCES_BUTTONS_H_


/*
const unsigned NUMBER_2 = ;
const unsigned NUMBER_3 =;
const unsigned NUMBER_4 =;
const unsigned NUMBER_5 =;
const unsigned NUMBER_6 =;
const unsigned NUMBER_7 =;
const unsigned NUMBER_8 =;
const unsigned NUMBER_9 =;
*/
void delay(long long bound);
void ButtonsInit();
void PORTE_IRQHandler(void);

unsigned get_number_mask(unsigned num);
void One();
void Two();
void Clear();

#endif /* SOURCES_BUTTONS_H_ */
