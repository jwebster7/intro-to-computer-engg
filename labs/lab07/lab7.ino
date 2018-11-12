#include <SPI.h>
int local;
unsigned long secondTimer;
float Temperature;
float ThermoCouple;

// function to read temperature from Max6675
float Read_SPI_Temperature(){
  //set up the SPI
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  //set the chip select low
  PORTC &= ~0x04;
  int TempData = SPI.transfer16(0);
  PORTC |= 0x04;
  SPI.endTransaction();
  TempData = (TempData / 8 ) & 0x0fff;
  Temperature = 0.25 * (float) TempData;
  Temperature = 1.8*Temperature + 32.0;
  return Temperature;
} // end of Read_SPI_Temperature

void setup() {
 //Setup Chip Select Pin and set as inactive.
 pinMode( A2, OUTPUT);
 digitalWrite( A2, HIGH );

 //initialize SPI:
 SPI.begin();
 SPI.setClockDivider( SPI_CLOCK_DIV2 );
 SPI.setBitOrder( MSBFIRST );
 SPI.setDataMode(SPI_MODE0);

 //setup serial port
 Serial.begin( 9600);

 //prepare timer.
 secondTimer = millis();
}

void loop() {
 
  if( millis() - secondTimer >= 1000 ){
    // Read Temperature sensor
    ThermoCouple = Read_SPI_Temperature( );
    
    secondTimer += 1000;

    //report data
    Serial.print( "Temp = ");
    Serial.println( ThermoCouple );
  }
}


