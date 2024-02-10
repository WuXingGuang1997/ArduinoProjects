#include <SoftwareSerial.h>

SoftwareSerial sim800(2, 3); //SIM800L Tx & Rx is connected to Arduino #3 & #2

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorvalue2=0;
bool ripeti=false;
String valore="5000";
void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
    pinMode(12, INPUT);
    sim800.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);
  sim800.println("AT"); //Once the handshake test is successful, it will back to OK
  //updateSerial();
  resp("OK");
  sim800.println("AT+CSQ"); //test segnale
  resp("OK");
  sim800.println("AT+CFUN=1"); //full funzioni
  resp("OK");  
  sim800.println("AT+CGATT=1"); //collegati a gprs
  resp("OK");
  sim800.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  resp("OK");
  sim800.println("AT+SAPBR=3,1,\"APN\",\"TM\"");
  resp("OK");
  sim800.println("AT+SAPBR=1,1");
  resp("OK");
  sim800.println("AT+HTTPINIT"); //Init HTTP service
  resp("OK");
  sim800.println("AT+HTTPPARA=\"CID\",1");
  resp("OK");
  sim800.println("AT+HTTPPARA=\"REDIR\",1"); //Auto redirect
  resp("OK");  
 
}
void loop() {
sensorvalue2=digitalRead(12);
Serial.println(sensorvalue2);
if(sensorvalue2==LOW){

 sensorValue = analogRead(sensorPin);
   // Serial.println(sensorValue);

    if(sensorValue<500){
      if(ripeti==true){
      int v = analogRead(A0);
    sim800.println("AT+HTTPPARA=\"URL\",\"http://www.arduinoxing.it/service.php?sens="+String(v)+" motore spento "+valore+"\"");
    resp("OK");    
    sim800.println("AT+HTTPACTION=0");  //call
    resp("OK");
    delay(5000);
    sim800.println("AT+HTTPREAD");    
    resp("OK");
     
       digitalWrite(ledPin, LOW);
       ripeti =false;
     
       
      }
    }
    else{

            if(ripeti==false){
      int v = analogRead(A0);
    sim800.println("AT+HTTPPARA=\"URL\",\"http://www.arduinoxing.it/service.php?sens="+String(v)+" motore acceso "+valore+"\"");
    resp("OK");    
    sim800.println("AT+HTTPACTION=0");  //call
    resp("OK");
    delay(5000);
    sim800.println("AT+HTTPREAD");    
    resp("OK");

 sim800.println("AT+HTTPPARA=\"URL\",\"http://www.arduinoxing.it/dati2.txt\"");
    resp("OK");    
    sim800.println("AT+HTTPACTION=0");  //call
    resp("OK");
    delay(5000);
    sim800.println("AT+HTTPREAD");


    if (resp("1000")==1){
    valore="1000";
    }
    
 sim800.println("AT+HTTPPARA=\"URL\",\"http://www.arduinoxing.it/dati2.txt\"");
    resp("OK");    
    sim800.println("AT+HTTPACTION=0");  //call
    resp("OK");
    delay(5000);
    sim800.println("AT+HTTPREAD");


    if (resp("5000")==1){
    valore="5000";
    }

 sim800.println("AT+HTTPPARA=\"URL\",\"http://www.arduinoxing.it/dati2.txt\"");
    resp("OK");    
    sim800.println("AT+HTTPACTION=0");  //call
    resp("OK");
    delay(5000);
    sim800.println("AT+HTTPREAD");
    if (resp("10000")==1){
    valore="10000";
    }

    sim800.println("AT+HTTPPARA=\"URL\",\"http://www.arduinoxing.it/dati2.txt\"");
    resp("OK");    
    sim800.println("AT+HTTPACTION=0");  //call
    resp("OK");
    delay(5000);
    sim800.println("AT+HTTPREAD");
    if (resp("15000")==1){
    valore="15000";
    }
       digitalWrite(ledPin, LOW);
       ripeti =true;
       }
  digitalWrite(ledPin, HIGH);
  delay(valore.toInt());
  digitalWrite(ledPin, LOW);
  delay(2000);
 Serial.println("on");
 
        } 
}
}

int resp (String txt) {   
  int n = 0; 
  String ret = "";
  bool LOOP = true;
  while(LOOP){
    
    if (sim800.available()) {
      char c = sim800.read();
      if (c == '\n') {
       
        Serial.println("RX:" + ret + "#");

       
        if (ret == txt) {
          Serial.println("---");
          
          LOOP = false;
          n = 1;
        } else if (ret == "OK") {
          LOOP = false;
          n = 0;
        } else if (ret == "ERROR") {
          LOOP = false;
          n = -1;
        }
        
        ret = "";
      } else if (c == '\r') {        
      } else {
        ret += c;           
      }    
    }
  }
  delay(1000);
  return n;
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    sim800.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(sim800.available()) 
  {
    Serial.write(sim800.read());//Forward what Software Serial received to Serial Port
  }
}
