#include <SPI.h>
#include <LiquidCrystal.h>
int local;
unsigned long secondTimer;
float Temperature;
float ThermoCouple;

LiquidCrystal LcdDriver(11,9,5,6,7,8); //Declaring which pins to use
int count; //Declaring int variable count
unsigned long LcdTimer; //Timer for the loop
unsigned long SecondsTimer; //Timer for seconds
int Hours, Minutes, Seconds; //Vars for Hours, Minutes, Seconds


//*****************************************************************
void SW_SpiInitialize()
{
  pinMode(A5, OUTPUT); //Clock
  pinMode(A4, INPUT); //Data In
  pinMode(A3, OUTPUT); //Chip Select
}

int SW_Spi16( void )
{
  int hold = 0; //A temp variable
  
  PORTC &= ~(0x08); //Set Chip Select Low (the 3rd bit; A3)
  PORTC &= ~(0x20); //Set Clock low (the 5th bit; A5)
  
  //Loop for k = 15 to 0
  for (int k = 15; k >= 0; k--)
  {
    PORTC |= 0x20; //Set Clock high
    //Read input and place in bit k
    if (bitRead(PINC, 4))
    {
      bitSet(hold, k);
    }
    PORTC &= ~(0x20); //Set Clock low
  }
  //Set Chip Select High
  PORTC |= 0x08;
  return hold;
}

// function to read temperature from Max6675
float Read_SPI_Temperature(){
  int TempData = SW_Spi16();
  //set the chip select low
  //PORTC &= ~0x08;
  TempData = (TempData / 8 ) & 0x0fff;
  Temperature = 0.25 * (float) TempData;
  Temperature = 1.8*Temperature + 32.0;
  //PORTC |= 0x08;
  return Temperature;
} // end of Read_SPI_Temperature

//*****************************************************************

void UpdateClock()
{
    //If Seconds are less than 59
    if (Seconds < 59)
    {
        Seconds++; //Increments Seconds
    }
    else 
    {
        Seconds = 0; //Resets Seconds
    
   //If Minutes are less than 59
        if (Minutes < 59)
        {
            Minutes++; //Increments Minutes
        }
        else
        {
            Minutes = 0; //Resets Minutes  

       //If Hours are less than 23
            if (Hours < 23)
            {
                Hours++; //Increments Hours  
            }
            else
            {
                Hours = 0; //Reset Hours  
            }//end hours test
        }//end minutes test
    }//end seconds test
}//end updateclock method

//Method SendClock
void SendClock()
{
    //checks what the leading digit of hours should be; if hours Less than 10
    if (Hours < 10)
    {
        LcdDriver.print("0"); //Print 0 if Hours less than 10
    }
    LcdDriver.print(Hours); //Print Hours
    LcdDriver.print(":"); //Print “:” between Hours

    //checks for leading digit of minutes
    if (Minutes < 10)
    {
        LcdDriver.print("0"); //Print 0 if Minutes less than 10
    }
    LcdDriver.print(Minutes); //Print Minutes
    LcdDriver.print(":"); //Print “:” between Minutes and Seconds

    //checks for leading digit of seconds
    if (Seconds < 10)
    {
        LcdDriver.print("0"); //Print 0 if Seconds less than 10
    }
    LcdDriver.print(Seconds); //Print Seconds
}//end of sendclock method

//*****************************************************************

void setup() 
{
    LcdDriver.begin(16,2); //Starting the LCD
    LcdDriver.clear(); //Clearing the LCD
    count = 0; //Initializing count to zero
    SecondsTimer = millis(); //Sets SecondsTimer = millis()

    //Initialize the clock
    Hours = 23; //initializes Hours to 23
    Minutes = 59; //initializes Minutes to 59
    Seconds = 55; //initializes Seconds to 55

  SW_SpiInitialize();
  secondTimer = millis();
  Serial.begin( 9600);
}

void loop() 
{
  if( millis() - secondTimer >= 1000 )
  {
    //Thermo code
      // Read Temperature sensor
      ThermoCouple = Read_SPI_Temperature( );
      //report data
      LcdDriver.setCursor(0,0);
      LcdDriver.print( "Temp = ");
      LcdDriver.print( ThermoCouple );

    //clock code
      UpdateClock(); //Updates the clock
      LcdDriver.setCursor( 0,1 ); //Sets the clock on the seconds row
      SendClock(); //Sends the clock to the LCD

    //incrementing the timer
      secondTimer += 1000;
  }
}
//*****************************************************************
