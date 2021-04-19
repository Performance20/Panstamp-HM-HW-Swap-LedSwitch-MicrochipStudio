# Panstamp-Swap-LedSwitch-MicrochipStudio

Adaption to compile via MicrochipStudio 7. 
 
 I restructure and adapted the whole code base to have a clear separation between Arduino bibo's and the panstamp and swap code. 
 Beside them, the code is adapted to run on a standard Arduino (Clone) Nano (Atmega328)
 
 Used Pins can be find at panpins.h, which I added as new file to the Panstamp code.
 I used the standard hardware Spi Pins to connect to the CC1101 modul (Mosi, Miso, SS, SCL) + INT0 (PB2) as Interrupt from the CC1101 (GDO0).
 

