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
  float temp_altitude = get_altitude();
  Serial.print(", altitude: ");
  Serial.print(temp_altitude);
  
  Serial.print(", Relative Alt: ");
  Serial.print(temp_altitude - ground_altitude );
  
  Serial.print(", Max Alt: ");
  Serial.println(max_altitude);
  //////////////////////////////////////////////////////
}



////////////////// SET UP FUNCTIONS ///////////////////////////////////////
int init_barometer()
{
  if(!barometer.begin()) return EXIT_FAILURE;

  // Get reference pressure for relative altitude
  referencePressure = barometer.readPressure();
  // Check settings
  barometer.getOversampling();	
  
  // Set ground altitude
  ground_altitude = get_altitude() ;
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




//////////////////////////  PRESSURE FUNCTIONS  ///////////////////////////////////////////////
//Wrapper, returns long
long get_pressure()
{
  return barometer.readPressure();
}
