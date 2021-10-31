/*This coding is developed by Mudit Lal .
 View our video at this link
 https://www.youtube.com/watch?v=JXEivVXzFtw and the tutorial is - http://www.instructables.com/id/Obstacle-Avoiding-Robot-Motor-Shield/*/ 
/* ----------------------------------------------------Setting up the sensor and the motor shield----------------------------------------------------*/
#define trigPin 8//Attach Trig to port 8
#define echoPin 7//Attach Echo to port 7
#include <AFMotor.h>//Make sure you install the directory
AF_DCMotor motor1(1,MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);

/* ----------------------------------------------------------------Setting up the motors-------------------------------------------------------------*/ 

void setup() {
  Serial.begin(9600); 
   pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  motor1.setSpeed(150);//Sets up the speed of motors
motor2.setSpeed (150);  
}
 
void loop() {

/* -------------------------------------------------------This process is continously repeated-------------------------------------------------------*/ 
   
   long duration, distance; 
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 20)//If an object is in distance of 20cm 
 
 /* ---------------------------------------------------This will happen when an object is detected---------------------------------------------------*/ 

 {   
    motor1.run(FORWARD); //The robot turns
    motor2.run (BACKWARD);

}
  
  /* -------------------------------------------------------If there is nothing in front of it--------------------------------------------------------*/ 
 
  else {
delay (2);
   motor1.run(FORWARD); // If there is nothing then the robot will keep moving forward
    motor2.run(FORWARD);  
  }  
  
   
 
}

