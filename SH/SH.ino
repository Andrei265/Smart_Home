#include <Servo.h>
#include "Ultrasonic.h"
#include <SPI.h>
#include <Wire.h>

#define bathroomLightPin 5    
#define perimeterLightPin 9   
#define livingRoomLightPin 3    
#define corridorLightPin 6    

int commandValue;
byte isNewCommandReceived, ledDoorLap;
int clocktime;
int cltime;
int PIRValue = 0;
int PIRState;
int lightState;
int pirPin1 = A1;      
int pirPin2 = A2;      

int lightcycle;
int corridorLightState;          
int lightTimerValue;              
long previousMillis1 = 0; 

int livingRoomLightState;         
int lightTimerValue;
long previousMillis2 = 0;

int bathroomLightState;
int lightTimerValue;
long previousMillis3 = 0;

int lightG, lightV, lightK;
int ledDoor = 13;
int relay1 = 2;         
int relay2 = 10;
int relay3 = 4;
int relay4 = 12;
int a, b, c, d, k1 = 0, k2 = 0, k3 = 0, k4 = 0, s1 = 0, kOK = 0, pas = 0, MD = 0, npas = 1, nom = 0, InvPas = 0, smv = 0, smvon = 0, PIR3;
int key1, key2, key3, key4, keyOK, passw, kmanl, sig = 0, lig = 0, key11, zal1 = 0, zal11 = 0, kom2 = 0, kom22 = 0, tul = 0, tul2 = 0;
char incomingByte;
Ultrasonic ultrasonic(7, 11);
Servo servo;

void setup() {
  Wire.begin(4);                
  Wire.onReceive(receiveEvent); 
  Serial.begin(9600);
  pinMode(A3, OUTPUT);
  pinMode(ledDoor, OUTPUT);
  pinMode(pirPin1, INPUT);       
  pinMode(pirPin2, INPUT);       
  pinMode(relay1, OUTPUT);       
  digitalWrite(relay1, HIGH);    
  pinMode(relay2, OUTPUT);       
  digitalWrite(relay2, HIGH);
  pinMode(relay3, OUTPUT);
  digitalWrite(relay3, HIGH);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay4, HIGH);

  pinMode(bathroomLightPin, OUTPUT);
  pinMode(perimeterLightPin, OUTPUT);
  pinMode(livingRoomLightPin, OUTPUT);
  pinMode(corridorLightPin, OUTPUT);
  analogWrite(bathroomLightPin, 0);
  analogWrite(perimeterLightPin, 0);
  analogWrite(livingRoomLightPin, 0);
  analogWrite(corridorLightPin, 0);

  servo.attach(8);
  servo.write(90);
}

void loop() {
  if (isNewCommandReceived == 1) {
    handleCommand();
    isNewCommandReceived = 0;
  }

  if (lightState == 1) {
    handleLight();
  }

  if (PIRState == 1) {
    handlePIR();
  }

  delay(30);
}

void handleCommand() {
  switch (commandValue) {
    case 1:
      handleCommand1();
      break;
    case 3:
    case 101:
      handleCommand3();
      break;
    case 44:
      handleCommand44();
      break;
    case 9:
      handleCommand9();
      break;
    case 10:
      handleCommand10();
      break;
    case 11:
      handleCommand11();
      break;
    case 22:
      handleCommand22();
      break;
    case 12:
      handleCommand12();
      break;
    case 21:
      handleCommand21();
      break;
    case 13:
      handleCommand13();
      break;
    case 31:
      handleCommand31();
      break;
    case 14:
      handleCommand14();
      break;
    case 41:
      handleCommand41();
      break;
    case 15:
      handleCommand15();
      break;
    case 51:
      handleCommand51();
      break;
  }
}

void handleCommand1() {
  PIRState = 0;
  lightState = 0;
  tul2 = 1;
  kom22 = 1;
  zal11 = 1;
  corridorLightState = 0;
  lightTimerValue = 0;
  kom22 = 0;
  lzalstate = 0;
  valC = 0;
  zal11 = 0;
  ltulstate = 0;
  valT = 0;
  tul2 = 0;
  Wire.beginTransmission(5); 
  Wire.write(commandValue);          
  Wire.endTransmission();
}

void handleCommand3() {
  digitalWrite(ledDoor, HIGH);
  delay(100);
  digitalWrite(ledDoor, LOW);
  delay(100);
  digitalWrite(ledDoor, HIGH);
  delay(100);
  digitalWrite(ledDoor, LOW);
  delay(100);
  digitalWrite(ledDoor, HIGH);
  delay(100);
  digitalWrite(ledDoor, LOW);
  delay(100);
  digitalWrite(ledDoor, HIGH);
  delay(100);
  digitalWrite(ledDoor, LOW);
  delay(100);
  digitalWrite(ledDoor, HIGH);
  delay(100);
  digitalWrite(ledDoor, LOW);
  delay(100);
  Serial.println("light");
  nom = 0;   
  sig = 0;   
  lig = 0;  
  PIRValue = 0;
  lightState = 1;
  lightin();
}

void handleCommand44()

void handleCommand44() {
  Serial.println("security");
  nom = 0;   
  sig = 0;   
  lig = 0;   
  lightState = 0;
  PIRState = 1;
  s1 = 0;
  tul2 = 1;
  kom22 = 1;
  zal11 = 1;
  corridorLightState = 0;
  lightTimerValue = 0;
  kom22 = 0;
  lzalstate = 0;
  valC = 0;
  zal11 = 0;
  ltulstate = 0;
  valT = 0;
  tul2 = 0;
  Wire.beginTransmission(5); 
  Wire.write(4);            
  Wire.endTransmission();
  PIR();
}

void handleCommand9() {
  analogWrite(perimeterLightPin, 255);
  delay(300);
  analogWrite(perimeterLightPin, 0);
  for (int i = 90; i <= 164; i++) {
    servo.write(i);
    delay(17);
  }
  Wire.beginTransmission(5); 
  Wire.write(commandValue);          
  Wire.endTransmission();
}

void handleCommand10() {
  for (int i = 164; i >= 90; i--) {
    servo.write(i);
    delay(17);
  }
  Wire.beginTransmission(5); 
  Wire.write(commandValue);          
  Wire.endTransmission();
}

void handleCommand11() {
  Serial.println(11);
  for (int i = 0; i <= 150; i++) {
    analogWrite(corridorLightPin, i); 
    delay(10);
  }
  lightK = 1;
  Wire.beginTransmission(5); 
  Wire.write(commandValue);          
  Wire.endTransmission();
}

void handleCommand22() {
  for (int k = 150; k >= 0; k--) {
    analogWrite(corridorLightPin, k);
    delay(10);
  }
  lightK = 0;
  Wire.beginTransmission(5);
  Wire.write(commandValue);         
  Wire.endTransmission();
}

void handleCommand12() {
  Serial.println(12);
  for (int i = 0; i <= 150; i++) {
    analogWrite(livingRoomLightPin, i); 
    delay(10);
  }
  lightG = 1;
  Wire.beginTransmission(5); 
  Wire.write(commandValue);          
  Wire.endTransmission();
}

void handleCommand21() {
  Serial.println(21);
  for (int k = 150; k >= 0; k--) {
    analogWrite(livingRoomLightPin, k); 
    delay(10);
  }
  lightG = 0;
  Wire.beginTransmission(5); 
  Wire.write(commandValue);          
  Wire.endTransmission();
}

void handleCommand13() {
  Serial.println(13);
  for (int i = 0; i <= 150; i++) {
    analogWrite(bathroomLightPin, i); 
    delay(10);
  }
  lightV = 1;
  Wire.beginTransmission(5); 
  Wire.write(commandValue);          
  Wire.endTransmission();
}

void handleCommand31() {
  Serial.println(31);
  for (int k = 150; k >= 0; k--) {
    analogWrite(bathroomLightPin, k); 
    delay(10);
  }
  lightV = 0;
  Wire.beginTransmission(5); 
  Wire.write(commandValue);          
  Wire.endTransmission();
}

void handleCommand14() {
  Serial.println(14);
  analogWrite(perimeterLightPin, 255); 
  Wire.beginTransmission(5); 
  Wire.write(commandValue);          
  Wire.endTransmission();
}

void handleCommand41() {
  Serial.println(41);
  analogWrite(perimeterLightPin, 0); 
  Wire.beginTransmission(5); 
  Wire.write(commandValue);          
  Wire.endTransmission();
}

void handleCommand15() {
  for (int i = 0; i <= 150; i++) {
    if (lightG == 0) analogWrite(livingRoomLightPin, i);
    if (lightV == 0) analogWrite(bathroomLightPin, i);
    if (lightK == 0) analogWrite(corridorLightPin, i);
    delay(10);
  }
  lightG = 1;
  lightV = 1;
  lightK = 1;
  Wire.beginTransmission(5); 
  Wire.write(commandValue);          
  Wire.endTransmission();
}

void handleCommand51() {
  AllLightOff();
}

void newinfoCheck() {
  if (commandValue != 99) isNewCommandReceived = 1; 
}

void AllLightOff() {
  for (int k = 150; k >= 0; k--) {
    if (lightG == 1) analogWrite(livingRoomLightPin, k);   
    if (lightV == 1) analogWrite(bathroomLightPin, k);  
    if (lightK == 1) analogWrite(corridorLightPin, k); 
    delay(10);
  }
  lightG = 0;
  lightV = 0;
  lightK = 0;
  Wire.beginTransmission(5); 
  Wire.write(51);            
  Wire.endTransmission();
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { 

  }
  commandValue = Wire.read();    
  Serial.println(commandValue);
  if (commandValue != 99) isNewCommandReceived = 1; 
}