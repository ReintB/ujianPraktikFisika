#include <Servo.h>
Servo servo;
int sensor_pin = 4;
int servo_pin = 5;
int val;
void setup(){
  pinMode(sensor_pin,INPUT);
  servo.attach(servo_pin);  
}

void loop(){
  val = digitalRead(sensor_pin);

  if (val==0)
  {servo.write(0);
   delay(1000);
  }
  if (val==1)
  {servo.write(180);
    }
}