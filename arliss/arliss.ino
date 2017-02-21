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
#include "I2Cdev.h"

//Personal libraries
#include "arliss.h"

//For Barometer MS5611
#include "MS5611.h" 
#include "barometer.h"

//For GYRO MPU6050
#include "MPU6050.h"
#include "accelgyro.h"

/////////////////////////////////////////////////
//  DEFINES
////////////////////////////////////////////////
#define DEBUG
#define BAROMETER
#define GYRO



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
  Serial.begin(9600);
  delay(1000);
  
  #ifdef BAROMETER
    #ifdef DEBUG
      Serial.println("\nSetting Barometer");
    #endif
    
    setup_barometer();
    
    #ifdef DEBUG
      Serial.println("\nBarometer Ready!!");
    #endif
  #endif
  
  
  #ifdef GYRO
    #ifdef DEBUG
      Serial.println("\nInitializing Gyro...");
    #endif
    
    accelgyro.initialize();
    // verify connection
    if(accelgyro.testConnection() == 0)
    {
      error_flag = 1;
      #ifdef DEBUG
            Serial.println("Gyro connection failed");
      #endif
    }
    #ifdef DEBUG
      else Serial.println("Gyro connection successful");
    #endif
  #endif
  
  current_rover_state = pre_launch;
  
  pre_launch_routine();
  

}




void loop()
{
  
  
  // Execute current rover state corresponding routine
  //(*rover_state_routines[current_rover_state])(); 
  
  Serial.println("\n\nEnded\n\n");
  
  while(1);
}




// During the pre launch: wait until launch detection
void *pre_launch_routine()
{
  Serial.println("Rove_status: pre_launch");
  
  
  while(current_rover_state == pre_launch)
  {
    print_barometer_data();
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




