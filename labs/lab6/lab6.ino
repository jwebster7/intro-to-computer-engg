volatile int encoderPosition;                      //Global variable (int)encoderPosition
unsigned long Time;                                //Time keeps track of time in ms 
unsigned long timer;                               //timer keeps track of time in ms
#include <LiquidCrystal.h>
LiquidCrystal LcdDriver(11, 9, 5, 6, 7, 8 );

//Button enumerator
enum Button                                       //Initializes an enumerator Button w/idle, wait, low
{
  Idle,                                            //enum variable Idle
  Wait,                                            //enum variable Wait
  Low                                              //enum variable Low
};

Button ButtonState;

int ButtonNextState(int input)                     //function that is to be called in loop
{
  switch (ButtonState)
  {
    case Idle:                                     //State where nothing is happening
      {
        if (input == LOW)                          //If button is LOW
        {
          Time = millis();                         //Record time of high to low transition
          ButtonState = Wait;                      //Move to Wait
          digitalWrite(13, HIGH);                  //Turns the LED on
        }
        break;
      }//end Idle

    case Wait:                                     // When Button LOW; Wait for 5 millis
      {
        if (input == HIGH)                         //If button is HIGH
        {
          ButtonState = Idle;                      //Sets the buttonstate to idle
        }
        else if (millis() - Time >= 5)             //If 5 millis has passed
        {
          ButtonState = Low;                       //Setting button state to LOW
          digitalWrite(13, LOW);                   //Turns LED off
          return 1;                                //The button has been pressed
        }
        break;                                     //Breaks out of the switch case
      }//end Wait

    case Low:                                      //Sets Button to LOW
      {
        if (input == HIGH)                         //checks if the input is set to HIGH
        {
          ButtonState = Idle;                      //Sets the buttonstate to idle
        }
        break;                                     //Breaks out of the switch case
      }//end Low
  }//end switch-case
  return 0;
}//end ButtonNextStat

//MonitorA is an interrupt service routine
void MonitorA()
{
  //Check if inputA = inputB
  if (digitalRead(2) == digitalRead(3))                   
  {
    //Increment encoderPosition
    encoderPosition+=1;                    
  }
  //Else, inputA != inputB, therefore
  else                                    
  {
    //Decrement encoderPosition
    encoderPosition-=1;                      
  }
}

//MonitorB is an interrupt service routine 
void MonitorB()
{
  if (digitalRead(2) == digitalRead(3))                   
  {
    //Decrement encoderPosition
    encoderPosition-=1;  
  }
  else
  {
    //Increment encoderPosition
    encoderPosition+=1;  
  }
}


void setup() 
{
  timer = millis();
  pinMode(13, OUTPUT);                               //activates pin 13 to receive output
  pinMode(4, INPUT);                                 //activates pin 4 to accept input
  Button ButtonState = Idle;                         //initializes button buttonstate to idle
  Serial.begin(9600);                                //sets baud rate to 9600
  
  pinMode(2, INPUT);                                 //activates pin 2 for input
  pinMode(3, INPUT);                                 //activates pin 3 for input
  LcdDriver.begin(16, 2);                            //Begins the LCD
  attachInterrupt(digitalPinToInterrupt(2), MonitorA, CHANGE); //Attaches ISR to pin 2 for detecting change
  attachInterrupt(digitalPinToInterrupt(3), MonitorB, CHANGE); //Attaches ISR to pin 3 for detecting change
}

void loop() 
{
    if(millis() - timer >= 100)
    {
      LcdDriver.setCursor(0,0);
      LcdDriver.clear();

      if(ButtonNextState(digitalRead(4)))
      {
        encoderPosition--;
      }//end if 

      LcdDriver.print("Enc Val: ");
      LcdDriver.print(encoderPosition);
      timer+=100;
    }
}

