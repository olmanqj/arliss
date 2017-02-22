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

int16_t ax, ay, az;
int16_t gx, gy, gz;



//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////


void print_gyro_data()
{

    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    // display tab-separated accel/gyro x/y/z values
    Serial.print("a/g:\t");
    Serial.print(ax); Serial.print("\t");
    Serial.print(ay); Serial.print("\t");
    Serial.print(az); Serial.print("\t");
    Serial.print(gx); Serial.print("\t");
    Serial.print(gy); Serial.print("\t");
    Serial.println(gz);
}




////////////////// SET UP FUNCTIONS ///////////////////////////////////////
int init_accelgyro()
{
  accelgyro.initialize();
  // verify connection
  if(accelgyro.testConnection() == 0) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
