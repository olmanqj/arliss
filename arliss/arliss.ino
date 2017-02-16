//////////////////////////////////////////////////
// Arliss.ino
//
//
//
//
// 
/////////////////////////////////////////////////



/////////////////////////////////////////////////
//  INCLUDES
////////////////////////////////////////////////

//For IMU Sensor
#include <Wire.h>

//Personal libraries
#include "arliss.h"

//For Barometer MS5611
#include "MS561101BA.h" 
#include "barometer.h"

/////////////////////////////////////////////////
//  DEFINES
////////////////////////////////////////////////
//#define DEBUG






//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////
ROVER_STATE current_rover_state;     // Rover state: 0 = groud pre launch, 1 = launch, 

//Altitude variables
float relative_altitude;
float absolute_altitude;
float ground_altitude;
float max_altitude;


float press, temp;

//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  delay(1000);
  
  Serial.println("\nSetting Barometer...\n");
  setup_barometer();
  Serial.println("\nBarometer Stabilized!!");
  
  current_rover_state = pre_launch;

}


void loop()
{
  //Serial.print("Current rover state:");
  //Serial.println(current_rover_state);
  
  ////////////////////////Barometro//////////////////////////
  //Temp
  
  
  Serial.print(" temp: ");
  float temperature = get_temperature();
  if(temperature) {
    temp = temperature;
  }
  Serial.print(temp);
  
  
  //Press
  Serial.print(" degC pres: ");
  float pressure = get_pressure();
  if(pressure) {
    press = pressure;
  }
  Serial.print(press);
  

  //Alt
  Serial.print(" mbar altitude: ");
  Serial.print(get_altitude(press, temp));
  Serial.println(" m");
  //////////////////////////////////////////////////////
  

}





