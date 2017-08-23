//////////////////////////////////////////////////
// Barometer.h
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

// For Barometer



//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////

// For Barometer
MS5611 barometer; //ms5611
double referencePressure;
float ground_altitude;
float max_altitude;
float max_relative_altitude;

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
  
  Serial.print(", Max Relative: ");
  Serial.println(max_relative_altitude);
  //////////////////////////////////////////////////////
}



////////////////// SET UP FUNCTIONS ///////////////////////////////////////
int init_barometer()
{
  if(!barometer.begin(MS5611_ULTRA_HIGH_RES)) return EXIT_FAILURE;

    // Check settings
  barometer.getOversampling();  

  // Get reference pressure for relative altitude
  referencePressure = barometer.readPressure();

      // Check settings
  barometer.getOversampling();  
  
  // Set ground altitude
  ground_altitude = get_altitude();
  return EXIT_SUCCESS;
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
  float temp_relative_altitude= get_altitude() - ground_altitude;
  if(temp_relative_altitude > max_relative_altitude) max_relative_altitude = temp_relative_altitude;  // Set Max relative altitude when needed
  return temp_relative_altitude;
}


void reset_relative_altitude()
{
   ground_altitude = get_altitude() ; 
   max_relative_altitude = 0;
}

//////////////////////////  PRESSURE FUNCTIONS  ///////////////////////////////////////////////
//Wrapper, returns long
long get_pressure()
{
  return barometer.readPressure();
}
