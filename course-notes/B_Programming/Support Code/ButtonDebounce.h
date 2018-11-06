#ifndef ButtonDebounce_H
#define ButtonDebounce_H

// Set up pin and button state.
int ButtonPin = 4;
enum buttonStates {BS_Idle,BS_Wait,BS_Low};
buttonStates buttonState = BS_Idle;
unsigned long buttonTimer;

// Initialization code, setting up pin.
void ButtonInitialize( int pin )
{
    ButtonPin = pin;
    pinMode( ButtonPin, INPUT );
} // End of ButtonInitialize

// Function called in loop to check for button release.
// Returns a 1 on the buttons release.
int ButtonTest(  )
{
  // Read in the buttons current value.
  int Press = digitalRead( ButtonPin ); 
  int ReturnValue = 0;
  switch( buttonState )
  {
    case BS_Idle: // if we are waiting for a press,
       if( Press == LOW )
       {
         // Once press occurs
         buttonTimer = millis();  // record time
         buttonState = BS_Wait;        // and move to next state
       }
       break; 
    case BS_Wait: // button just went low
       if( Press == HIGH ) // and now goes high
       {
         buttonState = BS_Idle;  // return to 0 state.
       }
       else // if still low
       {
         // and sufficient time has passed.
         if( millis() - buttonTimer >= 10 )
         {
            ReturnValue = 1; // Return 1 indicating pressed.
            buttonState = BS_Low; // move on to state two
         }
       }
       break;
     case BS_Low:
       if( Press == HIGH )
       {
         ReturnValue = 2; // Return 2 indicating release.
         buttonState = BS_Idle;
       } // End of high test.
       break;
  } // End of switch on buttonState
  
  return ReturnValue;
  
} // End of ButtonRead

#endif
