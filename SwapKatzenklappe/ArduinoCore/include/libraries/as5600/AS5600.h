
/****************************************************
  AMS 5600 class for Arduino platform
  Author: Tom Denton
  Date: 15 Dec 2014
  File: AMS_5600.h 
  Version 1.00
  www.ams.com
   
  Description:  This class has been designed to
  access the AMS 5600 “potuino” shield.
***************************************************/

#ifndef AMS_5600_h
#define AMS_5600_h

#include <Arduino.h>

class AMS_5600
{
public:
  AMS_5600(void);
  
  enum {
	  POWER_MODE_NORM = 0,
	  POWER_MODE_LPM1 = 1,
	  POWER_MODE_LPM2 = 2,
	  POWER_MODE_LPM3 = 3,

	  HYSTERESIS_OFF = 0,
	  HYSTERESIS_1LSB = 1,
	  HYSTERESIS_2LSB = 2,
	  HYSTERESIS_3LSB = 3,

	  OUTPUT_STAGE_ANALOG_FULL = 0,
	  OUTPUT_STAGE_ANALOG_REDUCED = 1,
	  OUTPUT_STAGE_DIGITAL_PWM = 2,

	  SLOW_FILTER_16X = 0,
	  SLOW_FILTER_8X = 1,
	  SLOW_FILTER_4X = 2,
	  SLOW_FILTER_2X = 3,

	  FAST_FILTER_THRESHOLD_SLOW = 0,
	  FAST_FILTER_THRESHOLD_6LSB = 1,
	  FAST_FILTER_THRESHOLD_7LSB = 2,
	  FAST_FILTER_THRESHOLD_9LSB = 3,
	  FAST_FILTER_THRESHOLD_18LSB = 4,
	  FAST_FILTER_THRESHOLD_21LSB = 5,
	  FAST_FILTER_THRESHOLD_24LSB = 6,
	  FAST_FILTER_THRESHOLD_10LSB = 7,

  };
  
  int getAddress();

  word setMaxAngle(word newMaxAngle = -1);
  word getMaxAngle();

  word setStartPosition(word startAngle = -1);
  word getStartPosition();

  word setEndPosition(word endAngle = -1);
  word getEndPosition();

  word getRawAngle();
  word getScaledAngle();

  int detectMagnet();
  int getMagnetStrength();
  int getAgc();
  word getMagnitude();

  int getBurnCount();
  int burnAngle();
  int burnMaxAngleAndConfig();
  void setOutPut(uint8_t mode);

  bool setPowerMode(uint8_t powerMode);
  uint8_t getCONF();

private:
  int _ams5600_Address;

  word _rawStartAngle;
  word _zPosition;
  word _rawEndAngle;
  word _mPosition;
  word _maxAngle;

  /* Registers */
  int _zmco;
  int _zpos_hi; /*zpos[11:8] high nibble  START POSITION */
  int _zpos_lo; /*zpos[7:0] */
  int _mpos_hi; /*mpos[11:8] high nibble  STOP POSITION */
  int _mpos_lo; /*mpos[7:0] */
  int _mang_hi; /*mang[11:8] high nibble  MAXIMUM ANGLE */
  int _mang_lo; /*mang[7:0] */
  int _conf_hi;
  int _conf_lo;
  int _raw_ang_hi;
  int _raw_ang_lo;
  int _ang_hi;
  int _ang_lo;
  int _stat;
  int _agc;
  int _mag_hi;
  int _mag_lo;
  int _burn;

  int readOneByte(int in_adr);
  word readTwoBytes(int in_adr_hi, int in_adr_lo);
  void writeOneByte(int adr_in, int dat_in);
};
#endif