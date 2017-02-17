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

//Altitude variables
float ground_altitude;
float max_altitude;





//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////


float get_pressure();
float get_temperature();
float get_altitude();


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
	#define READ_FREQUENCY 250
	#define STABILIZATION_FACTOR 0.05

        
        
        float realtive_altitude = 99999; 
        

        unsigned char read_counter;
	while(realtive_altitude > STABILIZATION_FACTOR)
	{
          ground_altitude = get_altitude();
          
          read_counter = 0;
	  while(read_counter < READ_FREQUENCY)
          {           
            read_counter ++;
            get_altitude();            
            //Serial.print ("Temp: ");
            //Serial.print (get_temperature());      
            //Serial.print (", Press: ");
            //Serial.print (get_pressure());            
            //Serial.print (", Alt: ");
            //Serial.print (get_altitude());
            //Serial.print ("\n");            
          }	          
          realtive_altitude = ground_altitude - get_altitude();
          if(realtive_altitude < 0) realtive_altitude = realtive_altitude * -1;  // Absolute value         
	  //Serial.print("\nrealtive_altitude:");
	  //Serial.println(realtive_altitude);
          Serial.print (".");
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
    //Serial.print ("Last Temp: ");
    //Serial.println (last_temperature);
    delay(100);
  }
  
  //Wait until the pressure is not changing
  wait_for_barometer_stabilization();
  //when ready set ground altitudw
  ground_altitude = get_altitude();	
  
}



//////////////////////// TEMPERATURE FUNCTIONS  ////////////////////////////////////////////
float get_temperature()
{
  float temp_temperature = barometer.getTemperature(MS561101BA_OSR_4096);
  //delay(100);
  //Serial.print ("Readed Temp: ");
  //Serial.println (temp_temperature);
  // If impossible to read temperature, return last readed temperature
  if( temp_temperature ==NULL || temp_temperature < (-244.8) )  // -244.83 its an error output from barometer whenn reads anything
  {
   return last_temperature;
  }
  last_temperature = temp_temperature;
  return temp_temperature;
}



///////////////////////// ATLTITUDE FUNCTIONS /////////////////////////////////////////////////
float get_altitude() {
  float press =  get_pressure();
  float temp = get_temperature();
  //return (1.0f - pow(press/101325.0f, 0.190295f)) * 4433000.0f;
  
  float temp_altitude = ((pow((SEA_PRESSURE / press), 1/5.257) - 1.0) * (temp + 273.15)) / 0.0065;
  
  if(temp_altitude > max_altitude) max_altitude = temp_altitude;  // Set Max altitude when needed
  return temp_altitude;
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
  //Serial.print("\nReaded press: ");
  //Serial.println(temp_press);
  if(temp_press!=NULL) {
    push_pressure(temp_press);
  }
  return get_average(pressure_buffer, PRESSURE_BUFFER_SIZE);
  
}
