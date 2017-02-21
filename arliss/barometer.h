//////////////////////////////////////////////////
// Barometer.h
//
// API
// 
//
//
// 
/////////////////////////////////////////////////




/////////////////////////////////////////////////
//  INCLUDES
////////////////////////////////////////////////



/////////////////////////////////////////////////
//  DEFINES
////////////////////////////////////////////////
#define DEBUG

// For Barometer



//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////

// For Barometer
MS5611 barometer; //ms5611
double referencePressure;
float max_altitude;


//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////


long get_pressure();
double get_temperature();
float get_altitude();
float get_relative_altitude();


/////////////////// GENERAL FUNCTION  //////////////////////////////


void print_barometer_data()
{
   ////////////////////////Barometro//////////////////////////
  //Temp
  Serial.print("temp: ");
  Serial.print(get_temperature());
  
  
  //Press
  Serial.print(", pres: ");
  Serial.print(get_pressure());
  
  //Alt
  Serial.print(", altitude: ");
  Serial.print(get_altitude());
  
  Serial.print(", Relative Alt: ");
  Serial.print(get_relative_altitude() );
  
  Serial.print(", Max Alt: ");
  Serial.println(max_altitude);
  //////////////////////////////////////////////////////
}



////////////////// SET UP FUNCTIONS ///////////////////////////////////////
void setup_barometer()
{
  // Initialize Barometer sensor
  #ifdef DEBUG
    Serial.println("Initialize Barometer...");
  #endif

  while(!barometer.begin())
  {
    #ifdef DEBUG
      Serial.println("Could not find a valid Barometer sensor, check wiring!");
    #endif
    delay(500);
  }
  // Get reference pressure for relative altitude
  referencePressure = barometer.readPressure();
  // Check settings
  barometer.getOversampling();	
}



//////////////////////// TEMPERATURE FUNCTIONS  ////////////////////////////////////////////
//Wrapper, returns double
double get_temperature()
{
  return barometer.readTemperature();
}



///////////////////////// ATLTITUDE FUNCTIONS /////////////////////////////////////////////////
float get_altitude() 
{
  long temp_pressure = barometer.readPressure();
  // Calculate altitude
  float temp_altitude = barometer.getAltitude(temp_pressure);
  if(temp_altitude > max_altitude) max_altitude = temp_altitude;  // Set Max altitude when needed
  return temp_altitude; 
}

float get_relative_altitude()
{
  long temp_pressure = barometer.readPressure();
  // Calculate altitude
  return barometer.getAltitude(temp_pressure, referencePressure);
}


//////////////////////////  PRESSURE FUNCTIONS  ///////////////////////////////////////////////
//Wrapper, returns long
long get_pressure()
{
  return barometer.readPressure();
}
