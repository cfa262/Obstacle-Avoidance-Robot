
#include <Servo.h> //import servo library
#include <AFMotor.h> //import your motor shield library
#define trigPin 7 // define the pins of first sensor
#define echoPin 6 
#define trigPin_2 5 // define the pins on second sensor
#define echoPin_2 4

Servo calvin;
int leftFwd = 8;
int leftRev = 9; 
int rightFwd = 10;
int rightRev = 11;

void startCar(){
  digitalWrite(leftFwd, HIGH);
  digitalWrite(leftRev, LOW);
  digitalWrite(rightFwd, HIGH);
  digitalWrite(rightRev, LOW);
  
}
void stopCar(){
  digitalWrite(leftFwd, LOW);
  digitalWrite(leftRev, LOW);
  digitalWrite(rightFwd, LOW);
  digitalWrite(rightRev, LOW);
  
}
void leftTurn(){
  digitalWrite(leftFwd, LOW);
  digitalWrite(leftRev, HIGH);
  digitalWrite(rightFwd, HIGH);
  digitalWrite(rightRev, LOW);
  
}
void rightTurn(){
  digitalWrite(leftFwd, HIGH);
  digitalWrite(leftRev, LOW);
  digitalWrite(rightFwd, LOW);
  digitalWrite(rightRev, HIGH);
}
void turnAround(){
  rightTurn();
  delay(500);
  rightTurn();
  delay(500);
}
long activateSensor1(){
  long range;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(1); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5); //this delay is required too
  digitalWrite(trigPin, LOW);
  long dura = pulseIn(echoPin, HIGH);
  range = (dura/2) / (29.1);
  return range;
}
long activateSensor2(){
  long range;
  digitalWrite(trigPin_2, LOW);  
  delayMicroseconds(1); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(5); //this delay is required too
  digitalWrite(trigPin_2, LOW);
  long dura = pulseIn(echoPin_2, HIGH);
  range = (dura/2) / (29.1);
  return range;
}


void setup() { 
  // put your setup code here, to run once:
  Serial.begin(9600); // begin serial communitication  
  Serial.println("Motor test!");
  pinMode(trigPin, OUTPUT);// sets the trig pin to output (Send sound waves)
  pinMode(echoPin, INPUT);// sets the echo pin to input (Recieve sound waves)
  pinMode(trigPin_2, OUTPUT);// sets the trig pin to output (Send sound waves)
  pinMode(echoPin_2, INPUT);// sets the echo pin to input (Recieve sound waves)
  
  pinMode(leftFwd, OUTPUT);
  pinMode(leftRev, OUTPUT);
  pinMode(rightFwd, OUTPUT);
  pinMode(rightRev, OUTPUT);
  
  int pin = 12;
  calvin.attach(pin); //sets the servo
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, distance, duration_2, distance_2; // start the scan
  
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin_2, LOW);  
  delayMicroseconds(1); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(5); //this delay is required too
  
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin_2, LOW);
  duration = pulseIn(echoPin, HIGH);
  duration_2 = pulseIn(echoPin_2, HIGH);

  distance = (duration/2) / (29.1);  //converts distance to centimeters
  distance_2 = (duration_2/2) / (29.1); //converts distance to centimeters
  //calvin.write(100);
  
  //if there's an obstacle 25 centimers, ahead, do the following:
  if (distance < 25){   
    Serial.println ("Close Obstacle detected!" );
    Serial.println ("Obstacle Details:");
    Serial.print ("Distance From Robot is " );
    Serial.print (distance);
    Serial.println ( " Centimeters! Will now find a way to turn");//print out the distance in centimeters.
    
    stopCar();
    delay(500); //delays time for car stop

    for(int i=0; i<160; i+=10){
      calvin.write(i);
      //delay(500);
      distance_2 = activateSensor2();
      delay(100);
      if(distance_2 > 25 && i < 80){
        rightTurn();
        //delay(500);
        return;
      }else if(distance_2 > 25 && i >=80){
        leftTurn();
        //delay(500);
        return;
      }
    }
    for(int j=160; j>0; j-=10){
      calvin.write(j);
      //delay(500);
      distance_2 = activateSensor2();
      delay(100);
      if(distance_2 > 25 && j < 80){
        rightTurn();
        //delay(500);
        return;
      }else if(distance_2 > 25 && j >=80){
        leftTurn();
        //delay(500);
        return;
      }
    }
  }

  else {
    
    Serial.println ("No obstacle detected. going forward");
    //delay (15);
    startCar();
    //calvin.write(140); //will move the servo
    delay(100);
    //calvin.write(40); //will move the servo

  } 

}




