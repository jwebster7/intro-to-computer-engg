#include "ClockBasics.h"

// ClockTimer
#define CLOCK_INTERVAL 1000
unsigned long ClockTimer;

// Simple timer to flash LED.
#define LED_INTERVAL 500
unsigned long LedTimer;

// Run once, To set up system
void setup()
{
  // Initialize LED timer and pin
  LedTimer = millis();
  pinMode(13, OUTPUT);

  // Serial Com.
  Serial.begin(9600);

  // Set up clock 
  ClockTimer = millis();
  Hours = 23;
  Minutes = 59;
  Seconds = 55;

} // End of setup

// Code that is run continuously.
void loop()
{
  // LED Flashing Timer.
  if (millis() - LedTimer >= LED_INTERVAL)
  {
    // Toggle LED.
    if (digitalRead(13))
    {
       digitalWrite(13, LOW);
    }
    else
    {
       digitalWrite(13, HIGH);
    }
    LedTimer += LED_INTERVAL; // Update Timer.

  } // End of Led Timer.

  // Check for one second to update clock
  if( millis() - ClockTimer >= CLOCK_INTERVAL )
  {
     UpdateClock(); // move clock ahead one second.
     SendClock();   // send to serial monitor.
     ClockTimer += CLOCK_INTERVAL; //UPDATE TIMER
  }
  
  // Check for incoming serial data.
  if (Serial.available())
  {
      // Use incoming character to set clock.
      SettingClock( Serial.read() );
      
  } // End of Serial available if

} // End of loop

