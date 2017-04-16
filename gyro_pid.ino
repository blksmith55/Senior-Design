#include "freeram.h"
#include "mpu.h"
#include "I2Cdev.h"
#include <PID_v1.h>

//need output pin
int ret;
double mod, Setpoint, Input, Output;
double Kp=2, Ki=0, Kd=1; //tuning parameters
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
    Fastwire::setup(400,0);
    Serial.begin(38400);
    ret = mympu_open(200);
    Input = 0;
    Setpoint = 0;
    myPID.SetMode(AUTOMATIC);
}
unsigned int c = 0; //cumulative number of successful MPU/DMP reads
void loop() {
    ret = mympu_update();
    if (mympu.ypr[2] < 0){
        mod = mympu.ypr[2] + 180.0;
     }
     else if (mympu.ypr[2] > 0){
        mod = mympu.ypr[2] - 180.0;
     }
     delay(1);
//      Serial.print(" R: "); Serial.print(mympu.ypr[2]);
     Serial.print(" RM: "); Serial.print(mod);
// PID functions
  if (mod < 0){  //if right side is lower
    Input = mod;
    myPID.Compute();
    Serial.print(" PID1: "); Serial.println(Output);
    //output PID -> slow down other motor
    //output PID -> 255 - Output to pwm for other motor
  }
  else if (mod >0 ){ //if left side is lower
    Input = -mod;
    myPID.Compute();
    Serial.print(" PID2: "); Serial.println(Output);
  }
  
  //write so if mod is negative, controls one motor
  //if positive, controls other motor
}

