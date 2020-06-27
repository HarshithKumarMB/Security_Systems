#include<AFMotor.h>
#include"Servo.h"
#include <afstandssensor.h>
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
int a =0;
const int get_info = 8;
AfstandsSensor afstandssensor(10, 11);
Servo my_servo;
void setup() {
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  my_servo.attach(9);
  pinMode(get_info, INPUT);
}

void loop() {
  if(get_info == LOW){
  if(afstandssensor.afstandCM()<30)
  {
     motor1.run(FORWARD);
     motor2.run(BACKWARD);
     motor3.run(FORWARD);
     motor4.run(BACKWARD);
     my_servo.write(0);
     while(a != 360){
      
     
     
     my_servo.write(a);
     a = a+30;
     
     delay(200);
     }
     a=0;
  }
  else
  {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
  }
  delay(10);

}
}
