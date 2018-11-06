unsigned long LedTimerTwenty;
unsigned long LedTimerTen;
void setup() {
  pinMode(12, OUTPUT);
  LedTimerTen = millis();
  pinMode(13, OUTPUT);
  LedTimerTwenty = millis();

}
void loop() {
  
  if ( millis() - LedTimerTwenty >= 20 ) {

    //Pulsing the pin quickly every 20 milliseconds
    PORTB &= ~0x10; //force bit 4, Pin 12, low
    PORTB |= 0x10; //force bit 4, pin 12, high

    //pulsing the 13 pin every 20 milliseconds
    if ( digitalRead(13) == HIGH ) {
      digitalWrite( 13, LOW );
    }//end if
    else {
      digitalWrite( 13, HIGH );
    }//end else
    LedTimerTwenty += 20;
  }//end if
  
}//end loop

