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


float press, temp;

//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\nSetting Barometer");
  setup_barometer();
  Serial.println("\nBarometer Ready!!");
  
  Serial.print("\nGround altitude: ");
  Serial.println(ground_altitude);
  
  current_rover_state = pre_launch;

}


void print_barometer_data()
{
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
  
  float temp_alt = get_altitude() ;
  //Alt
  Serial.print(" mbar altitude: ");
  Serial.print(temp_alt);
  Serial.print(" m ");
  
  Serial.print(", Relative Altitude: ");
  Serial.println(ground_altitude - temp_alt );
  //////////////////////////////////////////////////////

}


void loop()
{
  //Serial.print("Current rover state:");
  //Serial.println(current_rover_state);
  print_barometer_data();
  
  
  //float temp_alt = get_altitude() ;
  //Serial.print("Ground Altitude: ");
  //Serial.print(ground_altitude );
  //Serial.print(", Absolute Altitude: ");
  //Serial.print(temp_alt);
  //Serial.print(", Relative Altitude: ");
  //Serial.println(ground_altitude - temp_alt );
  
}





