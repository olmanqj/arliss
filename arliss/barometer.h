//////////////////////////////////////////////////
// Barometer.h
//
// API
// float get_pressure()
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
// For Barometer
MS561101BA barometer = MS561101BA();
float pressure_buffer[PRESSURE_BUFFER_SIZE];
int pressure_counter=0;
const float sea_press = 1013.25;





//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////


float get_pressure();
float get_temperature();
float get_altitude(float press, float temp);


/////////////////// GENERAL FUNCTION  //////////////////////////////

float get_average(float * buff, int size) {
  float sum = 0.0;
  for(int i=0; i<size; i++) {
    sum += buff[i];
  }
  return sum / size;
}





////////////////// SET UP FUNCTIONS ///////////////////////////////////////

// Waits until the delta between two barometer reads (every read frequency) is less than the stabilization factor
void wait_for_barometer_stabilization()
{
	int read_frequency = 100;
	float stabilization_factor = 0.3;
	
        // Wait until read some data
        float temp_pressure = get_pressure();
        float temp_temperature = get_temperature();
        
        while(temp_pressure ==NULL)
        {
          Serial.print ("Press: ");
          Serial.print (temp_pressure);
          Serial.print (", Temp: ");
          Serial.print (temp_temperature);
          Serial.print ("\n");
          temp_pressure = get_pressure();
          temp_temperature = get_temperature();
        }

        //Wait until read some real data
        float last_compared_pressure;
	float delta_pressure = 99999;
        unsigned char read_counter;
	while(delta_pressure > stabilization_factor)
	{
          last_compared_pressure = get_pressure();
          read_counter = 0;
	  while(read_counter < read_frequency)
          {
            temp_pressure = get_pressure();
            read_counter ++;
          }	
          delta_pressure = abs(last_compared_pressure - temp_pressure);
	  Serial.print("delta p:");
	  Serial.println(delta_pressure);

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
  
  wait_for_barometer_stabilization();
	
}



//////////////////////// TEMPERATURE FUNCTIONS  ////////////////////////////////////////////

// Wrapper for getTemperature
float get_temperature()
{
  return barometer.getTemperature(MS561101BA_OSR_4096);
}



///////////////////////// ATLTITUDE FUNCTIONS /////////////////////////////////////////////////
float get_altitude(float press, float temp) {
  //return (1.0f - pow(press/101325.0f, 0.190295f)) * 4433000.0f;
  return ((pow((SEA_PRESSURE / press), 1/5.257) - 1.0) * (temp + 273.15)) / 0.0065;
}



//////////////////////////  PRESSURE FUNCTIONS  ///////////////////////////////////////////////

void push_pressure(float val) {
  pressure_buffer[pressure_counter] = val;
  pressure_counter = (pressure_counter + 1) % PRESSURE_BUFFER_SIZE;
}



float get_pressure()
{
  return barometer.getPressure(MS561101BA_OSR_4096);
  /*
  float temp_press = barometer.getPressure(MS561101BA_OSR_4096);
  if(temp_press!=NULL) {
    push_pressure(temp_press);
  }
  return get_average(pressure_buffer, PRESSURE_BUFFER_SIZE);
  */
}
