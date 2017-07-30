//////////////////////////////////////////////////
// Arliss.h
//
//
//
//
// by Olman D. Quiros Jimenez
/////////////////////////////////////////////////




/////////////////////////////////////////////////
//  DEF
////////////////////////////////////////////////

#define DEBUG

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
long pkg_counter = 0;

//For watchdog
unsigned long watchdog_threshold;


//////////////////////////////////////////////////
//  FUNCTIONS PROTOTYPES
/////////////////////////////////////////////////

int send_message(char * message);
void handle_error(const char * message);

// Definition of all state routines
void *pre_launch_routine();
void *ascent_routine();
void *descent_routine();
void *navigation_routine();
void *closing_up_routine();
void *end_navigation_routine();
// Array of all routines for the different rover_states
void* (*rover_state_routines[])() = {pre_launch_routine, ascent_routine, descent_routine, navigation_routine, closing_up_routine, end_navigation_routine}; 




//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////


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



void  set_watchdog_mins(float mins)
{
  watchdog_threshold = (unsigned long)((mins * 60000) + millis());
}



unsigned char check_watchdog()
{
  if( watchdog_threshold <= millis()  ) 
  {
    send_message("watchdog_activated");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

