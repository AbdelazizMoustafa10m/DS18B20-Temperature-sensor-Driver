/*
 * Interrupt_Driver_ATMEGA32.h
 *
 * Created: 7/25/2018 5:16:08 PM
 *  Author: Abdelaziz
 */ 


#ifndef INTERRUPT_DRIVER_ATMEGA32_H_
#define INTERRUPT_DRIVER_ATMEGA32_H_

     #include "MACROS.h"
	 #include "Micro_Config.h"
	 #include "STD TYPES.h"
	 #include <avr/interrupt.h>

     	/* Have The Flags That indicate , that the Event has occurred */
     	#define INT_FLAG_REGISTER			((void *)  0x5A)      /* GIFR */
     	/* Have The Global Interrupt Enable Flag which is used to Enable/Disable All interrupts*/
     	#define MCU_STATES_REGISTER			((void *)  0x5f)		/* SREG */
     	/* Have Flags That Control The TRIGGER Event of INT0,INT1 */
     	#define INT_EVENT_CONTROL_REGISTER	((void *)  0x55)		/* MCUCR */
     	/* Have Flags That Control The TRIGGER Event of INT2 */
     	#define INT_EVENT_CONTROL2_REGISTER	((void *)  0x54)		/* MCUCSR */
     	/* have Flags That Enable/Disable INT0 , INT1 and INT2 */
     	#define INT_FLAG_CONTROL_REGISTER	((void *)  0x5B)		/* GICR */
		
		#define I_BIT (7)
		#define INT0_ENABLE_BIT (6)
		#define INT1_ENABLE_BIT (7)
		#define INT2_ENABLE_BIT (5)
		
		typedef enum {RISINGMODE, FALLINGMODE, LOWLEVELMODE, EDGETRIG}interrupt_mode;
		typedef enum {INTERRUPT0, INTERRUPT1, INTERRUPT2}interrupt_source;
			
		/*this function will be used to ENABLE a certain interrupt in a certain mode*/
		void Ex_Interrupt_Enable(interrupt_source Source, interrupt_mode Mode);
		/*this function will be used to DISABLE a certain interrupt*/
		void Ex_Interrupt_Disable(interrupt_source Source);
		/*this function will be used to ENABLE the GLOBAL INNTERRUPT FLAG*/
		void Global_Interrupt_Enable(void);
		/*this function will be used to DISABLE the GLOBAL INTERRUPT FLAG*/
		void Global_Interrupt_Disable(void);

#endif /* INTERRUPT_DRIVER_ATMEGA32_H_ */