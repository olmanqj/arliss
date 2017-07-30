//////////////////////////////////////////////////
// Magnetometer.h
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

// For Magnetometer



//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////




HMC5883L compass;
MPU6050 mpu;

Vector norm;

float heading;

float declinationAngle;


//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////



int init_magnetometer()
{
  
  declinationAngle = (DECLINATION_DEG + ( DECLINATION_MIN / 60.0)) / (180 / M_PI);
  
   while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
    return EXIT_FAILURE;
  }

  mpu.setI2CMasterModeEnabled(false);
  mpu.setI2CBypassEnabled(true) ;
  mpu.setSleepEnabled(false);


  while (!compass.begin())
  {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    delay(500);
    return EXIT_FAILURE;
  }

  // Set measurement range
  compass.setRange(HMC5883L_RANGE_1_3GA);

  // Set measurement mode
  compass.setMeasurementMode(HMC5883L_CONTINOUS);

  // Set data rate
  compass.setDataRate(HMC5883L_DATARATE_30HZ);

  // Set number of samples averaged
  compass.setSamples(HMC5883L_SAMPLES_8);

  // Set calibration offset. See HMC5883L_calibration.ino
  compass.setOffset(0, 0); 
  
  return EXIT_SUCCESS;
}




float get_heading()
{
  norm = compass.readNormalize();

  // Calculate heading
  heading = atan2(norm.YAxis, norm.XAxis);


  heading += declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0)
  {
    heading += 2 * PI;
  }
 
  if (heading > 2 * PI)
  {
    heading -= 2 * PI;
  }

  // Convert to degrees
  //float headingDegrees = heading * 180/M_PI; 
  return heading * 180/M_PI; 
  
}



void print_magnetometer_data()
{
  float headingDegrees = get_heading();

  // Output
  Serial.print("deg: ");
  Serial.print(headingDegrees);
  Serial.println();

  delay(100);
}


