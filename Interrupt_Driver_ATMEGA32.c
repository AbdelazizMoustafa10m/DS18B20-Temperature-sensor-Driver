/*
 * Interrupt_Driver_ATMEGA32.c
 *
 * Created: 7/25/2018 7:37:53 PM
 *  Author: Abdelaziz
 */ 
  
  
   #include "Interrupt_Driver_ATMEGA32.h"
   
   void Ex_Interrupt_Enable(interrupt_source Source, interrupt_mode Mode)
   {
	   switch(Source)
	   {
		   case INTERRUPT0 :
		                     switch(Mode)
							 {
							   case RISINGMODE :
							                      SET_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC00);
												  SET_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC01);
												  break;
							   case FALLINGMODE :
							                      CLEAR_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC00);
							                      SET_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC01);
							                      break;
							   case LOWLEVELMODE :
							                      CLEAR_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC00);
							                      CLEAR_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC01);
							                      break;
							   case EDGETRIG :
							                      SET_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC00);
							                      CLEAR_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC01);
							                      break;
							   default:
							                      break;
							 }
							SET_BIT(REG8_Access(INT_FLAG_CONTROL_REGISTER),INT0_ENABLE_BIT);
							break;
	       case INTERRUPT1 :
		                     switch(Mode)
		                     {
			                     case RISINGMODE :
			                                        SET_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC10);
			                                        SET_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC11);
			                                        break;
			                     case FALLINGMODE :
			                                        CLEAR_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC10);
			                                        SET_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC11);
			                                        break;
			                     case LOWLEVELMODE :
			                                        CLEAR_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC10);
			                                        CLEAR_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC11);
			                                        break;
			                     case EDGETRIG :
			                                        SET_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC10);
			                                        CLEAR_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC11);
			                                        break;
			                     default:
			                                        break;
		                     }
		                     SET_BIT(REG8_Access(INT_FLAG_CONTROL_REGISTER),INT1_ENABLE_BIT);
		                     break;
		   case INTERRUPT2 :
		                       switch(Mode)
							   {
		                                 case RISINGMODE :
		                                                   SET_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC2);
		                                                   break;
		                                 case FALLINGMODE :
		                                                    CLEAR_BIT(REG8_Access(INT_EVENT_CONTROL_REGISTER),ISC2);
		                                                    break;
							             default:
							                                break;
							   }
							   SET_BIT(REG8_Access(INT_FLAG_CONTROL_REGISTER),INT2_ENABLE_BIT);
							   break;
	       default: 
		                       break;
	   }
	   
   }
   void Ex_Interrupt_Disable(interrupt_source Source)
   {
	   switch(Source)
	   {
	       case INTERRUPT0 :
		                    CLEAR_BIT(REG8_Access(INT_FLAG_CONTROL_REGISTER), INT0_ENABLE_BIT);
							break; 
							
		   case INTERRUPT1 :
		                     CLEAR_BIT(REG8_Access(INT_FLAG_CONTROL_REGISTER), INT1_ENABLE_BIT);
		                     break;
		   case INTERRUPT2 :
		                     CLEAR_BIT(REG8_Access(INT_FLAG_CONTROL_REGISTER), INT2_ENABLE_BIT);
		                     break;
	   }
   }
   void Global_Interrupt_Enable(void)
   {
	   SET_BIT(REG8_Access(MCU_STATES_REGISTER), I_BIT);
	   
   }
   void Global_Interrupt_Disable(void)
   {
	   CLEAR_BIT(REG8_Access(MCU_STATES_REGISTER), I_BIT);
   }