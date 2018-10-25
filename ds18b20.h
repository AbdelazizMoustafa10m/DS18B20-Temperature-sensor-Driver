/*
 * ds18b20.h
 *
 * Created: 9/5/2018 3:45:03 AM
 *  Author: Abdelaziz
 */ 


#ifndef DS18B20_H_
#define DS18B20_H_

    #include "Micro_Config.h"
    #include "MACROS.h"
    #include "STD TYPES.h"
	
/** 
 *  @file  <ds18b20.h>
 *  @brief <Header File of The DS18B20 temperature sensor library.>
 *         <It contains The Prototypes of all function available in
 *          the library,definitions of all Macros, and Enumerations> 
 *
 *  @author<Eng/Abdelaziz Moustafa Abdelazem> 
 *  @date  <5-Sept-18>
 *
 */
	
	/* Hardware Connection for the sensor*/
	#define ONE_WIRE_OUTREG    (REG8_Access(PORTC_OUTPUTREG))
	#define ONE_WIRE_DIRREG    (REG8_Access(PORTC_DIRREG))
	#define ONE_WIRE_INPUTREG  (REG8_Access(PORTC_INPUTREG))
	#define ONE_WIRE_DQ_PIN	               PC3

	/* These Macros are the delay time in us needed in the initialization process*/
	#define Bus_Low_Delay_Time              (500)
	#define Slave_wait_time_till_pres_pulse (2)
	#define slave_presence_pulse_time       (10)
	/*These Macros are the delay time in us needed in the read/write process*/
	#define Recovery_Time_Delay             (1)
	#define Waiting_Time_before_Read        (15)
	#define Write_Timeslot_Duration         (70)
	#define waiting_Time_before_Write       (15)
	#define Read_Timeslot_Duration          (60)
	#define Master_Write_Zero_Duration      (45)
	#define Master_Read_One_Duration        (45)
    /* These Macros are the response of the slave when initiating the bus*/
	#define OneWire_NO_ERROR                (0)
	#define OneWire_COMMUINCATION_ERROR     (1)
    /* These Macros are the response of the sensor when trying to Read/write data*/
    #define DS18B20_COMMUNICATION_ERROR     (1)
    #define DS18B20_OK                      (0)
    
    /* This Macros Define the conversion time in ms for each conversion resolution*/
    #define NINE_BIT_RESOLUTION_CONV_TIME    (94)
    #define TEN_BIT_RESOLUTION_CONV_TIME     (188)
    #define ELVEN_BIT_RESOLUTION_CONV_TIME   (375)
    #define TWELEVE_BIT_RESOLUTION_CONV_TIME (750)
    
    /* This Macros Define The factor in °C for each conversion resolution*/
    #define NINE_BIT_RESOLUTION_FACTOR    (0.5)
    #define TEN_BIT_RESOLUTION_FACTOR     (0.25)
    #define ELVEN_BIT_RESOLUTION_FACTOR   (0.125)
    #define TWELEVE_BIT_RESOLUTION_FACTOR (0.0625)
	
    /* This Enumeration defines the commands sent to the ROM of the sensor to Initiate communication*/
    typedef enum {Search_ROM = 0xF0, Read_ROM = 0x33, Match_ROM = 0x55,
	    Skip_ROM = 0xCC, Alarm_Search = 0xEC
    }ROM_Command;
    
	/* This Enumeration defines the commands sent to the sensor to Initiate any process*/
    typedef enum {Convert_Temp = 0x44, Write_Data_to_Scratchpad = 0x4E, Read_Data_From_Scratchpad = 0xBE,
	    Copy_Scratchpad_to_EEPROM = 0x48, Recall_Data_from_EEPROM = 0xB8, Read_Power_Supply = 0xB4
    }DS18B20_Functin_Cmd;
    
	/* This Enumeration defines the different resolutions that the sensor can be configured with*/
    typedef enum {Nine_Bit_Resolution = 0x1F, Ten_Bit_Resolution = 0x3F, Eleven_Bit_Resolution = 0x5F,
	    Tweleve_Bit_Resolution = 0x7F
    }Resolution_Select;

    /** 
	 *  @brief <void OneWireBusLow(void)>
	 *  <This Function intiates commuincation with one wire protocol by the master pulling bus low>
	 *
	 *  @param <void>
	 *
	 *  @return <function return is void>
	 *
	 */
    void OneWireBusLow(void);
	
	/** 
	 *  @brief <void OneWireBusFree(void)>
	 *  <This Function intiates commuincation with one wire protocol by the master floating the bus>
	 *
	 *  @param <void>
	 *
	 *  @return <function return is void>
	 *
	 */
    void OneWireBusFree(void);
	
	/** 
	 *  @brief <uint8 OneWireRead(void)>
	 *  <This Function reads the logic data on the bus i.e. 0 or 1 to know if the slave is present on bus>
	 *
	 *  @param <void>
	 *
	 *  @return <uint8 returns 0 for DS18B20 Prescence on the bus, 1 for non prescence.>
	 *
	 */
    uint8 OneWireRead(void);
	
	/** 
	 *  @brief <void One_Wire_Write(uint8 byte)>
	 *  <This Function sends one byte via 1-Wire interface to the DS18B20 sensor>
	 *
	 *  @param uint8 <byte> <a byte value to be sent to the DS18B20 sensor via 1-wire interface>
	 *
	 *  @return <function return is void>
	 *
	 */
    void One_Wire_Write(uint8 byte);
	
	/** 
	 *  @brief <uint8 One_Wire_Read(void)>
	 *  <This Function reads a byte from the sensor via 1-Wire interface.>
	 *
	 *  @param <void>
	 *
	 *  @return <uint8 returns byte read from the DS18B20 Sensor via 1-Wire interface.>
	 *
	 */
    uint8 One_Wire_Read(void);
	
	/** 
	 *  @brief <uint8 DS18B20_Sensor_Reset(void)>
	 *  <This Function Used The function prepares the 1-Wire bus and 
	 *   initialization of the DS18B20 sensor before data exchange.>
	 *
	 *  @param <void>
	 *
	 *  @return <uint8 returns 0 for success, 1 for failed initialization attempt.>
	 *
	 */
    uint8 DS18B20_Sensor_Reset(void);
	
	/** 
	 *  @brief <uint8 DS18B20_Sesnsor_Configure(Resolution_Select res)>
	 *  <This Function Used for configuring the resolution of the sensor.>
	 *
	 *  @param Resolution_Select <res> <different resolution from Resolution_Select Enumeration. >
	 *
	 *  @return <uint8 returns 0 for success, 1 for failed configuring attempt.>
	 *
	 */
	uint8 DS18B20_Sesnsor_Configure(Resolution_Select res);
	
	/** 
	 *  @brief <uint8 DS18B20ReadScratchPad(void)>
	 *  <This Function reads the contents of DS18B20 scratchpad.>
	 *
	 *  @param <void>
	 *
	 *  @return <uint8 returns 0 if CRC error is detected, 1 for successful scratchpad read.>
	 *
	 */
    uint8 DS18B20ReadScratchPad(void);
	
	/** 
	 *  @brief <uint16 DS18B20ReadTemp(Resolution_Select res)>
	 *  <This functions initiates a temperature conversion via CONVERT_T function command
	 *   and then issues READ_SCRATCHPAD command for fetching the temperature reading.>
	 *
	 *  @param Resolution_Select <res> <different resolution from Resolution_Select Enumeration. >
	 *
	 *  @return <uint16 returns Temperature measured by the sensor based on the resolution of conversion.>
	 *
	 */
    uint16 DS18B20ReadTemp(Resolution_Select res);

#endif /* DS18B20_H_ */