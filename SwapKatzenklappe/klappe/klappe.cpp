/*
 
 */

#include <avr/wdt.h> 
#include "Wire.h"
#include "regtable.h"
#include "swap.h"
#include "as5600.h"


#define SERIAL_SPEED             9600
byte led0[1] = { 0 };	 	// led1 state
byte rst[1] = { 0 };
uint16_t sleepIntervall = 250;	

#define SEND_STATE_MSG				5 //43.200 // if in loops, send all 12h a message

#define STATE_INIT					0
#define STATE_DETECT_SENSOR_I2C		STATE_INIT + 1
#define STATE_MAGNET_DETECT			STATE_DETECT_SENSOR_I2C + 1
#define STATE_MAIN_LOOP   			STATE_MAGNET_DETECT + 1

uint8_t stateCode = STATE_INIT;	

AMS_5600 ams5600;  // position sensor

extern uint16_t getBatteryVoltage(void);
extern uint16_t convertRawAngleToDegrees(uint16_t newAngle);

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
  
  Serial.begin(SERIAL_SPEED);
  // Init SWAP stack
  swap.init();
 
  // Enter SYNC state
  swap.enterSystemState(SYSTATE_SYNC);
   //swap.enterSystemState(SYSTATE_RXON);
      
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
  // Transmit all standartd register
  for (rgc=0; rgc<=REGI_TXINTERVAL; rgc++)
  swap.getRegister(rgc)->getData();

  // Transmit initial custom register 
  for (rgc=REGI_PROCVOLTSUPPLY; rgc<=REGI_STATECODE; rgc++)
	  swap.getRegister(rgc)->getData();
	  
  // attach Hall postion sensor	  
  stateCode = STATE_DETECT_SENSOR_I2C;
  swap.getRegister(REGI_STATECODE)->getData();
  Wire.begin();  
  if(ams5600.detectMagnet() == 0 ){
	  while(1){
		  if(ams5600.detectMagnet() == 1 ){
			  Serial.print("Current Magnitude: ");
			  Serial.println(ams5600.getMagnitude());
			  stateCode = STATE_MAIN_LOOP;
			  swap.getRegister(REGI_STATECODE)->getData();
			  break;
		  }
		  else{
			  Serial.println("Can not detect magnet");
			  stateCode = STATE_MAGNET_DETECT;
			  swap.getRegister(REGI_STATECODE)->getData();
		  }
		  delay(1000);
	  }
  }
  
  Serial.println("Modul ready!");
}

/**
 * loop
 *
 * Arduino main loop
 */

void loop()
{
  uint16_t msgcnt = 0;
  
   // Sleep
  swap.goToSleepMS(sleepIntervall);
  // receive possible set commands
  swap.enterSystemState(SYSTATE_SYNC); 
  
  if (!(msgcnt % SEND_STATE_MSG))  {
	msgcnt++;
	swap.getRegister(REGI_PROCVOLTSUPPLY)->getData();  
	swap.getRegister(REGI_BATTVOLTSUPPLY)->getData();
  }
  
  swap.getRegister(REGI_AS5600_ANGLEDEG)->getData();
  swap.getRegister(REGI_AS5600_MAGNETSTRENGTH)->getData();
  
  Serial.print("Current Magnitude: ");
  Serial.print(ams5600.getMagnitude());
  Serial.print("  Current Magnet Strength: ");
  Serial.print(ams5600.getMagnetStrength());
  Serial.print("  Grad: ");
  Serial.println(String(convertRawAngleToDegrees(ams5600.getRawAngle()),DEC));

  delay(500);
}
