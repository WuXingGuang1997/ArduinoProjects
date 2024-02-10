#include <SoftwareSerial.h>


#include <NewPing.h>
#include <Servo.h>
#define PULdx 7
#define DIRdx 8
#define VELdx 150
#define PULsx 9
#define DIRsx 10
#define VELsx 150
#define TRIGGER_PIN A2
#define ECHO_PIN A3
#define TRIGFrontLeft A0
#define ECHOFrontLeft A1
#define TRIGFrontRight A4
#define ECHOFrontRight A5
#define TRIGBackLeft A6
#define ECHOBackLeft A7
#define TRIGBackRight A8
#define ECHOBackRight A9
#define TRIGBack A10
#define ECHOBack A11
#define max_distance 60

NewPing sonar(TRIGGER_PIN, ECHO_PIN, max_distance);
NewPing sonarFrontLeft(TRIGFrontLeft, ECHOFrontLeft, max_distance);
NewPing sonarFrontRight(TRIGFrontRight, ECHOFrontRight, max_distance);
NewPing sonarBackRight(TRIGBackRight, ECHOBackRight, max_distance);
NewPing sonarBackLeft(TRIGBackLeft, ECHOBackLeft, max_distance);
NewPing sonarBack(TRIGBack, ECHOBack, max_distance);
int distance = 0;
int leftDistance;
int rightDistance;
int FrontLeftDistance = 0;
int FrontRightDistance = 0;
int BackLeftDistance = 0;
int BackRightDistance = 0;
int BackDistance=0;
int leftDistance2;
int rightDistance2;
boolean object;
Servo servo;
int i = 0;
int ostacolopin = 2;
int ostacolo = LOW;
String Data;
String str = "";
SoftwareSerial BTSerial(11, 12);
void setup() {
  int Distance;
  pinMode(PULdx, OUTPUT);
  pinMode(DIRdx, OUTPUT);
  digitalWrite(DIRdx, HIGH);
  pinMode(PULsx, OUTPUT);
  pinMode(DIRsx, OUTPUT);
  digitalWrite(DIRsx, LOW);
  servo.attach(5);
  servo.write(90);
  pinMode(ostacolopin, INPUT);
  pinMode(4, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(4, HIGH);
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(9600);
}
void loop() {
  if (BTSerial.available()) {
    char ch = BTSerial.read();
 
Data=Data+ch;
    if (!BTSerial.available() && Data.length()>3) {
      Serial.println(Data);
      if(Data=="Avanti"){
        str="Avanti";
  
      }else{
        str="Stop";
        }
Data="";

  }
  }
  if (!BTSerial.available()) {
  if (str=="Avanti"){
    objectAvoid();
    
    }
    else{
      
      }
  }


  // Keep reading from Arduino Serial Monitor and send to HC-05

}
void avanti() {
    digitalWrite(DIRdx, HIGH);
  digitalWrite(DIRsx, LOW);
  for (i = 0; i < 500; i++) {
    digitalWrite(PULdx, HIGH);
    digitalWrite(PULsx, HIGH);
    delayMicroseconds(VELdx);
    digitalWrite(PULdx, LOW);
    digitalWrite(PULsx, LOW);
    delayMicroseconds(VELdx);
  }                 // wait for a second// turn the LED off by making the voltage LOW
}
void indietro() {
  
  digitalWrite(DIRdx, LOW);
  digitalWrite(DIRsx, HIGH);
  for (i = 0; i < 3000; i++) {
    digitalWrite(PULdx, HIGH);
    digitalWrite(PULsx, HIGH);
    delayMicroseconds(VELdx);
    digitalWrite(PULdx, LOW);
    digitalWrite(PULsx, LOW);
    delayMicroseconds(VELdx);
  }                 // wait for a second// turn the LED off by making the voltage LOW
}
void destra() {
  for (i = 0; i < 1000; i++) {
    digitalWrite(PULdx, HIGH);
    delayMicroseconds(VELdx);
    digitalWrite(PULdx, LOW);
    delayMicroseconds(VELdx);
  }
}
void sinistra() {
  for (i = 0; i < 1000; i++) {
    digitalWrite(PULsx, HIGH);
    delayMicroseconds(VELsx);
    digitalWrite(PULsx, LOW);
    delayMicroseconds(VELsx);
  }
}
int getDistance() {
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 100;
  }
  return cm;
}
int getFrontLeftDistance() {
  int cm2 = sonarFrontLeft.ping_cm();
  if (cm2 == 0) {
    cm2 = 100;
  }
  return cm2;
}
int getFrontRightDistance() {
  int cm = sonarFrontRight.ping_cm();
  if (cm == 0) {
    cm = 100;
  }
  return cm;
}
int getBackLeftDistance() {
  int cm = sonarBackLeft.ping_cm();
  if (cm == 0) {
    cm = 100;
  }
  return cm;
}
int getBackRightDistance() {
  int cm = sonarBackRight.ping_cm();
  if (cm == 0) {
    cm = 100;
  }
  return cm;
}
int getBackDistance() {
  int cm = sonarBack.ping_cm();
  if (cm == 0) {
    cm = 100;
  }
  return cm;
}
void objectAvoid() {
  distance = getDistance();
  FrontLeftDistance = getFrontLeftDistance();
  FrontRightDistance = getFrontRightDistance();
  BackLeftDistance = getBackLeftDistance();
  BackRightDistance = getBackRightDistance();
  BackDistance = getBackDistance();

 if (FrontLeftDistance > 0 && FrontLeftDistance <= 40 && FrontRightDistance >30 && distance>30 && BackLeftDistance > 30 && BackRightDistance >30 && BackDistance > 30){
 Serial.println(FrontLeftDistance);
 Serial.println(FrontRightDistance);
  indietro();
   sinistra();
}
else if (FrontRightDistance > 0 && FrontRightDistance <= 40 && FrontLeftDistance >30 && distance>30 && BackLeftDistance > 30 && BackRightDistance >30 && BackDistance > 30){
 Serial.println(FrontLeftDistance);
  Serial.println(FrontRightDistance);
  indietro();
   destra();
}


  
 else if (distance <= 40) {
    //stop
    Stop();
    Serial.println("Stop");
    lookLeft();
    lookRight();
    delay(100);
    if (rightDistance <= leftDistance) {
      //left
      object = true;
      turn();
      Serial.println("moveLeft");
    } else {
      //right
      object = false;
      turn();
      Serial.println("moveRight");
    }
    delay(100);
  }
  else {
    //forword
    Serial.println("moveforword");
   avanti();
  }
}
int lookLeft () {
  //lock left
  servo.write(150);
  delay(500);
  leftDistance = getDistance();
  delay(100);
  servo.write(90);
  Serial.print("Left:");
  Serial.print(leftDistance);
  return leftDistance;
  delay(100);
}
int lookRight() {
  //lock right
  servo.write(30);
  delay(500);
  rightDistance = getDistance();
  delay(100);
  servo.write(90);
  Serial.print("   ");
  Serial.print("Right:");
  Serial.println(rightDistance);
  return rightDistance;
  delay(100);
}
void Stop() {
}
void turn() {
  if (object == false) {
    Serial.println("turn Right");
    indietro();
    destra();

  }
  else {
    Serial.println("turn left");
    indietro();
    sinistra();

  }
}
