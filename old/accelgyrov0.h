//////////////////////////////////////////////////
// Gyro.h
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
#define DEBUG




//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////


MPU6050 accelgyro;
int16_t accel_x, accel_y, accel_z,  gyro_x, gyro_y, gyro_z;


//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////


void print_accelgyro_data()
{
    accelgyro.getMotion6(&accel_x, &accel_y, &accel_z,  &gyro_x, &gyro_y, &gyro_z);
    Serial.print("a/g:\t");
    Serial.print(accel_x); Serial.print("\t");
    Serial.print(accel_y); Serial.print("\t");
    Serial.print(accel_z); Serial.print("\t || ");
    Serial.print(gyro_x); Serial.print("\t");
    Serial.print(gyro_y); Serial.print("\t");
    Serial.println(gyro_z);
}




////////////////// SET UP FUNCTIONS ///////////////////////////////////////
int init_accelgyro()
{
  accelgyro.initialize();
  // verify connection
  if(accelgyro.testConnection() == 0) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}


void read_accelgyro()
{
  accelgyro.getMotion6(&accel_x, &accel_y, &accel_z,  &gyro_x, &gyro_y, &gyro_z);
}

////////////////// ACCELEROMETER FUNCTIONS ///////////////////////////////////////
//accelgyro.getAcceleration(&ax, &ay, &az);





////////////////// GYROSCOPE FUNCTIONS ///////////////////////////////////////


//accelgyro.getRotation(&gx, &gy, &gz);

