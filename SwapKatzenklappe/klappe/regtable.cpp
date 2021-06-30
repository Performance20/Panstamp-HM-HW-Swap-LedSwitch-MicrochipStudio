/*
 * CPPFile1.cpp
 *
 * Created: 16.02.2021 09:30:42
 *  Author: Helge
 */ 

/**
 * regtable
 *
 * Copyright (c) 2014 panStamp <contact@panstamp.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 01/26/2012
 */

#include "product.h"
#include "regtable.h"
#include "as5600.h"


extern AMS_5600 ams5600;  // position sensor
/**
 * Declaration of custom functions
 */
const void updtProcVoltSupply(byte rId);
const void updtBattVoltSupply(byte rId);

const void updAS5600_AngleValueRaw(byte rId);
const void updAS5600_AngleValueDeg(byte rId);
const void updAS5600_MagnitudeValue(byte rId);
const void updAS5600_MagnetStrengthValue(byte rId);
const void updAS5600_ScaledAngle(byte rId);
const void updAS5600_MaxAngle(byte rId);
const void updAS5600_StartPosition(byte rId);
const void updAS5600_EndPosition(byte rId);
const void updAS5600_i2cAddress(byte rId);
const void updAS5600_AGC(byte rId);

const void setAS5600_MaxAngle(byte rId, byte *state);
const void setAS5600_StartPosition(byte rId, byte *state);
const void setAS5600_EndPosition(byte rId, byte *state);

const void setled0(byte rId, byte *state);
const void setled1(byte rId, byte *state);
const void modulreset(byte rId, byte *state);
const void setSleepIntervall_ms(uint8_t id, uint8_t *interval);
  
  uint16_t getBatteryVoltage(void);
  uint16_t convertRawAngleToDegrees(uint16_t newAngle);

/**
 * Definition of common registers
 */
DEFINE_COMMON_REGISTERS()

/*
 * Definition of custom registers
 */
// Repater config. Not being used by the application. Only kept for backward compatibility
/*
byte dtRepeaterCfg[1];       // Repeater config
REGISTER regRepeaterCfg(dtRepeaterCfg, sizeof(dtRepeaterCfg), NULL, NULL);
// Binary output registers
*/
// Voltage supply
static byte dtProcVoltSupply[2];
REGISTER regProcVoltSupply(dtProcVoltSupply, sizeof(dtProcVoltSupply), &updtProcVoltSupply, NULL);
static byte dtBattVoltSupply[2];
REGISTER regBattVoltSupply(dtBattVoltSupply, sizeof(dtBattVoltSupply), &updtBattVoltSupply, NULL);

extern byte led0[1];       // led0 state
REGISTER regLed0(led0, sizeof(led0), NULL, &setled0);
byte led1[1];       // led1 state
REGISTER regLed1(led1, sizeof(led1), NULL, &setled1);
extern byte rst[1];
REGISTER regReset(rst, sizeof(rst), NULL, &modulreset);

static byte as5600_AngleValueRaw[2];
REGISTER regAS5600_AngleValueRaw(as5600_AngleValueRaw, sizeof(as5600_AngleValueRaw), &updAS5600_AngleValueRaw, NULL);
static byte as5600_AngleValueDeg[2];
REGISTER regAS5600_AngleValueDeg(as5600_AngleValueDeg, sizeof(as5600_AngleValueDeg), &updAS5600_AngleValueDeg, NULL);
static byte as5600_MagnitudeValue[2];  // strengst of the magnet value
REGISTER regAS5600_MagnitudeValue(as5600_MagnitudeValue, sizeof(as5600_MagnitudeValue), &updAS5600_MagnitudeValue, NULL);
static byte as5600_MagnetStrengthValue[2];  // strengst of the magnet value
REGISTER regAS5600_MagnetStrengthValue(as5600_MagnetStrengthValue, sizeof(as5600_MagnetStrengthValue), &updAS5600_MagnetStrengthValue, NULL);
static byte as5600_ScaledAngle[2];  
REGISTER regAS5600_ScaledAngle(as5600_ScaledAngle, sizeof(as5600_ScaledAngle), &updAS5600_ScaledAngle, NULL);

static byte as5600_MaxAngle[2];
REGISTER regAS5600_MaxAngle(as5600_MaxAngle, sizeof(as5600_MaxAngle), &updAS5600_MaxAngle, &setAS5600_MaxAngle);
static byte as5600_StartPosition[2];
REGISTER regAS5600_StartPosition(as5600_StartPosition, sizeof(as5600_StartPosition), &updAS5600_StartPosition, &setAS5600_StartPosition);
static byte as5600_EndPosition[2];
REGISTER regAS5600_EndPosition(as5600_EndPosition, sizeof(as5600_EndPosition), &updAS5600_EndPosition, &setAS5600_EndPosition);

static byte as5600_i2cAddress[1];
REGISTER regAS5600_i2cAddress(as5600_i2cAddress, sizeof(as5600_i2cAddress), &updAS5600_i2cAddress, NULL);
static byte as5600_AGC[1];
REGISTER regAS5600_AGC(as5600_AGC, sizeof(as5600_AGC), &updAS5600_AGC, NULL);
extern uint16_t sleepIntervall;
REGISTER regSleepIntervall_ms((uint8_t*)&sleepIntervall, sizeof(sleepIntervall), NULL, &setSleepIntervall_ms, SWDTYPE_INTEGER, NVOLAT_FIRST_CUSTOM);
extern uint8_t stateCode;	
REGISTER regStateCode(&stateCode, sizeof(stateCode), NULL, NULL);



/**
 * Initialize table of registers
 */
DECLARE_REGISTERS_START()
  &regProcVoltSupply,
  &regBattVoltSupply,
  &regLed0,
  &regLed1,
  &regReset,
  &regAS5600_AngleValueRaw,
  &regAS5600_AngleValueDeg,
  &regAS5600_MagnitudeValue,
  &regAS5600_MagnetStrengthValue,
  &regAS5600_ScaledAngle,
  &regAS5600_MaxAngle,
  &regAS5600_StartPosition,
  &regAS5600_EndPosition,
  &regAS5600_i2cAddress,
  &regAS5600_AGC,
  &regSleepIntervall_ms,
  &regStateCode
DECLARE_REGISTERS_END()

/**
 * Definition of common getter/setter callback functions
 */
DEFINE_COMMON_CALLBACKS()

/**
 * Definition of custom getter/setter callback functions
 */

/**
 * updtVoltSupply
 *
 * Measure voltage supply and update register
 *
 * 'rId'  Register ID
 */
const void updtProcVoltSupply(byte rId)
{  
  uint16_t result = panstamp.getVcc();
  
  // Update register value
  regTable[rId]->value[0] = (result >> 8) & 0xFF;
  regTable[rId]->value[1] = result & 0xFF;
}


/**
 * updtVoltSupply
 *
 * Measure voltage supply and update register
 *
 * 'rId'  Register ID
 */
const void updtBattVoltSupply(byte rId)
{  
  uint16_t result = getBatteryVoltage();
  
  // Update register value
  regTable[rId]->value[0] = (result >> 8) & 0xFF;
  regTable[rId]->value[1] = result & 0xFF;
}

/**
 * updAngleValue
 *
 * read Agc register of as5600  = angle
 *
 * 'rId'  Register ID
 */
const void updAS5600_AngleValueRaw(byte rId)
{
  uint16_t agcValue = ams5600.getRawAngle();
  
  regTable[rId]->value[0] = (agcValue >> 8) & 0xFF;
  regTable[rId]->value[1] = agcValue & 0xFF;
}

/**
 * updAngleValue
 *
 * read Agc register of as5600  = angle
 *
 * 'rId'  Register ID
 */
const void updAS5600_AngleValueDeg(byte rId)
{
  uint16_t agcValue = convertRawAngleToDegrees(ams5600.getRawAngle());
  
  regTable[rId]->value[0] = (agcValue >> 8) & 0xFF;
  regTable[rId]->value[1] = agcValue & 0xFF;
}

/**
 * updAS5600_MagnitudeValue
 *
 * read magnitude register of as5600
 *
 * 'rId'  Register ID
 */
const void updAS5600_MagnitudeValue(byte rId)
{
  uint16_t agcValue  = ams5600.getMagnitude();
  
  regTable[rId]->value[0] = (agcValue >> 8) & 0xFF;
  regTable[rId]->value[1] = agcValue & 0xFF;
}

/**
 * updAS5600_MagnetStrengthValue
 *
 * read magnet strength register of as5600
 *  Out: 0 if no magnet is detected
 *	1 if magnet is to weak
 *	2 if magnet is just right
 *	3 if magnet is to strong 
 *
 * 'rId'  Register ID
 */
const void updAS5600_MagnetStrengthValue(byte rId)
{
  uint16_t agcValue  = ams5600.getMagnetStrength();
  
  regTable[rId]->value[0] = (agcValue >> 8) & 0xFF;
  regTable[rId]->value[1] = agcValue & 0xFF;
}

/**
  updAS5600_ScaledAngle
 
  read as5600 value of scaled angle register
  Description: gets scaled value of magnet position.
  start, end, or max angle settings are used to 
  determine value
 */

const void updAS5600_ScaledAngle(byte rId)
{
	uint16_t agcValue  = ams5600.getScaledAngle();
	
	regTable[rId]->value[0] = (agcValue >> 8) & 0xFF;
	regTable[rId]->value[1] = agcValue & 0xFF;
}

/**
  updAS5600_getMaxAngle
 
  read as5600 value of max angle register
 */

const void updAS5600_MaxAngle(byte rId)
{
	uint16_t agcValue  = ams5600.getMaxAngle();
	
	regTable[rId]->value[0] = (agcValue >> 8) & 0xFF;
	regTable[rId]->value[1] = agcValue & 0xFF;
}

const void setAS5600_MaxAngle(byte rId, byte *state)
{
	uint16_t newValue;  
	
	newValue = ((uint16_t) state[1] * 256) + (uint16_t) state[0];
	ams5600.setMaxAngle(newValue);
}

/**
  updAS5600_getStartPosition
 
  read as5600 value of max angle register
 */

const void updAS5600_StartPosition(byte rId)
{
	uint16_t agcValue  = ams5600.getStartPosition();
	
	regTable[rId]->value[0] = (agcValue >> 8) & 0xFF;
	regTable[rId]->value[1] = agcValue & 0xFF;
}

const void setAS5600_StartPosition(byte rId, byte *state)
{
	uint16_t newValue;
		
	newValue = ((uint16_t) state[1] * 256) + (uint16_t) state[0];
	ams5600.setStartPosition(newValue);
}

/**
  updAS5600_getEndPosition
 
  read as5600 value of max angle register
 */

const void updAS5600_EndPosition(byte rId)
{
	uint16_t agcValue  = ams5600.getEndPosition();
	
	regTable[rId]->value[0] = (agcValue >> 8) & 0xFF;
	regTable[rId]->value[1] = agcValue & 0xFF;
}

const void setAS5600_EndPosition(byte rId, byte *state)
{
	uint16_t newValue;
	
	newValue = ((uint16_t) state[1] * 256) + (uint16_t) state[0];
	ams5600.setEndPosition(newValue);	
}

/**
  updAS5600_i2cAddress
 
  read as5600 I2C address
 */

const void updAS5600_i2cAddress(byte rId)
{
	regTable[rId]->value[0]  = ams5600.getAddress();
}

/**
  updAS5600_AGC register
 */

const void updAS5600_AGC(byte rId)
{
	regTable[rId]->value[0]  = ams5600.getAgc();
}

/**
 * setled0
 *
 * Set setled0 output
 *
 */
const void setled0(byte rId, byte *state)
{
    // Update register
	
   led0[0] = state[0];
   if (led0[0] == 0)
		digitalWrite(LED, LOW);
   else
		digitalWrite(LED, HIGH);
		
}

/**
 * setled1
 *
 * Set setled1 output
 *
 */
const void setled1(byte rId, byte *state)
{
    // Update register
  regTable[rId]->value[0] = state[0];
}


const void modulreset(byte rId, byte *state)
{
	if (state[0] == 1)
	{
		swap.enterSystemState(SYSTATE_RXOFF);
		rst[0] = state[0];
		panstamp.reset();
	}
}

const void setSleepIntervall_ms(uint8_t id, uint8_t *interval)  
{                                                                     
	regSleepIntervall_ms.setValueFromBeBuffer(interval);             
}


/*
*  Battery measurement functions stolen from asksin++
*/

#define BAT_NUM_MESS_ADC       10
#define AVR_BANDGAP_VOLTAGE    3080L

/**
 * get the voltage off battery
 */
uint16_t  getBatteryVoltage(void) {
	
	uint32_t adcValue = 0;
	
	pinMode(BATT_MEASURE_PIN, INPUT);						// set the ADC pin as input
	
	pinMode(BATT_ENABLE_PIN, OUTPUT);						// set pin as out put
	digitalWrite(BATT_ENABLE_PIN, LOW);						// activate network 			
	  
	analogReference(EXTERNAL); // pin is connected to VCC
	for (int i=0; i<BAT_NUM_MESS_ADC; i++)
	{
	  adcValue += analogRead(BATT_MEASURE_PIN);
	  delay(2);
	}	  
	adcValue /= BAT_NUM_MESS_ADC;
	
	pinMode(BATT_ENABLE_PIN, INPUT_PULLUP);  
	digitalWrite(BATT_MEASURE_PIN, HIGH);
	
	return (adcValue * AVR_BANDGAP_VOLTAGE * 57) / 10240;  // R1=470k, R2=100k	 
}


/*******************************************************
/* Function: convertRawAngleToDegrees
/* In: angle data from AMS_5600::getRawAngle
/* Out: human readable degrees as unsigned int
/* Description: takes the raw angle and calculates
/* float value in degrees.
/*******************************************************/

uint16_t convertRawAngleToDegrees(uint16_t newAngle)
{
/* Raw data reports 0 - 4095 segments, which is 0.087 of a degree */
  return ((newAngle * 0.087) + 0.5); // round to a full degree
}
