/*
DC motor library for Arduino

Taken from: https://www.engineersgarage.com/contribution/arduino-library-dc-motor-control

Contributor: AM Bhatt

Any attribution to the author


This library is used to control DC motors. It can:

·         control its speed from 0 to 100% and its direction

·         rotate motor forward and reverse at set speed 

·         start or stop the motor as well as provides DC BREAK for instant STOP 

One has to select arduino pins for the motor then start rotating motor using given library functions

*/

#ifndef DC_Motor_h

#define DC_Motor_h

 

#include "Arduino.h"



 

class DC_Motor
{ 

    private:

            int pin_1, pin_2, motor_speed, dir_flag;

    public:

    DC_Motor(int pin1,int pin2);

    DC_Motor(int pin1,int pin2,int speed_flag);

    void forward(void);

    void forward_with_set_speed(void);

    void reverse(void);

    void reverse_with_set_speed(void);

    void run_motor(int dir,int speed);

    void set_speed(int speed);  

    void start_motor(int dir);

    void jogg_full_speed(int dir);

    void stop_motor(void);

    void dc_break(void); 

    void motor_speed_zero(void); 

    void soft_start(int dir,int speed,int time_int_sec);

    void smooth_stop(int time_int_sec);

    void jogg_set_speed(int dir,int speed);

  };

#endif
