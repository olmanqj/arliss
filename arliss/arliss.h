//////////////////////////////////////////////////
// Arliss.h
//
//
//
//
// 
/////////////////////////////////////////////////




/////////////////////////////////////////////////
//  DEF
////////////////////////////////////////////////

typedef enum {
    pre_launch,
    ascent,
    descent,
    navigation,
    closing_up,
    end_navigation
} ROVER_STATE;



//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////
unsigned char error_flag = 0;



//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////

// Definition of all state routines
void *pre_launch_routine();
void *ascent_routine();
void *descent_routine();
void *navigation_routine();
void *closing_up_routine();
void *end_navigation_routine();

// Array of all routines for the different rover_states
void* (*rover_state_routines[])() = {pre_launch_routine, ascent_routine, descent_routine, navigation_routine, closing_up_routine, end_navigation_routine}; 



