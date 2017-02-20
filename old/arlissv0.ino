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
  
  pre_launch_routine();
  

}


void print_barometer_data()
{
   ////////////////////////Barometro//////////////////////////
  //Temp
  Serial.print(" temp: ");
  Serial.print(get_temperature());
  
  
  //Press
  Serial.print(", pres: ");
  Serial.print(get_pressure());
  
  //Alt
  float temp_alt = get_altitude() ;
  Serial.print(", altitude: ");
  Serial.print(get_altitude());
  
  Serial.print(", Relative Alt: ");
  Serial.print(temp_alt - ground_altitude );
  
  Serial.print(", Max Alt: ");
  Serial.println(max_altitude);
  //////////////////////////////////////////////////////

}


void loop()
{
  //Serial.print("Current rover state:");
  //Serial.println(current_rover_state);
  
  //print_barometer_data();
  
  // Execute current rover state corresponding routine
  //(*rover_state_routines[current_rover_state])(); 
  
  Serial.println("\n\nEnded\n\n");
  
  while(1);
}



void print_prelaunch_info()
{
    //Alt
    float temp_alt = get_altitude() ;
    Serial.print("altitude: ");
    Serial.print(get_altitude());
    
    Serial.print(", Relative Alt: ");
    Serial.print(temp_alt - ground_altitude );
    
    Serial.print(", Max Alt: ");
    Serial.println(max_altitude);
    //////////////////////////////////////////////////////
}

// During the pre launch: wait until launch detection
void *pre_launch_routine()
{
  Serial.println("Rove_status: pre_launch");
  
  while(current_rover_state == pre_launch)
  {
    print_prelaunch_info();
  }
  
  current_rover_state = ascent;
  ascent_routine();
}

void *ascent_routine()
{
  Serial.println("Rove_status: ascent");
  
  current_rover_state = descent;
  descent_routine();
}


void *descent_routine()
{
  Serial.println("Rove_status: descent");
  
  current_rover_state = navigation;
  navigation_routine();
}


void *navigation_routine()
{
  Serial.println("Rove_status: navigation");
  
  current_rover_state = closing_up;
  closing_up_routine();
}


void *closing_up_routine()
{
  Serial.println("Rove_status: closing_up");
  
  current_rover_state = end_navigation;
  end_navigation_routine();
}



void *end_navigation_routine()
{
  Serial.println("Rove_status: end_navigation");
  
  
}




