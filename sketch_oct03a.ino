// Library for the servo motor
#include <Servo.h>

// Variable declaration
const int trigPin = 12; //ultrasonic sensor's trigger pin connection
const int echoPin = 11; //ultrasonic sensor's echo pin connection
const float speedOfSound = 767.3; // speed of sound in miles per hour
const float pingTime; // time taken to hit the target and back in microseconds
const int redLedPin = 4; // red led's pin connection
const int greenLedPin = 3; // green led's pin connection 
const int servoPin = 6; // servo motor's pin connection
const int buzzer = 8; // buzzer's pin connection 
const int pirPin = 9; // pir sensor's controller pin connection
float targetDistance;  // target distance variable for the ultrasonic sensor
int pirStat = 0; // pir sensor's status 

// Instance of the servo motor class
Servo myLock;

void setup(){
  Serial.begin(9600); // Establishing a connection to the serial monitor 

  // Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT); // setting trigger pin as output 
  pinMode(echoPin, INPUT); // setting echo pin as input

  // Led pins
  pinMode(redLedPin, OUTPUT); // setting red led pin as output
  pinMode(greenLedPin, OUTPUT); // setting green led pin as output

  // pir infrared sensor
  pinMode(pirPin, INPUT); // setting pir infrared sensor as input

  myLock.attach(servoPin); // connecting the servo pin to the servo object
  Serial.println("Starting the security alarm system"); // displays a message to the serial monitor
}

void loop(){
  // sending signal towards a target
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);

  // storing the time the signal travelled to the target and back
  pingTime = pulseIn(echoPin, HIGH);
  pingTime = pingTime/1000000; // converting the time in microseconds to seconds
  pingTime = pingTime/3600; // converting the time in seconds to hours
  
  targetDistance = speedOfSound*pingTime/2; // calculating the distance to the target and back
  targetDistance = targetDistance/2; // calculating the distance to the target only
  targetDistance = targetDistance*63360; // converting the distance in miles to inches

  Serial.println(targetDistance); // displaying the distance to the serial monitor
  delay(100); // pausing the program running

  // checking the distance between the ultrasonic sensor and target and locking the door or opening it depending on the outcome
  if(targetDistance < 20){
    digitalWrite(redLedPin, HIGH); // turning on the red led
    digitalWrite(greenLedPin, LOW); // turning off the green led
    delayMicroseconds(2); // pausing
    myLock.write(160); // turning the servo motor 160 degree clockwise
    delay(100); // pausig
    Serial.println("Door Locked"); // displaying "Door Locked" on serial monitor 
  }else{
    digitalWrite(redLedPin, LOW); // turning off the red led
    digitalWrite(greenLedPin, HIGH); // turning on the green led
    delayMicroseconds(2); // pausing
    myLock.write(20); // turning the servo motor 20 degree anticlockwise
    delay(100); // pausing 
    Serial.println("Door Opened"); // displaying "Door Opened" on serial monitor
  }
  
  pirStat  = digitalRead(pirPin); //reading the status of the pir infrared sensor

  // checking the value obtained from the reading against posible outcomes
  if(pirStat == HIGH){
    Serial.println("Motion detected in the house"); // displays "Motion detected in the house" on the serial monitor
    tone(buzzer, 1000); // sets the buzzer ringing
    delayMicroseconds(100); // pausing
    noTone(0); // stop buzzer
  }else{
    Serial.println("There's no one in the house at the moment"); // displays "There's no one in the house at the moment" on the serial monitor
    noTone(0); // stop buzzer
    delayMicroseconds(5); // pausing
  }
}
