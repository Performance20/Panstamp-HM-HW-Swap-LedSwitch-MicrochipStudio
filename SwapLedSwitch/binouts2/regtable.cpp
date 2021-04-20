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


/**
 * Declaration of custom functions
 */
const void updtProcVoltSupply(byte rId);
const void updtBattVoltSupply(byte rId);
const void setled0(byte rId, byte *state);
const void setled1(byte rId, byte *state);

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
byte led0[1];       // led0 state
REGISTER regLed0(led0, sizeof(led0), NULL, &setled0);
byte led1[1];       // led1 state
REGISTER regLed1(led1, sizeof(led1), NULL, &setled1);


/**
 * Initialize table of registers
 */
DECLARE_REGISTERS_START()
  &regProcVoltSupply,
  &regBattVoltSupply,
  &regLed0,
  &regLed1
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
  unsigned long result = panstamp.getVcc();
  
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
  unsigned long result = panstamp.getVcc();
  
  // Update register value
  regTable[rId]->value[0] = (result >> 8) & 0xFF;
  regTable[rId]->value[1] = result & 0xFF;
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
	
   regTable[rId]->value[0] = state[0];
   if (led0[0] == 0)
		digitalWrite(LED, LOW);
   else
		digitalWrite(LED, HIGH);
		
}

/**
 * setled0
 *
 * Set setled0 output
 *
 */
const void setled1(byte rId, byte *state)
{
    // Update register
  regTable[rId]->value[0] = state[0];
}
