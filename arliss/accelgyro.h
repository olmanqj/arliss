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

#define MOTION_READS  20
#define IN_MOTION_BUFF_SIZE 10

#define MOTION_DETECTION_THRESHOLD 1
#define MOTION_DETECTION_DURATION 1
#define ZERO_MOTION_DETECTION_THRESHOLD 2
#define ZERO_MOTION_DETECTION_DURATION 2



//////////////////////////////////////////////////
//  GLOBAL VARIABLES
/////////////////////////////////////////////////
MPU6050 accelgyro;
Activites activiti;



unsigned char in_motion_buff[IN_MOTION_BUFF_SIZE];
unsigned char in_motion_buff_index=0;

//////////////////////////////////////////////////
//  FUNCTIONS
/////////////////////////////////////////////////

unsigned char in_motion();


/////////////////// GENERAL FUNCTION  //////////////////////////////

void print_accelgyro_data()
{
  Serial.print("In_motion: ");
  Serial.println(in_motion());
}



void push_motion_val(unsigned char val) {
  in_motion_buff[in_motion_buff_index] = val;
  in_motion_buff_index = (in_motion_buff_index + 1) % IN_MOTION_BUFF_SIZE;
}

float get_average(unsigned char * buff, unsigned char size) {
  float sum = 0.0;
  for(int i=0; i<size; i++) {
    sum += buff[i];
  }
  return sum / size;
}


////////////////// SET UP FUNCTIONS ///////////////////////////////////////
int init_accelgyro()
{
  if(!accelgyro.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G)) return EXIT_FAILURE;
  accelgyro.setAccelPowerOnDelay(MPU6050_DELAY_3MS);
  accelgyro.setIntFreeFallEnabled(false);  
  accelgyro.setIntZeroMotionEnabled(false);
  accelgyro.setIntMotionEnabled(false);
  accelgyro.setDHPFMode(MPU6050_DHPF_5HZ);
  accelgyro.setMotionDetectionThreshold( MOTION_DETECTION_THRESHOLD );
  accelgyro.setMotionDetectionDuration( MOTION_DETECTION_DURATION );
  accelgyro.setZeroMotionDetectionThreshold( ZERO_MOTION_DETECTION_THRESHOLD );
  accelgyro.setZeroMotionDetectionDuration( ZERO_MOTION_DETECTION_DURATION );	
  
  
  // populate in_motion_buff before starting 
  for(int i=0; i<IN_MOTION_BUFF_SIZE; i++) {
    in_motion_buff[i] = in_motion();
  }
  
  return EXIT_SUCCESS;
}




////////////////// ACCELEROMETER FUNCTIONS ///////////////////////////////////////

unsigned char in_motion()
{
  activiti = accelgyro.readActivites();
  push_motion_val(activiti.isActivity);
  if( get_average(in_motion_buff, IN_MOTION_BUFF_SIZE) < 0.01 ) return 0;
  return 1;
}
 





////////////////// GYROSCOPE FUNCTIONS ///////////////////////////////////////

