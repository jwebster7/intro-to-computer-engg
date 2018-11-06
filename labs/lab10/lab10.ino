#include <TimerOne.h>
#include <MsTimer2.h>

#define ANALOGWRITE

// Pins used
#define AnalogPin 0 
#define AnalogOutputPin 10

float Time; 
float Frequency = .5;
float Period = 1.0 / Frequency;
float x = 0;

//Interupt service routine
void pwm_ISR()
{
  digitalWrite(13, HIGH); //Turns LED on
  Time += 5e-3; //Advance time by sample interval
  if (Time > Period)
  {
    Time -= Period; //Keeping check on Time so it won't grow too large
  } //end if
  x = 511*sin(6.2831853*Frequency*Time) + 512;
  Timer1.setPwmDuty(10, x);
  digitalWrite(13, LOW); //Turns LED off
} //end ISR function

void setup() 
{
  MsTimer2::set(5, pwm_ISR); //sets the time in ms
  MsTimer2::start(); //Enables the interrupt
  Timer1.initialize(250); //Initializes a timers period in microseconds
  Timer1.pwm(10, 512); //Generates a PWM waveform on pin 10
  pinMode(13, OUTPUT); //Set pin 13 to ouput for LED
  pinMode(10, OUTPUT); //Set pin 10 to output for PWM
}

void loop() 
{
  // put your main code here, to run repeatedly:

}

