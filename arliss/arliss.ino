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
#include <MS561101BA.h> // For Barometer MS5611


#include "arliss.h"


/////////////////////////////////////////////////
//  DEFINES
////////////////////////////////////////////////
//#define DEBUG


#define MOVAVG_SIZE 32  // For Barometer





//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////
 int current_rover_state;     // Rover state: 0 = groud pre launch, 1 = launch, 


//Altitude variables
float relative_altitude;
float absolute_altitude;
float ground_altitude;
float max_altitude;

// For Barometer
MS561101BA barometer = MS561101BA();
float movavg_buff[MOVAVG_SIZE];
int movavg_i=0;
const float sea_press = 1013.25;
float press, temp;






//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  delay(1000);
  
  
  setup_barometer();
  
  current_rover_state = pre_launch;

}



void loop()
{
  Serial.print("Current rover state:");
  Serial.println(current_rover_state);
  
  
  ////////////////////////Barometro//////////////////////////
  Serial.print(" temp: ");
  float temperature = barometer.getTemperature(MS561101BA_OSR_4096);
  if(temperature) {
    temp = temperature;
  }
  Serial.print(temp);
  Serial.print(" degC pres: ");
  press = barometer.getPressure(MS561101BA_OSR_4096);
  if(press!=NULL) {
    pushAvg(press);
  }
  press = getAvg(movavg_buff, MOVAVG_SIZE);
  Serial.print(press);
  Serial.print(" mbar altitude: ");
  Serial.print(getAltitude(press, temp));
  Serial.println(" m");
  //delay(1000);
  //////////////////////////////////////////////////////
  

}






////////////////////////Barometro/////////////////////////////////////

void setup_barometer()
{
  barometer.init(MS561101BA_ADDR_CSB_LOW); //CSB pin is connected to GND (not even connected(?)) 
  delay(100);
  
  // populate movavg_buff before starting loop
  for(int i=0; i<MOVAVG_SIZE; i++) {
    movavg_buff[i] = barometer.getPressure(MS561101BA_OSR_4096);
  }
}




float getAltitude(float press, float temp) {
  //return (1.0f - pow(press/101325.0f, 0.190295f)) * 4433000.0f;
  return ((pow((sea_press / press), 1/5.257) - 1.0) * (temp + 273.15)) / 0.0065;
}

void pushAvg(float val) {
  movavg_buff[movavg_i] = val;
  movavg_i = (movavg_i + 1) % MOVAVG_SIZE;
}

float getAvg(float * buff, int size) {
  float sum = 0.0;
  for(int i=0; i<size; i++) {
    sum += buff[i];
  }
  return sum / size;
}
////////////////////////////////////////////////////////////////
