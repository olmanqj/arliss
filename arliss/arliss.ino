/////////////////////////////////////////////////                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               //////////////////////////////////////////////////
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

#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  #define FEATHER
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif


//For IMU Sensor
#include <Wire.h>
#ifndef FEATHER
#include <I2Cdev.h>
#include <SoftwareSerial.h>
#endif

//Personal libraries
#include "arliss_config.h"
#include "arliss.h"


//For Barometer MS5611
#include "MS5611.h" 
#include "barometer.h"

//For GYRO MPU6050
#include "MPU6050.h"
#include "accelgyro.h"

//For Magnetometer HMC5883L
#include <HMC5883L.h>
#include <MPU6050.h>
#include "magnetometer.h"

// For GPS
#include "TinyGPS++.h"
#include "gps.h"

// For Motors
#include "motoroto.h" 


/////////////////////////////////////////////////
//  DEFINES
////////////////////////////////////////////////
// For Debugging
#define DEBUG
#define BAROMETER
#define ACCELGYRO
#define MAGNETOMETER
#define GPS
#define MOTORS


//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////
ROVER_STATE current_rover_state;     // Rover state: 0 = groud pre launch, 1 = launch, 




//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////


void setup()
{
  Serial.begin(9600);
  #ifdef DEBUG
    Serial.print("\n--------------------------------\Starting System!!\n");
  #endif

  
  // Turn On Starting_Pin
  pinMode( 13, OUTPUT);
  digitalWrite(13, HIGH);

  
  Wire.begin();
  
  delay(50);
   
  
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
  
  
  // Initialize Magnetometer  
  #ifdef MAGNETOMETER
    send_message("Initializing Magnetometer");
    // verify connection
    if(init_magnetometer() == EXIT_FAILURE) handle_error("Magnetometer connection failed");
    send_message("Magnetometer Ready");
  #endif
  
   // Initialize GPS  
  #ifdef GPS
    send_message("Initializing GPS");
    // verify connection
    if(init_gps( DESTINATION_LAT, DESTINATION_LON) == EXIT_FAILURE) handle_error("GPS connection failed");
    send_message("GPS Ready");
  #endif
  
  
  
  // Init Motors
   #ifdef MOTORS
    send_message("Initializing Motors");
    init_motors( MOTOR_L_PIN_A, MOTOR_L_PIN_B, MOTOR_L_PIN_ENA, MOTOR_R_PIN_A, MOTOR_R_PIN_B, MOTOR_R_PIN_ENA); 
    init_solenoid(SOLENOID_PIN_A, SOLENOID_PIN_B);
    send_message("Motors Ready");
  #endif
  
  
  send_message("All Systems Ready");

  // Turn Off Starting_Pin
  pinMode( 13, OUTPUT);
  digitalWrite(13, LOW);


  // Turn On Ready_Pin
  pinMode( READY_PIN, OUTPUT);
  digitalWrite(READY_PIN, HIGH);
  
  current_rover_state = pre_launch;
}




void loop()
{
  // Execute current rover state corresponding routine
  (*rover_state_routines[current_rover_state])(); 
}





////////////////////////////////////////////////////////////////////////////////////////////
////////                      MODES OF OPERATION
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////// PRE LAUNCH FUNCTIONS    /////////////////////////////////////////
// During the pre launch: wait until launch detection
void *pre_launch_routine()
{
  send_message("Rove_status: pre_launch");
  set_watchdog_mins(PRE_LAUNCH_WATCHDOG);
  
  unsigned long last_time_executed= millis();   //For time counting
  while(current_rover_state == pre_launch)
  {
    // If Relative Altitude > ALTITUDE_LAUNCH_DETECTION_THRESHOLD, AND IN motion, Launch detection!! 
    if( in_motion() && ( get_relative_altitude() > ALTITUDE_LAUNCH_DETECTION_THRESHOLD) )
    {  
      send_message("Launched"); 
      current_rover_state = ascent; // End the pre_launch_routine
      break;
    }
    //Send a message every 3 sec
    if(every_x_seconds(3, &last_time_executed) == EXIT_SUCCESS) send_message("Waiting for launch");

    
    // Check watchdog termination
    if(check_watchdog() == EXIT_FAILURE) current_rover_state = ascent;
  } 
}



////////////////////////// ASCENT FUNCTIONS    /////////////////////////////////////////

void *ascent_routine()
{
  send_message("Rove_status: ascent");
  unsigned long last_time_executed= millis();   //For time counting
  while(current_rover_state == ascent)
  {    
    // If Relative Altitude < Max relative Altitude, Apoapsis detection!!
    if( (get_relative_altitude() + APOAPSIS_DETECTION_THRESHOLD)  < max_relative_altitude)
    {  
      send_message("Apoapsis"); 
      current_rover_state = descent; // End the ascent_routine
      break;
    }

    //Send a message every 3 sec
    if(every_x_seconds(3, &last_time_executed) == EXIT_SUCCESS) send_message("Ascending");
  } 
}



////////////////////////// DESCENT FUNCTIONS    /////////////////////////////////////////

void *descent_routine()
{
  send_message("Rove_status: descent");
  unsigned long last_time_executed= millis();   //For time counting
  while(current_rover_state == descent)
  {
    // If Relative Altitude <= ALTITUDE_LNADING_DETECTION_THRESHOLD, AND NOT in motion, landing detection!!
    if(!in_motion() && (get_relative_altitude() < ALTITUDE_LNADING_DETECTION_THRESHOLD))
    {  
      send_message("Landing"); 
      delay(DELAY_BEFOR_NAVIGATION_START); //Wait some seconds before navigation begins, for ensure landing  
      current_rover_state = navigation; // End the descent_routine
      break;
    }

    //Send a message every 3 sec
    if(every_x_seconds(3, &last_time_executed) == EXIT_SUCCESS) send_message("Descending");
  } 
}



////////////////////////// NAVIGATION FUNCTIONS    /////////////////////////////////////////

void detach_parachute()
{
  send_message("Detaching parachute");

  int i = 3;
  while(i--)
  {
    solenoid_open();
    gps_delay(1000);
    solenoid_close();
    
    gps_delay(500);
    
    solenoid_open();
    gps_delay(1000);
  
    motor_forward();
    gps_delay(4000);
    solenoid_close();
    motor_stop();
  }
  solenoid_close();
  
  gps_delay(1000);  //Wait some seconds for ensure parachute detaching
}



void *navigation_routine()
{
  send_message("Rove_status: navigation");
   detach_parachute();
  
  float current_lat, current_lon;
  float turn;
  float rover_heading;
  float distance; // Distance to destination
  
  
  //while(1)
  while( ( distance = get_distance_to_dest()) >  DISTANCE_TO_DEST_THRESHOLD)
  {
    
    Serial.print( "| Dist:" );
    Serial.print( distance );
    
    
    Serial.print( "| Dest heading:" );
    get_course_to_dest();
    Serial.print( course_to_dest );
  
    Serial.print("| current heading: ");
    rover_heading = get_heading() ;
    Serial.print( rover_heading );
    
    Serial.print("| turn: ");
    turn = calculate_turn( rover_heading, course_to_dest);
    Serial.println(turn);
    
    while (turn !=  0)
    {
      motor_turn(turn);
      // Refresh turn
      turn = calculate_turn( get_heading(), get_course_to_dest());
      gps_delay(100);
    }
    
    // If no turn is necessary, go foreward
    motor_forward();
  

  }
  
  // When reached GPS point, stop
  motor_stop();
  
  current_rover_state = closing_up;
}




////////////////////////// CLOSING UP FUNCTIONS    /////////////////////////////////////////

void *closing_up_routine()
{
  send_message("Rove_status: closing_up");

  motor_forward();
  delay(3000);
  
  current_rover_state = end_navigation;
}



////////////////////////// END NAVIGATION FUNCTIONS    ////////////////////////////////////////
void *end_navigation_routine()
{
  send_message("Rove_status: end_navigation");
  
  send_message("Ended");
  
  while(1);
}




