unsigned long LedTimer;
unsigned long LedTimerThree;
void setup() {
  pinMode(13, OUTPUT);
  LedTimer = millis();
  pinMode(12, OUTPUT);
  LedTimerThree = millis();
}
void loop() {
//one second LED
  if ( millis()-LedTimer >= 1000 ) {
      if ( digitalRead(13) == HIGH ){
          digitalWrite( 13, LOW );
      }//end if
      else {
        digitalWrite( 13, HIGH );
      }//end else
    LedTimer += 1000;
    }//end if

//three second LED
if ( millis()-LedTimerThree >= 3000 ) {
      if ( digitalRead(12) == HIGH ){
          digitalWrite( 12, LOW );
      }//end if
      else {
        digitalWrite( 12, HIGH );
      }//end else
    LedTimerThree += 3000;
    }//end if
}//end loop
