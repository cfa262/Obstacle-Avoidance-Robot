
#include <Servo.h> //import servo library
#include <AFMotor.h> //import your motor shield library

// define the pins of first sensor
#define rightTrigPin 13
#define rightEchoPin 12
#define trigPin 10
#define echoPin 9
#define leftTrigPin 15
#define leftEchoPin 16

// initiate servo and pins
Servo calvin_servo;
//const int goPin = 12;
//const int stopPin = 2;

const int leftFwd = 7;
const int leftRev = 6;
const int rightFwd = 5;
const int rightRev = 4;
const int leftE = 11;
const int rightE = 3;

// car movement methods
void startCar() {
  analogWrite(leftE, 145);
  analogWrite(rightE, 130);
  digitalWrite(leftFwd, HIGH);
  digitalWrite(leftRev, LOW);
  digitalWrite(rightFwd, HIGH);
  digitalWrite(rightRev, LOW);
  
}
void stopCar() {
  analogWrite(leftE, 0);
  analogWrite(rightE, 0);
  digitalWrite(leftFwd, LOW);
  digitalWrite(leftRev, LOW);
  digitalWrite(rightFwd, LOW);
  digitalWrite(rightRev, LOW);
}

void leftTurn() {
  analogWrite(leftE, 150);
  analogWrite(rightE, 180);
  digitalWrite(leftFwd, LOW);
  digitalWrite(leftRev, HIGH);
  digitalWrite(rightFwd, HIGH);
  digitalWrite(rightRev, LOW);
}
void rightTurn() {
  analogWrite(leftE, 180);
  analogWrite(rightE, 150);
  digitalWrite(leftFwd, HIGH);
  digitalWrite(leftRev, LOW);
  digitalWrite(rightFwd, LOW);
  digitalWrite(rightRev, HIGH);
}
void turnAround() {
  analogWrite(leftE, 215);
  analogWrite(rightE, 210);
  digitalWrite(leftFwd, HIGH);
  digitalWrite(leftRev, LOW);
  digitalWrite(rightFwd, LOW);
  digitalWrite(rightRev, HIGH);
}

long activateSensor() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5); //this delay is required too
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long range = (duration / 2) / (29.1);
  return range;
}

  long activateLeftSensor(){
    digitalWrite(leftTrigPin, LOW);
    delayMicroseconds(1); // delays are required for a succesful sensor operation.
    digitalWrite(leftTrigPin, HIGH);
    delayMicroseconds(5); //this delay is required too
    digitalWrite(leftTrigPin, LOW);
    long duration = pulseIn(leftEchoPin, HIGH);
    long range = (duration/2) / (29.1);
    return range;
  }

  long activateRightSensor(){
    digitalWrite(rightTrigPin, LOW);
    delayMicroseconds(1); // delays are required for a succesful sensor operation.
    digitalWrite(rightTrigPin, HIGH);
    delayMicroseconds(10); //this delay is required too
    digitalWrite(rightTrigPin, LOW);
    long duration = pulseIn(rightEchoPin, HIGH);
    long range = (duration/2) / (29.1);
    return range;
  }


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // begin serial communitication
  Serial.println("Motor test!");
  pinMode(trigPin, OUTPUT);// sets the trig pin to output (Send sound waves)
  pinMode(echoPin, INPUT);// sets the echo pin to input (Recieve sound waves)
  pinMode(leftTrigPin, OUTPUT);// sets the trig pin to output (Send sound waves)
  pinMode(leftEchoPin, INPUT);// sets the echo pin to input (Recieve sound waves)
  pinMode(rightTrigPin, OUTPUT);// sets the trig pin to output (Send sound waves)
  pinMode(rightEchoPin, INPUT);// sets the echo pin to input (Recieve sound waves)
  pinMode(leftFwd, OUTPUT);
  pinMode(leftRev, OUTPUT);
  pinMode(rightFwd, OUTPUT);
  pinMode(rightRev, OUTPUT);
  pinMode(leftE, OUTPUT);
  pinMode(rightE, OUTPUT);
  
  int servoPin = 8; //sets the pin
  calvin_servo.attach(servoPin); //sets the servo
  //pinMode(goPin, OUTPUT);
  //pinMode(stopPin, OUTPUT);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  calvin_servo.write(80); //sets ultrasonic sensor to the middle
  long distance = activateSensor(); 
  delay(10);
  long leftDistance = activateLeftSensor();
  delay(10);
  long rightDistance = activateRightSensor();
  delay(10);
  
  //if there's an obstacle 20 centimers, straight ahead, do the following:
  if (distance < 15) {
    
    Serial.println ("Close Obstacle detected!" );
    Serial.println ("Obstacle Details:");
    Serial.print ("Distance From Robot is " );
    Serial.print (distance);
    Serial.println ( " Centimeters! Will now find a way to turn");//print out the distance in centimeters.

    stopCar();
    delay(500);
    calvin_servo.write(0);
    delay(500);
    distance = activateSensor();
    Serial.print("DISTANCE IS ");
    Serial.print(distance);
    Serial.println(" Centimeters");
    delay(500);
    if(distance > 20){
      Serial.println ("TURNING RIGHT");
      rightTurn();
      //delay(1000);
    }else{
      delay(500);
      calvin_servo.write(40);
      delay(500);
      calvin_servo.write(80);
      delay(500);
      calvin_servo.write(120);
      delay(500);
      calvin_servo.write(170);
      delay(500);
      distance = activateSensor();
      Serial.print("DISTANCE IS ");
      Serial.print(distance);
      Serial.println(" Centimeters");
      delay(500);
      if(distance > 20){
        delay(500);
        Serial.println("TURNING LEFT");
        leftTurn();
        //delay(1000);
      }else{ //bot will turn around if no right or left turns available
        delay(500);
        Serial.println("TURNING AROUND");
        turnAround();
        //delay(1000);
      }
    }
    delay(500);
  } 
  //adjusts bot to turn slight right
  else if(leftDistance < 6 && leftDistance > 0){
    
    Serial.println ("Obstacle detected on LEFT!" );
    Serial.print ("Distance From Robot is " );
    Serial.print (leftDistance);
    Serial.println ( " Centimeters!");
    
    //move a bit right
    analogWrite(leftE, 200);
    analogWrite(rightE, 200);
    digitalWrite(leftFwd, HIGH);
    digitalWrite(leftRev, LOW);
    digitalWrite(rightFwd, LOW);
    digitalWrite(rightRev, HIGH);
    delay(10);
    
  }
  //adjusts bot to turn slight left
  else if(rightDistance < 6 && rightDistance > 0){
    
    Serial.println ("Obstacle detected on RIGHT!" );
    Serial.print ("Distance From Robot is " );
    Serial.print (rightDistance);
    Serial.println ( " Centimeters!");
    
    //moving a bit left
    analogWrite(leftE, 200);
    analogWrite(rightE, 200);
    digitalWrite(leftFwd, LOW);
    digitalWrite(leftRev, HIGH);
    digitalWrite(rightFwd, HIGH);
    digitalWrite(rightRev, LOW);
    delay(10);
  }
  // procede, no obstacle ahead
  else {
    Serial.println ("No obstacle detected. going forward");
    startCar();
    //calvin_servo.write(140); //will move the servo
    delay(100);
    //calvin_servo.write(40); //will move the servo
  }
}




