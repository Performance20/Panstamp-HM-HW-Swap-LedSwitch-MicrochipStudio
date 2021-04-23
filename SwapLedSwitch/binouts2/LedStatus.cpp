/*
 
 */
 
#include "regtable.h"
#include "swap.h"

#define SERIAL_SPEED             9600

/**
 * setup
 *
 * Arduino setup function
 */
void setup()
{
  int i;
  
  INIT_ONBOARD_LED();
  digitalWrite(LED, HIGH);
  
  
  
  Serial.begin(SERIAL_SPEED);
  
  // Init SWAP stack
  swap.init();
  // Optionally set transmission amplifier to its maximum level (10dB)
  panstamp.setHighTxPower();
  
  // Transmit product code
  swap.getRegister(REGI_PRODUCTCODE)->getData();
  swap.getRegister(REGI_TXINTERVAL)->getData();
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
  swap.getRegister(REGI_TXINTERVAL)->getData();

  // Transmit initial custom register
  swap.getRegister(REGI_PROCVOLTSUPPLY)->getData();
  swap.getRegister(REGI_BATTVOLTSUPPLY)->getData();
  swap.getRegister(REGI_LED0)->getData();
  swap.getRegister(REGI_LED1)->getData();
  
  swap.enterSystemState(SYSTATE_RXOFF);
  
  Serial.println("Modul ready!");
}

/**
 * loop
 *
 * Arduino main loop
 */
extern uint16_t getBatteryVoltage(void);
void loop()
{
  int i;

   // Sleep
  swap.goToSleep();
   
  // receive possible set commands
 
  // update Processor Voltage
  swap.getRegister(REGI_PROCVOLTSUPPLY)->getData();
  // update Batterie Voltage
  swap.getRegister(REGI_BATTVOLTSUPPLY)->getData();

   delay(1000);
   swap.enterSystemState(SYSTATE_SYNC);
 // 
}
