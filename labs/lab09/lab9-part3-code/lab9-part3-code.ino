unsigned long Timer;

void setup() 
{
  Timer = millis();     //Initializes Timer to millis()
  Serial.begin(38400);  //Sets baud rate at 38400
  analogReference(EXTERNAL);
}

void loop() 
{
  float voltage; //float to hold the voltage

  //if time elapsed is 500 milliseconds
  if (millis() - Timer >= 500)
  {
    voltage = 3.3*analogRead(0) / 1024.0; //sets voltage from the analog input
    Serial.println(voltage);              //sends number from the ADC and the computed voltage over the serial port
    Timer+=500;                           //increments timer by 500
  }
}
