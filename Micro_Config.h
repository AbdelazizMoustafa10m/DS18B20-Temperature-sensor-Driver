/*
 * Micro_Config.h
 *
 * Created: 7/21/2018 2:38:16 PM
 *  Author: Abdelaziz
 */ 


#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

   #define F_CPU 1000000U
   #include <util/delay.h>
   #include <avr/io.h>
   #include "STD TYPES.h"
    /* input , output configuration*/
	
	/* there is a casting to make the controller see 0x3B as an address not as a value*/
	#define PORTA_OUTPUTREG (void *)0x3B
	#define PORTA_INPUTREG  (void *)0x39
	#define PORTA_DIRREG	(void *)0x3A
	
	#define PORTB_OUTPUTREG (void *)0x38
	#define PORTB_INPUTREG  (void *)0x36
	#define PORTB_DIRREG	(void *)0x37
	
	#define PORTC_OUTPUTREG (void *)0x35
	#define PORTC_INPUTREG  (void *)0x33
	#define PORTC_DIRREG	(void *)0x34
	
	#define PORTD_OUTPUTREG (void *)0x32
	#define PORTD_INPUTREG  (void *)0x30
	#define PORTD_DIRREG	(void *)0x31
	
	/* This line access an 8 bit IO register ,  volatile keyword is to prevent optimization*/
	#define REG8_Access(REG) (*(volatile uint8 *)REG)
	

#endif /* MICRO_CONFIG_H_ */