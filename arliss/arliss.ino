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
#define ALTITUDE_LAUNCH_DETECTION_THRESHOLD 1  //Relative altitude for detect launch
#define ALTITUDE_LNADING_DETECTION_THRESHOLD 1  //Relative altitude for detect landing



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
    // verify connection
    if(init_accelgyro() == EXIT_FAILURE) handle_error("Gyro connection failed");
    send_message("AccelGyro Ready");
  #endif
  
  send_message("All System Ready");
  current_rover_state = pre_launch;
  delay(1000);

}




void loop()
{
  // Execute current rover state corresponding routine
  (*rover_state_routines[current_rover_state])(); 
}




////////////////////////// GENERAL FUNCTIONS    /////////////////////////////////////////
int send_message(const char * message)
{
  pkg_counter++;
  #ifdef DEBUG
      Serial.print("pkg:");
      Serial.print(pkg_counter);
      Serial.print("\t$");
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


//Return SUCCESS if already passed the amount of seconds specified
int every_x_seconds(unsigned int seconds, unsigned long  *last_time_executed)
{
  if( ((seconds * 1000) + *last_time_executed) <= millis() ){
    *last_time_executed = millis();
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}


////////////////////////////////////////////////////////////////////////////////////////////
////////                      MODES OF OPERATION
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////// PRE LAUNCH FUNCTIONS    /////////////////////////////////////////
// During the pre launch: wait until launch detection
void *pre_launch_routine()
{
  send_message("Rove_status: pre_launch");

  unsigned long last_time_executed= millis();   //For time counting
  
  while(current_rover_state == pre_launch)
  {
    
    #ifdef DEBUG
      /*
      pkg_counter++;
      Serial.print("pkg:");
      Serial.print(pkg_counter);
      //print_barometer_data();
      print_accelgyro_data();
    */
    #endif
    
    // If Relative Altitude > ALTITUDE_LAUNCH_DETECTION_THRESHOLD, AND IN motion, Launch detection!!
    
    if( in_motion() && ((get_altitude() - ground_altitude) > ALTITUDE_LAUNCH_DETECTION_THRESHOLD) )
    {  
      send_message("Launched"); 
      current_rover_state = ascent; // End the pre_launch_routine
      break;
    }
    //Send a message every 3 sec
    if(every_x_seconds(3, &last_time_executed) == EXIT_SUCCESS) send_message("Waiting for launch");

  } 
}



////////////////////////// ASCENT FUNCTIONS    /////////////////////////////////////////

void *ascent_routine()
{
  send_message("Rove_status: ascent");
  unsigned long last_time_executed= millis();   //For time counting
  while(current_rover_state == ascent)
  {
    // If Relative Altitude < Max Altitude, Apoapsis detection!!
    if( ((get_altitude() - ground_altitude) < max_altitude))
    {  
      send_message("Apoapsis"); 
      current_rover_state = descent; // End the ascent_routine
      break;
    }
    //Send a message every 3 sec
    if(every_x_seconds(3, &last_time_executed) == EXIT_SUCCESS) send_message("Ascending");
  } 
  
  
  current_rover_state = descent; // End the ascent_routine

}



////////////////////////// DESCENT FUNCTIONS    /////////////////////////////////////////

void *descent_routine()
{
  send_message("Rove_status: descent");
  
  
  unsigned long last_time_executed= millis();   //For time counting
  
  while(current_rover_state == descent)
  {
    Serial.println(in_motion());
    // If Relative Altitude <= ALTITUDE_LNADING_DETECTION_THRESHOLD, AND NOT in motion, landing detection!!
    if(!in_motion() && ((get_altitude() - ground_altitude) <= ALTITUDE_LNADING_DETECTION_THRESHOLD))
    {  
      send_message("Landing"); 
      current_rover_state = navigation; // End the descent_routine
      break;
    }
    //Send a message every 3 sec
    if(every_x_seconds(3, &last_time_executed) == EXIT_SUCCESS) send_message("Descending");
  } 
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




