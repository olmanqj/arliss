//////////////////////////////////////////////////
// Arliss.ino
//
//
//
//
// by Olman D. Quiros Jimenez
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
// For Debugging
#define DEBUG
#define BAROMETER
#define ACCELGYRO

//For Operations
#define RELATIVE_ALTITUDE_FOR_LAUNCH_DETECTION 1  //Relative altitude for detect launch



//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////
ROVER_STATE current_rover_state;     // Rover state: 0 = groud pre launch, 1 = launch, 

char *  message_buffer;

//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////


void setup()
{
  Wire.begin();
  Serial.begin(9600);
  delay(1000);
  
  // Initialize Barometer
  #ifdef BAROMETER
    send_message("Initializing Barometer");
    // verify connection
    if (init_barometer() == EXIT_FAILURE) handle_error("Barometer connection failed");;
    send_message("Barometer Ready");
  #endif

  // Initialize Accelgyro  
  #ifdef ACCELGYRO
    send_message("Initializing AccelGyro");
    accelgyro.initialize();
    // verify connection
    if(init_accelgyro() == EXIT_FAILURE) handle_error("Gyro connection failed");
    send_message("AccelGyro Ready");
  #endif
  
  current_rover_state = pre_launch;
}




void loop()
{
  // Execute current rover state corresponding routine
  (*rover_state_routines[current_rover_state])(); 
}




////////////////////////// GENERAL FUNCTIONS    /////////////////////////////////////////
int send_message(const char * message)
{
  #ifdef DEBUG
      Serial.print("$");
      Serial.println(message);
  #endif
  return EXIT_SUCCESS;
}


void handle_error(const char * message)
{
  #ifdef DEBUG
      Serial.print("!Error: ");
      Serial.println(message);
      Serial.println("\Ending Program...\n");
  #endif
  while(1);
}




////////////////////////// PRE LAUNCH FUNCTIONS    /////////////////////////////////////////
// During the pre launch: wait until launch detection
void *pre_launch_routine()
{
  send_message("Rove_status: pre_launch");
  
  
      
    #ifdef DEBUG
    Serial.println("Waiting for launch...");
    #endif
  
  while(current_rover_state == pre_launch)
  {
    print_barometer_data();
    // If Relative Altitude > RELATIVE_ALTITUDE_FOR_LAUNCH_DETECTION, Launch detection!!
    if( (get_altitude() - ground_altitude) > RELATIVE_ALTITUDE_FOR_LAUNCH_DETECTION)
    {  
      current_rover_state = ascent; // End the pre_launch_routine
      break;
    }

  }
  send_message("Launched");  
}



////////////////////////// ASCENT FUNCTIONS    /////////////////////////////////////////

void *ascent_routine()
{
  send_message("Rove_status: ascent");
  
  current_rover_state = descent;
}



////////////////////////// DESCENT FUNCTIONS    /////////////////////////////////////////

void *descent_routine()
{
  send_message("Rove_status: descent");
  
  current_rover_state = navigation;
}



////////////////////////// NAVIGATION FUNCTIONS    /////////////////////////////////////////

void *navigation_routine()
{
  send_message("Rove_status: navigation");
  
  current_rover_state = closing_up;
}




////////////////////////// CLOSING UP FUNCTIONS    /////////////////////////////////////////

void *closing_up_routine()
{
  send_message("Rove_status: closing_up");
  
  current_rover_state = end_navigation;
}



////////////////////////// END NAVIGATION FUNCTIONS    ////////////////////////////////////////
void *end_navigation_routine()
{
  send_message("Rove_status: end_navigation");
  
  send_message("Ended");
  
  while(1);
}




