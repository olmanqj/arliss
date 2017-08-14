/////////////////////////////////////////////////
// motoroto.h
//
// API
// 
//
//
// by Olman D. Quiros Jimenez
/////////////////////////////////////////////////




/////////////////////////////////////////////////
//  INCLUDES
////////////////////////////////////////////////



/////////////////////////////////////////////////
//  DEFINES
////////////////////////////////////////////////
#define DEBUG



#define TURN_THRESHOLD 5



//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////







//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////



// Based on http://www.instructables.com/id/Arduino-Powered-Autonomous-Vehicle/
float calculate_turn( float current_heading, float target_heading )
{

    float turn = target_heading - current_heading;
    
    if (turn < -180) turn += 360;
    if (turn >  180) turn -= 360;
  

    if( abs(turn) <= TURN_THRESHOLD )
    {
      turn = 0;
      #ifdef DEBUG
      Serial.println("straight"); 
      #endif
    } 
    else if (turn < 0)
    {
      #ifdef DEBUG
      Serial.println("left");  
      #endif
    }

    else if (turn > 0)
      Serial.println("right");  
    else
      Serial.println("straight");  

    Serial.print("turn:");
    Serial.println(turn);    
    return turn; 
}  
