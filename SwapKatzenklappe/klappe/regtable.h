/**
 * regtable.h
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

#ifndef _REGTABLE_H
#define _REGTABLE_H

#include "register.h"
#include "commonregs.h"


/**
 * Register indexes
 */
DEFINE_REGINDEX_START()
 REGI_PROCVOLTSUPPLY,
 REGI_BATTVOLTSUPPLY,
 REGI_LED0,
 REGI_LED1,
 CMD_RESET,
 REGI_AS5600_ANGLERAW,
 REGI_AS5600_ANGLEDEG,
 REGI_AS5600_MAGNITUTE,
 REGI_AS5600_MAGNETSTRENGTH,
 REGI_AS5600_SCALEDANGLE,
 REGI_AS5600_MAXANGLE,
 REGI_AS5600_STARTPOSTION,
 REGI_AS5600_ENDPOSTION,
 REGI_AS5600_I2CADDRESS,
 REGI_S5600_AGC,
 REGI_SLEEP_MS,
 REGI_STATECODE
DEFINE_REGINDEX_END()

#endif
