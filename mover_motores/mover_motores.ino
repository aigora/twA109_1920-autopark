#include <AFMotor.h>
AF_DCMotor Motor1(1);
AF_DCMotor Motor2(2);
AF_DCMotor Motor3(3);
AF_DCMotor Motor4(4);

void setup()
   {        Motor1.run(RELEASE);
            Motor2.run(RELEASE);
            Motor3.run(RELEASE);
            Motor14run(RELEASE);
   }

void loop()
   {   Motor1.run(FORWARD); 
       Motor2.run(FORWARD);
       Motor3.run(FORWARD); 
       Motor4.run(FORWARD);

       Motor1.setSpeed(200);
       Motor2.setSpeed(200);
       Motor3.setSpeed(200);
       Motor4.setSpeed(200);
       
   }
