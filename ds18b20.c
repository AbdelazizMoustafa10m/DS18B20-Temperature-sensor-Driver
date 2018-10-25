/*
 * ds18b20.c
 *
 * Created: 9/5/2018 3:47:16 AM
 *  Author: Abdelaziz
 */ 

#include "ds18b20.h"

/** 
 *  @file  <ds18b20.c>
 *  @brief <Implements the functions defined in the header file.>
 *
 *  @author<Eng/Abdelaziz Moustafa Abdelazem> 
 *  @date  <5-Sept-18>
 *
 */

   /* Master pulls Data line low*/
   void OneWireBusLow(void)
   {
	   CLEAR_BIT(ONE_WIRE_OUTREG,ONE_WIRE_DQ_PIN);
	   SET_BIT(ONE_WIRE_DIRREG,ONE_WIRE_DQ_PIN);
   }
   /* Releases the data line and the external pull up Resistance makes it HIGH*/
   void OneWireBusFree(void)
   {
	   CLEAR_BIT(ONE_WIRE_DIRREG,ONE_WIRE_DQ_PIN);
   }
   /* Reads the logic data i.e. 0 or 1 present on the DATA line*/
   uint8 OneWireRead(void)
   {
	   return (IS_BIT_SET(ONE_WIRE_INPUTREG,ONE_WIRE_DQ_PIN));
   }
   
   void One_Wire_Write(uint8 byte)
   {
	   uint8 counter = 0;
	   /* Makes the DQ pin Output and Master pulls bus low for sensor presence pulse duration*/
	   for(counter=0;counter<8;counter++)
	   {
		   OneWireBusLow();
		   _delay_us(Slave_wait_time_till_pres_pulse);
		   /* Releasing the Bus if the master wants to write 1 on data line and waits 60us write time slot duration*/
		   if(byte & 0b00000001)
		   {
			   OneWireBusFree();
		   }
		   _delay_us(Write_Timeslot_Duration);
		   OneWireBusFree();
		   _delay_us(Recovery_Time_Delay);
		   byte=byte>>1;
	   }
   }
   
   uint8 One_Wire_Read(void)
   {
	   uint8 byte=0x00;
	   uint8 counter = 0;
	   /* Makes the DQ pin Output and Master pulls bus low for sensor presence pulse duration*/
	   for(counter=0;counter<8;counter++)
	   {
		   byte=byte>>1;
		   OneWireBusLow();
		   _delay_us(Slave_wait_time_till_pres_pulse);
		   /* Release Line after 1us to read from slave*/
		   OneWireBusFree();
		   _delay_us(Waiting_Time_before_Read);
		   /* Start sampling after 15us waiting before reading from sensor */
		   if(ONE_WIRE_INPUTREG &(1<<ONE_WIRE_DQ_PIN))
		   byte|=0b10000000;
		   _delay_us(Read_Timeslot_Duration);
	   }
	   return byte;
   }
   

uint8 DS18B20_Sensor_Reset(void)
{
	/* Master make the DQ pin as an output and then writing low on it for at least 480us to reset pulse*/
	OneWireBusLow();
	_delay_us(Bus_Low_Delay_Time);
    /* Master releases the bus and then wait at least 60us until slave can send a presence response*/
	OneWireBusFree();
	uint8 counter = 0;
	/* Check if Salve is present or not*/
	for(counter=0;counter<40;counter++)
	{
		if(OneWireRead()==0) 
		{
			break;
		}
		_delay_us(Slave_wait_time_till_pres_pulse);
	}
	if(counter==40)
	{
		return	OneWire_NO_ERROR;
	}
	
	for(counter=0;counter<30;counter++)
	{
		if(OneWireRead()==1) break;
		_delay_us(slave_presence_pulse_time);
	}
	return OneWire_COMMUINCATION_ERROR;
	
}

uint8 ds18b20_scratch_pad[9];

uint8 DS18B20_Sesnsor_Configure(Resolution_Select res)
 {
	 /*This Function is used to configure the sensor by selecting  
	   the resolution and number of sensors on bus*/
	 
	 /* Check Communication to know if the sensor is available on the bus or not*/ 
	 DS18B20_Sensor_Reset();
	 
	 /* This line is used to specify that there is only on sensor on the bus*/
	 One_Wire_Write(Skip_ROM);
	 
	 /* This line is used to write Data to the senor*/
	 One_Wire_Write(Write_Data_to_Scratchpad);
	 
	 /* This two lines writes the TH and TL bytes to sensor which are   
	    garbage value because we don't want to write data to the sensor*/ 
	 One_Wire_Write(ds18b20_scratch_pad[2]);
	 One_Wire_Write(ds18b20_scratch_pad[3]);
	 
	 /* This line is used to specify the resolution of the sensor*/
	 One_Wire_Write(res);
	 
	 return DS18B20_OK;
 }



uint8 DS18B20ReadScratchPad(void)
{
	uint8 counter= 0;
	 /* Check Communication to know if the sensor is available on the bus or not*/
	DS18B20_Sensor_Reset();
	/* This line is used to specify that there is only on sensor on the bus*/
	One_Wire_Write(Skip_ROM);
	/* This line is used to read Data to the sensor*/
	One_Wire_Write(Read_Data_From_Scratchpad);
	/* Reads All 8 bytes of the DS18B20 Sensor Scratchpad*/
	for(counter=0;counter<8;counter++)
	{
		ds18b20_scratch_pad[counter]=One_Wire_Read();
	}
	return DS18B20_OK;
}

uint16 DS18B20ReadTemp(Resolution_Select res)
{
	
	uint16 Temperature = 0;
	/* Check Communication to know if the sensor is available on the bus or not*/
	DS18B20_Sensor_Reset();
	/* This line is used to specify that there is only on sensor on the bus*/
	One_Wire_Write(Skip_ROM);
	/* This Line is used to send Temperature conversion request*/
	One_Wire_Write(Convert_Temp);
	/* This Switch Case is used to select the waiting conversion time based on resolution*/
	 switch(res)
	 {
		 case Nine_Bit_Resolution:
		                              _delay_ms(NINE_BIT_RESOLUTION_CONV_TIME);
		                              break;
		 case Ten_Bit_Resolution :
		                              _delay_ms(TEN_BIT_RESOLUTION_CONV_TIME);
		                              break;
		 case Eleven_Bit_Resolution:
		                              _delay_ms(ELVEN_BIT_RESOLUTION_CONV_TIME);
		 break;
		 case Tweleve_Bit_Resolution:
                                   	  _delay_ms(TWELEVE_BIT_RESOLUTION_CONV_TIME);
		                              break;
		 default:
		                              break;
	 }
	 /* This Line reads the Scratchpad of the DS18B20 sensor*/
	 DS18B20ReadScratchPad();
	 /* Takes the first two bytes only from the Scratchpad because temperature is stored in them*/
     Temperature= ( (ds18b20_scratch_pad[1]<<8) + ds18b20_scratch_pad[0] );
	 
	  /* This line is used to convert the temperature value obtained from the sensor Based on the resolution*/
	  switch(res)
	  {
		  case Nine_Bit_Resolution:
	                                    return (Temperature*NINE_BIT_RESOLUTION_FACTOR);
		                                break;
		  case Ten_Bit_Resolution :
		                                return (Temperature*TEN_BIT_RESOLUTION_FACTOR);
		                                break;
		  case Eleven_Bit_Resolution:
		                                return (Temperature*ELVEN_BIT_RESOLUTION_FACTOR);
		                                break;
		  case Tweleve_Bit_Resolution:
                                        return (Temperature*TWELEVE_BIT_RESOLUTION_FACTOR);
		                                break;
		  default:
		                                break;
	  }
	return DS18B20_OK;
	
}