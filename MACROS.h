/*
 * MACROS.h
 *
 * Created: 7/18/2018 3:56:48 PM
 *  Author: Abdelaziz
 */ 


#ifndef MACROS_H_
#define MACROS_H_


                    /* BIT MANPULATING MACROS */


    /* This line sets a certain bit in any register*/
#define SET_BIT(REG,BIT)  (REG|=(1<<BIT))
    /* This line clears a certain bit in any register*/
#define CLEAR_BIT(REG,BIT)  (REG&=~(1<<BIT))
    /* This line toggles a certain bit in any register*/
#define TOGGLE_BIT(REG,BIT)  (REG^=(1<<BIT))
    /* This line checks if a certain bit in any register is set and returns true if yes*/
#define IS_BIT_SET(REG,BIT)  (REG&=(1<<BIT))
    /* This line checks if a certain bit in any register is cleared and returns true if yes*/
#define IS_BIT_CLEAR(REG,BIT)  (!(REG|=(1<<BIT)))


#endif /* MACROS_H_ */