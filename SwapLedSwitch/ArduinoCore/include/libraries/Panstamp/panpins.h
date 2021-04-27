/*
 * panpins.h
 *
 * Created: 23.02.2021 10:38:38
 *  Author: Helge
 */ 


#ifndef PANPINS_H_
#define PANPINS_H_

// SPI CC1101 interface
//#define CC1101_SPI_SS   SS      // PB2 = SPI_SS
//#define CC1101_GDO0	    (2)      // PD2 = INT0

// Arduino values
#define SPI_SS			SS				// PB2 = SPI_SS
#define SPI_MOSI		MOSI            // PB3 = MOSI
#define SPI_MISO		MISO            // PB4 = MISO
#define SPI_SCK			SCK             // PB5 = SCK
#define GDO0			(2)			    // PD2 = INT0

// register direct access caused by speed reasons
#define PORT_SPI_MISO  PINB
#define BIT_SPI_MISO  4

#define PORT_SPI_SS  PORTB
#define BIT_SPI_SS   2

#define PORT_GDO0  PIND
#define BIT_GDO0  2

// On-board LED
#define ONBOARD_LED (4)  // PD4
#define LED      ONBOARD_LED
#define INIT_ONBOARD_LED()    pinMode(ONBOARD_LED, OUTPUT)

#define BATT_MEASURE_PIN       A3
#define BATT_ENABLE_PIN        7

#endif /* PANPINS_H_ */