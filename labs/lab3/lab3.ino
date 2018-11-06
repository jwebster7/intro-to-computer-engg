unsigned long Timer; //int time to keep track of the time        
char Letter = 'Z'; //this is the letter we will use for our conditional statements

//Setups the variables and functions used
void setup() 
{
  Serial.begin(9600); // Sets and begins the baud rate to 9600
  Timer = millis();
}//end setup

//Loops the main bulk of the code
void loop() 
{
  if ( millis() - Timer >= 500 )
  {    
     Serial.print(Letter);
     Timer += 500;
  }//end if
}//end loop

