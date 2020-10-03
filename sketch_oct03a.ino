int pirPin = 2; // variable to hold pir sensor's pin 
//int redLedPin = 13; // variable to hold red led pin
int pirStat = 0; // variable to store pir sensor's status
int trigPin = 12; //variable to hold ultrasonic sensor's trigger pin
int echoPin = 11; //variable to hold ultrasonic sensor's echo pin
float speedOfSound = 767.3; // variable to hold the speed of sound in miles per hour
float targetDistance; // variable to hold target distance of the ultrasonic sensor
float pingTime; // variable to hold the time the signal moves to hit target and back
int redLedPin = 6;
int greenLedPin = 3; 

void setup(){
  Serial.begin(9600); 
  pinMode(redLedPin, OUTPUT); 
  pinMode(pirPin,INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //new pin mmodes
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  Serial.println("Starting the security alarm system");
}

void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);

  pingTime = pulseIn(echoPin, HIGH);
  pingTime = pingTime/1000000;
  pingTime = pingTime/3600;
  
  targetDistance = speedOfSound*pingTime/2;
  targetDistance = targetDistance/2;
  targetDistance = targetDistance*63360;

  Serial.println(targetDistance);
  delay(2000);

  if(targetDistance < 20){
    digitalWrite(redLedPin, HIGH); 
    digitalWrite(greenLdPin, LOW); 
  }else{
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
  }
  
//  pirStat = digitalRead(pirPin);
//  if(pirStat == HIGH){
//    Serial.println("Motion detected");
//    digitalWrite(redLedPin, LOW);
//    delay(1000);
//  }
//  else{
//    Serial.println("No motion detected");
//    digitalWrite(redLedPin, LOW);
//    delay(1000);
//  }
}
