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
#define DEBUG




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
  
  #ifdef DEBUG
    Serial.println("\nSetting Barometer");
  #endif
  
  setup_barometer();
  
  #ifdef DEBUG
    Serial.println("\nBarometer Ready!!");
    Serial.print("\nGround altitude: ");
    Serial.println(ground_altitude);
  #endif
  
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
  
  //print_barometer_data();
  
  // Execute current rover state corresponding routine
  (*rover_state_routines[current_rover_state])(); 
  
  
}


// During the pre launch: wait until launch detection
void *pre_launch_routine()
{
  Serial.println("Rove_status: pre_launch");
  
  
  //current_rover_state = ascent;
}

void *ascent_routine()
{
  Serial.println("Rove_status: ascent");
  
  current_rover_state = descent;

}


void *descent_routine()
{
  Serial.println("Rove_status: descent");
  
  current_rover_state = navigation;

}


void *navigation_routine()
{
  Serial.println("Rove_status: navigation");
  
  current_rover_state = closing_up;

}


void *closing_up_routine()
{
  Serial.println("Rove_status: closing_up");
  
  current_rover_state = end_navigation;

}



void *end_navigation_routine()
{
  Serial.println("Rove_status: end_navigation");
  
  
}




