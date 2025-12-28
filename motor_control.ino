#include <IBusBM.h>

//OUTPUT pins 
#define coil1 27
#define coil2 26
#define PWM_coil 12
#define brush1 25
#define brush2 33
#define PWM_brush 14

//PWM parameters
#define PWM_res  8
#define PWM_freq  10000 

IBusBM IBus;    // IBus object

void setup() {
  IBus.begin(Serial2,1);
  Serial.begin(115200);

  //Motor direction set pins
  pinMode(coil1, OUTPUT);
  pinMode(coil2, OUTPUT);
  pinMode(brush1, OUTPUT);
  pinMode(brush2, OUTPUT);
  digitalWrite(coil1, HIGH);
  digitalWrite(coil2, LOW);
  digitalWrite(brush1, HIGH);
  digitalWrite(brush2, LOW);

  //PWM PIN SETUP
  ledcAttachPin(PWM_coil, 0);
  ledcSetup(0, PWM_freq, PWM_res);
  ledcAttachPin(PWM_brush, 1);
  ledcSetup(1, PWM_freq, PWM_res);

}

void loop() {
  int val;
  int duty;
  int duty_brush;
  int duty_coil;
  

  //Reading throttle from reciever and calculating duty cycle
  val = IBus.readChannel(2);
  duty = (val-1000)/10;
  if (duty > 2) {
    duty_brush = 10 + 70*duty/100;
    duty_coil = 100 - duty_brush;
  }
  else{
    duty_brush = 0;
    duty_coil = 0;
  }
  //Assigning duty cycle to output pwm pins
  ledcWrite(0, duty_coil*255/100);
  ledcWrite(1, duty_brush*255/100);

  //Direction of Motor
  if (IBus.readChannel(5)>1500){
    digitalWrite(brush1, LOW);
    digitalWrite(brush2, HIGH);
  }else{
    digitalWrite(brush1, HIGH);
    digitalWrite(brush2, LOW);
  }
  
}


