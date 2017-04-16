#include "freeram.h"
#include "mpu.h"
#include "I2Cdev.h"

int ret;
double mod;
void setup() {
    Fastwire::setup(400,0);
    Serial.begin(38400);
    ret = mympu_open(200);
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
     Serial.print(" RM: "); Serial.println(mod);
}

