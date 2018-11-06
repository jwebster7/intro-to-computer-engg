
#include <LiquidCrystal.h>
// Define LCD
LiquidCrystal LcdDriver(11, 9, 5, 6, 7, 8 );

// Setup clock
#include "ClockBasics.h"
#define CLOCK_INTERVAL 1000
unsigned long ClockTimer;

// Setup GPS variables.
float Latitude = 0.0, 
      Longitude = 0.0,
      Altitude = 0.0;
char  NorthSouth = 'N', 
      EastWest = 'W';
int   Fix = 0, 
      Sats = 0;
      
// Simple timer to Update Display.
#define INTERVAL 50
unsigned long Timer;

#include <SoftwareSerial.h> // Header for serial code.
SoftwareSerial SW_Serial(12, 13); // RX, TX
#include "DecodeGPGGA.h" // Header for GPS decoding 

// Run once, To set up system
void setup()
{
  // Initialize update and clock time.
  Timer = millis();
  ClockTimer = millis();

  // Set up basic serial port.
  Serial.begin( 9600 );
  // Set up LCD.
  LcdDriver.begin( 16, 2 );
  
  // Software Based Serial.
  SW_Serial.begin( 9600 );
  pinMode(10, OUTPUT );
} // End of setup

// Code that is run continuously.
void loop()
{
  char ch;

  // Clock
  if( millis() - ClockTimer >= CLOCK_INTERVAL )
  {
      // update and display clock.
      UpdateClock();
      LcdDriver.clear();
      LcdDriver.setCursor(0,0);
      SendClock();
      // Place GPS date on next 
      LcdDriver.setCursor(9,0);
      LcdDriver.print( Altitude,1);
      LcdDriver.setCursor(0,1);
      LcdDriver.print( NorthSouth );
      LcdDriver.print( Latitude,3 );
      LcdDriver.print( " " );
      LcdDriver.print( EastWest );
      LcdDriver.print( Longitude,3 );
      
      ClockTimer += CLOCK_INTERVAL;
  } // End of clock timer
  
  // Check for incoming serial data.
  ch = SW_Serial.read();
  if (ch != -1 )
  {
    // send strings to serial monitor for DEMO.
    Serial.print( ch ); 
    
    // Scan incoming characters for GPGGA string
    if( GGADecoderProcessor( ch ) )
    {
         PORTB |= 4; // Set pin 10 high
         // Copy data from GPGGA string into
         // local variables.
         Hours = GPS_Time / 10000;
         Minutes = (GPS_Time-10000*(long)Hours)/100;
         Seconds = (GPS_Time-10000*(long)Hours-100*(long)Minutes);
         Serial.println( "  " );
         Serial.print("T ");
         Serial.print(Hours);
         Serial.print(":");
         Serial.print(Minutes);
         Serial.print(":");
         Serial.println(Seconds);
         
         Latitude = GPS_Latitude, 
         NorthSouth = GPS_NorthSouth;
         Serial.print("LA ");
         Serial.print(Latitude,3);
         Serial.println( NorthSouth );
         Longitude = GPS_Longitude,
         EastWest = GPS_EastWest;
         Serial.print("LO ");
         Serial.print(Longitude,3);
         Serial.println( EastWest );
         Altitude = GPS_Altitude;
         Serial.print("A ");
         Serial.println(Altitude,1);
         Fix = GPS_Fix, 
         Sats = GPS_Sats;
         PORTB &= 0xfb; // Set pin 10 low 
    } // End of GPGGA decode
    
  } // End of Serial available if

} // End of loop

