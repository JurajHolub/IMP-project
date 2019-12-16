/**
 * @author Juraj Holub <xholub40>
 * @brief LPTMR0 interrupt handle.
 * @date December 2019
 * @project VUT FIT - IMP
 */

#ifndef SOURCES_LPTMR0_H_
#define SOURCES_LPTMR0_H_

typedef enum State_e {
	Idle, Start, Stop
} State;

void LPTMR0Init();
void LPTMR0_IRQHandler(void);
void setState(State s);
void showNextSave();
void clearTimers();
void saveTime();
void LPTMR0_Idle(void);
void LPTMR0_Start(void);
void LPTMR0_Stop(void);

#endif /* SOURCES_LPTMR0_H_ */
