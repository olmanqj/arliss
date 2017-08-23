/////////////////////////////////////////////////                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               //////////////////////////////////////////////////
// Arliss.ino
//
//
//
//
// by Olman D. Quiros Jimenez
/////////////////////////////////////////////////



/////////////////////////////////////////////////
//  DEFINES
////////////////////////////////////////////////

// PINOUT
#define READY_PIN          8


//#define GPS_RX_PIN         12
//#define GPS_TX_PIN         13

// Motor_L pins: 5,6
#define MOTOR_L_PIN_A      6
#define MOTOR_L_PIN_B      5
#define MOTOR_L_PIN_ENA    NULL

//Motor_R pins: 9, 10
#define MOTOR_R_PIN_A      10
#define MOTOR_R_PIN_B      9
#define MOTOR_R_PIN_ENA    NULL

#define SOLENOID_PIN_A      11
#define SOLENOID_PIN_B      12



// For Motor Driver
#define TURN_THRESHOLD    20
#define TURN_DELAY_BASE   200


//For GPS Operations

#define DESTINATION_LAT               9.854892
#define DESTINATION_LON               -83.907433

#define DISTANCE_TO_DEST_THRESHOLD    1
// Set declination angle on your location and fix heading
// You can find your declination on: http://magnetic-declination.com/
// (+) Positive or (-) for negative
// For Bytom / Poland declination angle is 4'26E (positive)
// For CR is  -1° 44' (negative)
// Formula: (deg + (min / 60.0)) / (180 / M_PI);
#define DECLINATION_DEG              1.0
#define DECLINATION_MIN              44.0
#define DECLINATION_SYMBOL           -




//For Barometer
#define ALTITUDE_LAUNCH_DETECTION_THRESHOLD 2    //Relative altitude for detect launch
#define APOAPSIS_DETECTION_THRESHOLD 2           //Threshold between relative altitude and max altitude 
#define ALTITUDE_LNADING_DETECTION_THRESHOLD 2   //Relative altitude for detect landing
#define DELAY_BEFOR_NAVIGATION_START 30000       //Time between descente ends and starts navigation



//For Watchdog
#define PRE_LAUNCH_WATCHDOG 30
#define ASCENT_WATCHDOG 30
#define DESCENT_WATCHDOG 30
#define CLOSING_UP_WATCHDOG 5

