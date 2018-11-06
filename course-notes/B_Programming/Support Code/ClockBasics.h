#ifndef ClockBasics_H
#define ClockBasics_H

// Variable used as clock settings.
int Hours, Minutes, Seconds;

// This function is to be called every second
// to update the clock represented by the
// global variables Hours, Minutes, Seconds
void UpdateClock()
{
  // Check if Seconds not at wrap point.
  if (Seconds < 59)
  {
    Seconds++; // Move seconds ahead.
  }
  else
  {
    Seconds = 0; // Reset Seconds
    // and check Minutes for wrap.
    if (Minutes < 59)
    {
      Minutes++; // Move seconds ahead.
    }
    else
    {
      Minutes = 0; // Reset Minutes
      // check Hours for wrap
      if (Hours < 23)
      {
        Hours++;// Move Hours ahead.
      }
      else
      {
        Hours = 0;// Reset Hours
      }// End of Hours test.
    } // End of Minutes test
  } // End of Seconds test
} // end of UpdateClock()

// Send Hours, Minutes and Seconds to a display.
void SendClock()
{
  // Check if leading zero needs to be sent
  if (Hours < 10)
  {
    LcdDriver.print("0");
  }
  LcdDriver.print(Hours); // Then send hours
  LcdDriver.print(":"); // And separator
  // Check for leading zero on Minutes.
  if (Minutes < 10)
  {
    LcdDriver.print("0");
  }
  LcdDriver.print(Minutes); // Then send Minutes
  LcdDriver.print(":"); // And separator
  // Check for leading zero needed for Seconds.
  if (Seconds < 10)
  {
    LcdDriver.print("0");
  }
  LcdDriver.print(Seconds); // Then send Seconds
} // End of SendClock()

// States for setting clock.
enum ClockStates { CLOCK_RUNNING, CLOCK_SET_HOURS,
                   CLOCK_SET_MINUTES, CLOCK_SET_SECONDS };
ClockStates clockState = CLOCK_RUNNING;

// Function that processes incoming characters to set the clock.
void SettingClock(int Button, int EncUpDown )
{
	// interpret input based on state
	switch (clockState)
	{
	case CLOCK_RUNNING:
		if (Button)
		{
			clockState = CLOCK_SET_HOURS;
			Hours = 0;   // Reset clock values.
			Minutes = 0;
			Seconds = 0;
		}
		break;
	case CLOCK_SET_HOURS: // 
		if (EncUpDown > 0)
		{
		  Hours++;
      if( Hours > 23 )
          Hours = 0;
		} 
		else if (EncUpDown < 0)
		{
		  Hours--;
      if( Hours < 0 )
          Hours = 23;
    } 
		else if (Button)
			clockState = CLOCK_SET_MINUTES;
		break;
	case CLOCK_SET_MINUTES: // 
    if (EncUpDown > 0)
    {
      Minutes++; 
      if( Minutes > 59 )
          Minutes = 0;
    }
    else if (EncUpDown < 0)
    {
      Minutes--;
      if( Minutes < 0 )
          Minutes = 59;
    }
    else if (Button)
      clockState = CLOCK_SET_SECONDS;
    break;
	case CLOCK_SET_SECONDS: // 
    if (EncUpDown > 0)
    {
      Seconds++; 
      if( Seconds > 59 )
          Seconds = 0;
    }
    else if (EncUpDown < 0)
    {
      Seconds--;
      if( Seconds < 0 )
          Seconds = 59;
    }
    else if (Button)
      clockState = CLOCK_RUNNING;
    break;

	}// End of clock mode switch.

} // End of SettingClock

#endif
