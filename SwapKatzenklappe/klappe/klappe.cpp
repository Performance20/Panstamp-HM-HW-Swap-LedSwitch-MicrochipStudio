/*
 
 */

#include <avr/wdt.h> 
#include <avr/pgmspace.h>
#include "Wire.h"
#include "regtable.h"
#include "swap.h"
#include "as5600.h"

//#define USE_SERIAL_DEBUG
#define SERIAL_SPEED             9600

byte led0[1] = { 0 };	 	// led1 state
byte led1[1] = { 10 };	 	// led1 state
byte rst[1] = { 0 };
uint16_t as5600_AngleValueDegActual = 0;
uint8_t as5600_MagnetStrengthValue = 0;
uint16_t oldAngleValue = 0;
#define SLEEP_TIME        250
uint16_t sleepIntervall = SLEEP_TIME;	// value 125 or 250 or 500 ms
#define SEND_STATE_MSG		(1000 / SLEEP_TIME)	* swap.txInterval //if in loops, send all 4h a message
uint8_t res;
uint32_t msgcnt = 0;

#define STATE_INIT					0
#define STATE_DETECT_SENSOR_I2C		STATE_INIT + 1
#define STATE_MAGNET_DETECT			STATE_DETECT_SENSOR_I2C + 1
#define STATE_MAIN_LOOP   			STATE_MAGNET_DETECT + 1

uint8_t stateCode = STATE_INIT;	

AMS_5600 ams5600;  // position sensor

extern uint16_t getBatteryVoltage(void);
extern uint16_t convertRawAngleToDegrees(uint16_t newAngle);
extern const void updAS5600_AngleValueDeg(byte rId);
extern const void updAS5600_MagnetStrengthValue(byte rId);


/**
 * setup
 *
 * Arduino setup function
 */
void setup()
{
  uint8_t i;
  uint8_t rgc;

  //stateCode = STATE_INIT;	
  INIT_ONBOARD_LED();
  digitalWrite(LED, HIGH);
#ifdef  USE_SERIAL_DEBUG
  Serial.begin(SERIAL_SPEED);
  while(!Serial);
  Serial.println(F("Modul Start!"));
#endif

  // Init SWAP stack
  swap.init();
 
  // Enter SYNC state
  swap.enterSystemState(SYSTATE_SYNC);
// During 3 seconds, listen the network for possible commands whilst the LED blinks
  for(i=0 ; i<6 ; i++)
  {
	digitalWrite(LED, HIGH);
	delay(50);
	digitalWrite(LED, LOW);
	delay(450);
  }
  // Optionally set transmission amplifier to its maximum level (10dB)
  //panstamp.setHighTxPower();
  // Transmit all standard register
  for (rgc=0; rgc<=REGI_TXINTERVAL; rgc++)
   swap.getRegister(rgc)->getData();
  // Transmit initial custom register 
  //for (rgc=REGI_PROCVOLTSUPPLY; rgc<=REGI_STATECODE; rgc++)
	 // swap.getRegister(rgc)->getData();
  swap.getRegister(REGI_PROCVOLTSUPPLY)->getData();
  swap.getRegister(REGI_BATTVOLTSUPPLY)->getData();
  swap.getRegister(REGI_SLEEP_MS)->getData(); 
  swap.getRegister(REGI_LED1)->getData();    
  // attach Hall position sensor	  
  stateCode = STATE_DETECT_SENSOR_I2C;
  swap.getRegister(REGI_STATECODE)->getData();
  Wire.begin();  
  if(ams5600.detectMagnet() == 0 ){
	  while(1){
		  if(ams5600.detectMagnet() == 1 ) {
			  stateCode = STATE_MAIN_LOOP;
			  swap.getRegister(REGI_STATECODE)->getData();
			  break;
		  }
		  else {
#ifdef  USE_SERIAL_DEBUG			  
			  Serial.println(F("Can not detect magnet"));
#endif
			  stateCode = STATE_MAGNET_DETECT;
			  swap.getRegister(REGI_STATECODE)->getData();
		  }
		  delay(1000);
	  }
  }
  swap.getRegister(REGI_AS5600_ANGLEDEG)->getData();
  swap.getRegister(REGI_AS5600_MAGNETSTRENGTH)->getData();
  res = ams5600.setPowerMode(ams5600.POWER_MODE_LPM3);
#ifdef  USE_SERIAL_DEBUG    
  if (res == true)
	Serial.println(F("Set Powermode to LPM3 = 100ms"));
  Serial.println(F("Modul ready!"));
#endif
}

/**
 * loop
 *
 * Arduino main loop
 */

void loop()
{
	int16_t agcDiff;
	
	updAS5600_MagnetStrengthValue(0);
	if ((as5600_MagnetStrengthValue >=1) && (as5600_MagnetStrengthValue <=3))
	{ // MAGNET IS AVAILABLE; DO NORMAL WORK
		// receive possible set commands
		if (msgcnt == 0)  {
			msgcnt = SEND_STATE_MSG;
			swap.enterSystemState(SYSTATE_RXON);  
			swap.getRegister(REGI_PROCVOLTSUPPLY)->getData(); 
			swap.getRegister(REGI_BATTVOLTSUPPLY)->getData();
			swap.getRegister(REGI_AS5600_ANGLEDEG)->getData();
			swap.getRegister(REGI_AS5600_MAGNETSTRENGTH)->getData();
#ifdef  USE_SERIAL_DEBUG
			Serial.print(F("Magnet Strength: "));
			Serial.print(as5600_MagnetStrengthValue);
			Serial.print(F("  Grad: "));
			Serial.println(String(as5600_AngleValueDegActual,DEC));
#endif
			swap.enterSystemState(SYSTATE_SYNC); 
 			delay(1000); // wait for receive mesg
			swap.enterSystemState(SYSTATE_RXOFF);
			delay(500);
		}
		msgcnt--;	
		updAS5600_AngleValueDeg(0);
		agcDiff = as5600_AngleValueDegActual - oldAngleValue;
		if ((agcDiff < (led1[0] * -1)) || (agcDiff > led1[0]))  // there is really a change and not only a noise
		{
		  swap.enterSystemState(SYSTATE_RXON);  
		  swap.getRegister(REGI_AS5600_ANGLEDEG)->getData();
		  oldAngleValue = as5600_AngleValueDegActual;
		  swap.enterSystemState(SYSTATE_SYNC); 
		  delay(100);
		  swap.enterSystemState(SYSTATE_RXOFF);
#ifdef  USE_SERIAL_DEBUG
		  Serial.print(F("Send Grad: "));
		  Serial.println(String(as5600_AngleValueDegActual,DEC));
		  delay(100);
#endif
		}
		// Sleep
		swap.goToSleepMS(sleepIntervall);		
	}
	else
	{
	 	swap.getRegister(REGI_AS5600_MAGNETSTRENGTH)->getData();
#ifdef  USE_SERIAL_DEBUG		 
		Serial.print(F("Magnet Strength: "));
		Serial.println(as5600_MagnetStrengthValue);
	    delay(500);
#endif		
		swap.goToSleep();
	}
}
