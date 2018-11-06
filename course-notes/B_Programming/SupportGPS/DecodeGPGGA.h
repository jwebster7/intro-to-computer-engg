#ifndef DecodeGPGGA_h
#define DecodeGPGGA_h 1

// Set up decoding state machine.
enum GPGGA_Decoder { GPS_WAIT, // waiting for starting $.
                     GPS_G,    // Waiting for first G
                     GPS_GP,    // Waiting for P
                     GPS_GPG,   // Waiting for G
                     GPS_GPGG,  // Waiting for G
                     GPS_GPGGA, // Waiting for final A
                     GPS_COMMA,
                     GPS_TIME,  // Reading through time.
                     GPS_TIME_MS,
                     GPS_LATITUDE_INT,
                     GPS_LATITUDE_FRAC,
                     GPS_N_S,
                     GPS_LONGITUDE_INT,
                     GPS_LONGITUDE_FRAC,
                     GPS_E_W,
                     GPS_FIX,
                     GPS_SATS,
                     GPS_DILUTION,
                     GPS_ALTITUDE_INT,
                     GPS_ALTITUDE_FRAC,
                     GPS_END };

GPGGA_Decoder GGADecoder = GPS_WAIT;

long GPS_Time = 0;
int GPS_Time_ms = 0;
float GPS_Latitude = 0.0, GPS_Longitude = 0.0;
float GPS_Fraction = 0.0, GPS_Degrees;
char  GPS_NorthSouth = 'N', GPS_EastWest = 'W';
int   GPS_Fix = 0, GPS_Sats = 0;
float GPS_Altitude = 0.0;


int GGADecoderProcessor( char Incoming )
{
    switch( GGADecoder )
    {
        default:
        case GPS_WAIT:
           if( Incoming == '$' )
              GGADecoder = GPS_G; 
           break;
        case GPS_G:
           if( Incoming == 'G' )
              GGADecoder = GPS_GP;
           else 
              GGADecoder = GPS_WAIT;               
           break;
        case GPS_GP:
           if( Incoming == 'P' )
              GGADecoder = GPS_GPG; 
           else 
              GGADecoder = GPS_WAIT;               
           break;
        case GPS_GPG:
           if( Incoming == 'G' )
              GGADecoder = GPS_GPGG; 
           else 
              GGADecoder = GPS_WAIT;               
           break;
        case GPS_GPGG:
           if( Incoming == 'G' )
              GGADecoder = GPS_GPGGA; 
           else 
              GGADecoder = GPS_WAIT;               
           break;
        case GPS_GPGGA:
           if( Incoming == 'A' )
              GGADecoder = GPS_COMMA; 
           else 
              GGADecoder = GPS_WAIT;               
           break;
        case GPS_COMMA:
           if( Incoming == ',' )
           {   
                GPS_Time = 0;
                GPS_Latitude = -1.0;
				        GPS_Longitude = -1.0;
				        GPS_Altitude = -500.0;
				        GGADecoder = GPS_TIME;
           }
           else 
              GGADecoder = GPS_WAIT;               
           break;
        case GPS_TIME:
           if( Incoming == ',' )
               GGADecoder = GPS_LATITUDE_INT; 
           else if( Incoming == '.' )
               GGADecoder = GPS_TIME_MS;
           else if( Incoming >= '0' && Incoming <= '9' )
               GPS_Time = GPS_Time*10l + (Incoming - '0');
           break;
        case GPS_TIME_MS:
           if( Incoming == ',' )
              GGADecoder = GPS_LATITUDE_INT;
           else if( Incoming >= '0' && Incoming <= '9' )
               GPS_Time_ms = GPS_Time_ms*10 + (Incoming - '0');
           break;
        case GPS_LATITUDE_INT:
           if( Incoming == '.' )
           {
              GPS_Fraction = 0.1F;
              GGADecoder = GPS_LATITUDE_FRAC; 
           }
           else if( Incoming == ',' )
                GGADecoder = GPS_N_S; 
           else if( Incoming >= '0' && Incoming <= '9' )
                GPS_Latitude = GPS_Latitude*10.0F 
				              + (float)(Incoming - '0');
           break;
        case GPS_LATITUDE_FRAC:
           if( Incoming == ',' )
           {
                GPS_Degrees = (int) (GPS_Latitude / 100); 
                GPS_Latitude = GPS_Degrees 
                             + ( GPS_Latitude - 100*GPS_Degrees )/60.0f;
              
                GGADecoder = GPS_N_S; 
           }
           else if( Incoming >= '0' && Incoming <= '9' )
           {
               GPS_Latitude = GPS_Latitude 
                               + GPS_Fraction * (Incoming - '0');
               GPS_Fraction *= 0.1F;
           }
           break;
        case GPS_N_S:
           if( Incoming == ',' )
                GGADecoder = GPS_LONGITUDE_INT; 
           else 
                GPS_NorthSouth = Incoming;
           break;
        case GPS_LONGITUDE_INT:
           if( Incoming == '.' )
           {
              GPS_Fraction = 0.1F;
              GGADecoder = GPS_LONGITUDE_FRAC; 
           }
           else if( Incoming == ',' )
           {
                GPS_Degrees = (int) (GPS_Longitude / 100); 
                GPS_Longitude = GPS_Degrees 
                             + ( GPS_Longitude - 100*GPS_Degrees )/60.0f;
                GGADecoder = GPS_E_W; 
           }
           else if( Incoming >= '0' && Incoming <= '9' )
                GPS_Longitude = GPS_Longitude*10.0F 
				                 + (float)(Incoming - '0');
           break;
        case GPS_LONGITUDE_FRAC:
           if( Incoming == ',' )
           {
                GPS_Degrees = (int)( GPS_Longitude / 100 ); 
                GPS_Longitude = GPS_Degrees 
                             + ( GPS_Longitude - 100*GPS_Degrees )/60.0f;
                GGADecoder = GPS_E_W; 
           }
           else if( Incoming >= '0' && Incoming <= '9' )
           {
                GPS_Longitude = GPS_Longitude 
                              + GPS_Fraction * (Incoming - '0');
                GPS_Fraction *= 0.1F;
           }
           break;
        case GPS_E_W:
           if( Incoming == ',' )
                GGADecoder = GPS_FIX; 
           else 
                GPS_EastWest = Incoming;
           break;
        case GPS_FIX:
           if( Incoming == ',' )
                GGADecoder = GPS_SATS; 
           else if( Incoming >= '0' && Incoming <= '9' )
                GPS_Fix = (Incoming - '0');
           break;
        case GPS_SATS:
           if( Incoming == ',' )
               GGADecoder = GPS_DILUTION; 
           else if( Incoming >= '0' && Incoming <= '9' )
                GPS_Sats = (Incoming - '0');
           break;
        case GPS_DILUTION:
           if( Incoming == ',' )
           {
               GGADecoder = GPS_ALTITUDE_INT; 
           }
           break;
        case GPS_ALTITUDE_INT:
           if( Incoming == '.' )
           {
              GPS_Fraction = 0.1F;
              GGADecoder = GPS_ALTITUDE_FRAC; 
           }
           else if( Incoming == ',' )
                GGADecoder = GPS_END; 
           else if( Incoming >= '0' && Incoming <= '9' )
                GPS_Altitude = GPS_Altitude*10.0F 
                      + (float)(Incoming - '0');
           break;
        case GPS_ALTITUDE_FRAC:
           if( Incoming == ',' )
           {
               GGADecoder = GPS_END; 
               return 1; 
           }
           else if( Incoming >= '0' && Incoming <= '9' )
           {
               GPS_Altitude = GPS_Altitude 
                              + GPS_Fraction * (Incoming - '0');
               GPS_Fraction *= 0.1F;
           }
           break;
        case GPS_END:
			if (Incoming == '\n' || Incoming == '\r')
			{
				GGADecoder = GPS_WAIT;
				return 1; // End detected so return a true
			}
           break;
    }
    return 0; // by default return false.
}
#endif
