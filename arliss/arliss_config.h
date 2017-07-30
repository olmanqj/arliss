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




//For GPS Operations
#define DESTINATION_LAT               9.961898
#define DESTINATION_LON               -84.065769 
#define DISTANCE_TO_DEST_THRESHOLD    2

// PINOUT
#define GPS_RX_PIN         2
#define GPS_TX_PIN         3



// Set declination angle on your location and fix heading
// You can find your declination on: http://magnetic-declination.com/
// (+) Positive or (-) for negative
// For Bytom / Poland declination angle is 4'26E (positive)
// For CR is  -1° 44' (negative)
// Formula: (deg + (min / 60.0)) / (180 / M_PI);
#define DECLINATION_DEG    1.0
#define DECLINATION_MIN    44.0
#define DECLINATION_SYMBOL  -




//For Barometer
#define ALTITUDE_LAUNCH_DETECTION_THRESHOLD 1    //Relative altitude for detect launch
#define APOAPSIS_DETECTION_THRESHOLD 2           //Threshold between relative altitude and max altitude 
#define ALTITUDE_LNADING_DETECTION_THRESHOLD 2   //Relative altitude for detect landing
#define DELAY_BEFOR_NAVIGATION_START 10000       //Time between descente ends and starts navigation



//For Watchdog
#define PRE_LAUNCH_WATCHDOG 30
#define ASCENT_WATCHDOG 30
#define DESCENT_WATCHDOG 30
#define CLOSING_UP_WATCHDOG 5
