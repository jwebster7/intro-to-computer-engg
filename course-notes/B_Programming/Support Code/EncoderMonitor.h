// Variable for keeping track of encoder change.
volatile int EncoderValue;

// Service Routine for Encoder line A
void EncoderMonitorPinA( void )
{
     // compare pin 3 and pin 2
     if( bitRead(PIND,3) == bitRead(PIND, 2) )
     {
         EncoderValue--;
     }
     else
     {
         EncoderValue++;
     }
}// End of EncoderMonitorPinA

// Service Routine for Encoder line B
void EncoderMonitorPinB( void )
{
     // compare pin 3 and pin 2
     if( bitRead(PIND,3) == bitRead(PIND,2) )
     {
         EncoderValue++; // Note this is the opposite
                         // of the action in PinA.
     }
     else
     {
         EncoderValue--;
     }
} // End of EncoderMonitorPinB

// Initializes the Encoder Monitoring Code.
void EncoderInitialize()
{
   // Set encoder value to zero
   EncoderValue = 0; 
   
   // Set up interrupts to monitor inputs from encoder.
   attachInterrupt( 0, EncoderMonitorPinA, CHANGE );
   attachInterrupt( 1, EncoderMonitorPinB, CHANGE );

}

