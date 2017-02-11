//////////////////////////////////////////////////
// Barometer.h
//
//
//
//
// 
/////////////////////////////////////////////////




/////////////////////////////////////////////////
//  INCLUDES
////////////////////////////////////////////////


/////////////////////////////////////////////////
//  DEFINES
////////////////////////////////////////////////
//#define DEBUG

// For Barometer
#define PRESSURE_BUFFER_SIZE 32  
#define SEA_PRESSURE 1013.25



//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////
//Altitude variables
float relative_altitude;
float absolute_altitude;
float ground_altitude;
float max_altitude;

// For Barometer
MS561101BA barometer = MS561101BA();
float pressure_buffer[PRESSURE_BUFFER_SIZE];
int pressure_counter=0;
const float sea_press = 1013.25;
float press, temp;




//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////


void wait_for_barometer_stabilization()
{
	unsigned char read_frequency = 100;
	float stabilization_factor = 0.1;
	
	float delta_pressure;
	while(delta_pressure > stabilization_factor)
	{
		
	
	}
	

}

void setup_barometer()
{
 barometer.init(MS561101BA_ADDR_CSB_LOW); //CSB pin is connected to GND (not even connected(?)) 
  delay(100);
 
  // populate pressure_buffer before starting loop
  for(int i=0; i<PRESSURE_BUFFER_SIZE; i++) {
    pressure_buffer[i] = barometer.getPressure(MS561101BA_OSR_4096);
  }
  
  //wait_for_barometer_stabilization();
	
}





float get_altitude(float press, float temp) {
  //return (1.0f - pow(press/101325.0f, 0.190295f)) * 4433000.0f;
  return ((pow((SEA_PRESSURE / press), 1/5.257) - 1.0) * (temp + 273.15)) / 0.0065;
}



void push_pressure(float val) {
  pressure_buffer[pressure_counter] = val;
  pressure_counter = (pressure_counter + 1) % PRESSURE_BUFFER_SIZE;
}


float get_average(float * buff, int size) {
  float sum = 0.0;
  for(int i=0; i<size; i++) {
    sum += buff[i];
  }
  return sum / size;
}
