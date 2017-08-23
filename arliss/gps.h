//////////////////////////////////////////////////
// Gps.h
//
// API
// 
//
//
// by Olman D. Quiros Jimenez
/////////////////////////////////////////////////




/////////////////////////////////////////////////
//  INCLUDES
////////////////////////////////////////////////




/////////////////////////////////////////////////
//  DEFINES
////////////////////////////////////////////////
#define DEBUG

// For GPS



//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////

static const uint32_t gps_baud = 9600;


// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
#ifdef FEATHER
  #define gps_serial Serial1
#else
static const int gps_rx_pin = GPS_RX_PIN, gps_tx_pin = GPS_TX_PIN;
SoftwareSerial gps_serial(gps_rx_pin, gps_tx_pin);
#endif




double destination_lat;
double destination_lon;

unsigned long distance_to_dest = 9999999;
long course_to_dest;

//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////

float get_lat();
float get_lon();
unsigned long get_distance_to_dest();
long get_course_to_dest();
static void gps_delay(unsigned long ms);




int init_gps(double dest_lat, double dest_lon )
{
  destination_lat = dest_lat;
  destination_lon = dest_lon;
  
  gps_serial.begin(gps_baud);
  
  // Wait until receive valid gps data
  while(gps.location.isValid() == 0)
  {
    #ifdef DEBUG
    Serial.println(F("Waiting for valid GPS data!!!"));
    #endif
    
    
    if ( millis() > 7000 && gps.charsProcessed() < 10 )
    {
      Serial.println(F("No GPS data received: check wiring!!!"));
      return EXIT_FAILURE;
    }
    
    gps_delay(500);
  
  }
  return EXIT_SUCCESS;
}



void print_gps_data()
{
  if (gps_serial.available()) gps.encode(gps_serial.read());
  
  Serial.print( "| Lat:" );
  Serial.print( gps.location.lat(), 6 );
  
  Serial.print( "| Long:" );
  Serial.print(gps.location.lng(), 6);
  
  Serial.print( "| Dist:" );
  get_distance_to_dest();
  Serial.print( distance_to_dest );
  
  Serial.print( "| Course:" );
  get_course_to_dest();
  Serial.print( course_to_dest );

  Serial.println();
}




float get_lat()
{
  return gps.location.lat();
}




float get_lon()
{
  return gps.location.lng();
}


unsigned long get_distance_to_dest()
{
  if (gps_serial.available()) gps.encode(gps_serial.read());
  distance_to_dest = (unsigned long)TinyGPSPlus::distanceBetween( gps.location.lat(), gps.location.lng(), destination_lat, destination_lon) ;
  return distance_to_dest;
}


long get_course_to_dest()
{
    if (gps_serial.available()) gps.encode(gps_serial.read());
    course_to_dest =    TinyGPSPlus::courseTo( gps.location.lat(), gps.location.lng(), destination_lat, destination_lon);
    return course_to_dest;
}


// This custom version of delay() ensures that the gps object is being "fed".
static void gps_delay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (gps_serial.available())
      gps.encode(gps_serial.read());
  } while (millis() - start < ms);
}












