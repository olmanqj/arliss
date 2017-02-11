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



//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  delay(1000);
  
  
  setup_barometer();
  
  current_rover_state = pre_launch;

}


void loop()
{
  //Serial.print("Current rover state:");
  //Serial.println(current_rover_state);
  
  ////////////////////////Barometro//////////////////////////
  //Temp
  Serial.print(" temp: ");
  float temperature = barometer.getTemperature(MS561101BA_OSR_4096);
  if(temperature) {
    temp = temperature;
  }
  Serial.print(temp);
  
  
  //Press
  Serial.print(" degC pres: ");
  press = barometer.getPressure(MS561101BA_OSR_4096);
  if(press!=NULL) {
    push_pressure(press);
  }
  press = get_average(pressure_buffer, PRESSURE_BUFFER_SIZE);
  Serial.print(press);
  
  //Alt
  Serial.print(" mbar altitude: ");
  Serial.print(get_altitude(press, temp));
  Serial.println(" m");
  //delay(1000);
  //////////////////////////////////////////////////////
  

}





