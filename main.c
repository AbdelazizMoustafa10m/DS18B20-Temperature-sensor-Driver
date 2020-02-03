/*
 * ONE_WIRE_Driver.c
 *
 * Created: 9/6/2018 12:35:03 AM
 * Author : Abdelaziz
 */ 

#include "ds18b20.h"
#include "LCD.h"
#include "Interrupt_Driver_ATMEGA32.h"

/**
*  @file  <ONE_WIRE_Driver.c>
*  @brief <Implements the Ds18b20 Libarary to measure temperature.>
*
*  @author<Eng/Abdelaziz Moustafa Abdelazem>
*  @date  <6-Sept-18>
*
*/

int main()
{
	uint8 Temp = 0;
	
	LCD_init();
	/* Configuring the DS18B20 sensor by selecting 12-Bit conversion Resolution*/
	DS18B20_Sesnsor_Configure(Tweleve_Bit_Resolution);
	
	
	while(1)
	{
		LCD_Select_RowCol(0,3);
		LCD_DisplayString("DS18B20 SENSOR");
		/* Read Sensor measuring*/
		Temp = DS18B20ReadTemp(Tweleve_Bit_Resolution);
		LCD_Select_RowCol(1,0);
		LCD_DisplayString("Temperature = ");
		LCD_DisplayInt(Temp);
		
	}

}


  
