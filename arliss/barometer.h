//////////////////////////////////////////////////
// Barometer.h
//
// API
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
// For Barometer
MS561101BA barometer = MS561101BA();
float pressure_buffer[PRESSURE_BUFFER_SIZE];
float last_temperature;
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
	int read_frequency = 10;
	float stabilization_factor = 0.001;
	
        // Wait until read some data
        float temp_pressure = get_pressure();
        float temp_temperature = get_temperature();
        float temp_altitude = get_altitude(temp_pressure, temp_temperature);//<<<<<<<<<<<<<<<<<<<
       
       
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
            temp_temperature = get_temperature();
            read_counter ++;
            Serial.print ("Temp: ");
            Serial.print (temp_temperature);      
            Serial.print (", Press: ");
            Serial.print (temp_pressure);            
            Serial.print (", Alt: ");
            Serial.print (get_altitude(temp_pressure, temp_temperature));
            Serial.print ("\n");
            
          }	
          delta_pressure = abs(last_compared_pressure - temp_pressure);
	  Serial.print("\ndelta p:");
	  Serial.println(delta_pressure);

	}
}

void setup_barometer()
{
  barometer.init(MS561101BA_ADDR_CSB_LOW); //CSB pin is connected to GND (not even connected(?)) 
  delay(100);
 
  //Populate pressure_buffer before starting loop
  for(int i=0; i<PRESSURE_BUFFER_SIZE; i++) {
    
    float temp_press = barometer.getPressure(MS561101BA_OSR_4096);
    // If barometer read is NULL, read until is not NULL
    while(temp_press == NULL )
    {
      temp_press = barometer.getPressure(MS561101BA_OSR_4096);
    }    
    pressure_buffer[i] = temp_press;// barometer.getPressure(MS561101BA_OSR_4096);  
  }
  
  // Populate last readed temperature
  while(last_temperature==NULL || last_temperature == -244.83 )
  {
    last_temperature = barometer.getTemperature(MS561101BA_OSR_4096);
    Serial.print ("Last Temp: ");
    Serial.println (last_temperature);
    delay(100);
  }
  
  //Wait until the pressure is not changing
  wait_for_barometer_stabilization();
	
}



//////////////////////// TEMPERATURE FUNCTIONS  ////////////////////////////////////////////
float get_temperature()
{
  float temp_temperature = barometer.getTemperature(MS561101BA_OSR_4096);
  delay(100);
  //Serial.print ("Readed Temp: ");
  //Serial.println (temp_temperature);
  // If impossible to read temperature, return last readed temperature
  if( temp_temperature ==NULL || temp_temperature == -244.83 )
  {
   return last_temperature;
  }
  last_temperature = temp_temperature;
  return temp_temperature;
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
  //return barometer.getPressure(MS561101BA_OSR_4096);
  
  float temp_press = barometer.getPressure(MS561101BA_OSR_4096);
  if(temp_press!=NULL) {
    push_pressure(temp_press);
  }
  return get_average(pressure_buffer, PRESSURE_BUFFER_SIZE);
  
}
