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


#define PIN_1      0
#define PIN_2      1
#define PIN_ENA    2


//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////


int motor_left[3]; 
int motor_right[3]; 




//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////



// Setup motors
int  init_motors( char motor_left_pin1, char motor_left_pin2, char motor_left_ena, char motor_right_pin1, char motor_right_pin2, char motor_right_ena) 
{
  //Declarar los pines para el motor 1
   motor_left[PIN_1] = motor_left_pin1;
   motor_left[PIN_2] = motor_left_pin2;
   motor_left[PIN_ENA] = motor_left_ena;
   
   pinMode( motor_left[PIN_1], OUTPUT);
   pinMode( motor_left[PIN_2], OUTPUT);
   pinMode( motor_left[PIN_ENA], OUTPUT);
   
   
   //Declarar los pines para el motor 2
   motor_right[PIN_1] = motor_right_pin1;
   motor_right[PIN_2] = motor_right_pin2;
   motor_right[PIN_ENA] = motor_right_ena;
  
   pinMode( motor_right[0], OUTPUT);
   pinMode( motor_right[1] , OUTPUT);
   pinMode( motor_right[2], OUTPUT);
   
   
   // HIGH Enable Pins
   digitalWrite(motor_left[PIN_ENA], HIGH);
   digitalWrite(motor_right[PIN_ENA], HIGH);
   
   
   
   return EXIT_SUCCESS;
}



// Based on http://www.instructables.com/id/Arduino-Powered-Autonomous-Vehicle/
float calculate_turn( float current_heading, float target_heading )
{

    float turn = target_heading - current_heading;
    
    if (turn < -180) turn += 360;
    if (turn >  180) turn -= 360;
  

    if( abs(turn) <= TURN_THRESHOLD )
    {
      return 0;    // Go Straight
    } 
    else if (turn < 0)
    {
      return turn;  // Turn left
    }
    else if (turn > 0)
    {
      return turn;    // Turn right
    } 
    else
    {
      return 0;     //Go Straight
    }

}  




void motor_stop()
{
  digitalWrite(motor_left[0], LOW); 
  digitalWrite(motor_left[1], LOW); 
  
  digitalWrite(motor_right[0], LOW); 
  digitalWrite(motor_right[1], LOW);
  delay(25);
}

void drive_forward()
{
  digitalWrite(motor_left[0], HIGH); 
  digitalWrite(motor_left[1], LOW); 
  
  digitalWrite(motor_right[0], HIGH); 
  digitalWrite(motor_right[1], LOW); 
}

void drive_backward()
{
  digitalWrite(motor_left[0], LOW); 
  digitalWrite(motor_left[1], HIGH); 
  
  digitalWrite(motor_right[0], LOW); 
  digitalWrite(motor_right[1], HIGH); 
}

void turn_left()
{
  digitalWrite(motor_left[0], LOW); 
  digitalWrite(motor_left[1], HIGH); 
  
  digitalWrite(motor_right[0], HIGH); 
  digitalWrite(motor_right[1], LOW);
}


void turn_right()
{
  digitalWrite(motor_left[0], HIGH); 
  digitalWrite(motor_left[1], LOW); 
  
  digitalWrite(motor_right[0], LOW); 
  digitalWrite(motor_right[1], HIGH); 
}





// If way > 0 turn right, if way < 0 turn left
void motor_turn( float way)
{

  if( way == 0) return; 
  
  float turn_delay = abs(way)* 2 + TURN_DELAY_BASE;
  
  Serial.print("turn_delay:");
  Serial.println(turn_delay);
  
  
  if (way > 0)   // Turn left
  {
      turn_left();
      delay(turn_delay);
      motor_stop();
  }
  else if (way < 0)  // Turn right
  {
    turn_right();
    delay(turn_delay);
    motor_stop();
  } 

  return;
}








