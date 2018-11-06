#include <LiquidCrystal.h>                    //includes LCD lib
LiquidCrystal LcdDriver(12,10,8,6,5,4);       //creates a LCD object; 12 = RS pin, 10 = RW pin, 8 = enable pin;
                                              //Controlled using pin 6, 5, 4
unsigned long LcdTimer;                       //Timer for the LCD Loop
float RPM;                                    //Global var for RPM's
float timeElapsed;                            //Global var holding change in Time; from one rising edge to the next
float numerator;                              //Global var for holding the numberator for finding the RPM

//Sends the RPM to the LCD
void SendDisplay(float rpmRecieved)
{
  LcdDriver.begin(16,2);                      //Sets the position of the LCD
  LcdDriver.print(rpmRecieved);               //Prints the RPM's at (16, 2)
}

//Sets up the variables to be used in the code
void setup() 
{  
  numerator = 1.052632 * (10**6);             //store the numerator for the RPM equation
  timeElapsed = 1;                            //Initialize to 1; Will later be calculated with difference between
                                              //2 different times (rising edge to next rising edge)
  RPM = numerator / timeElapsed;              //Finding the RPM
}

//Runs the program; 
//Calls SendDisplay
void loop() 
{
  
}


