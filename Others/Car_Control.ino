#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
String state;
const int motorPin1=4;
const int motorPin2=16;
const int motorPin3=17;
const int motorPin4=5;

void setup() {
 pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  pinMode(motorPin3,OUTPUT);
  pinMode(motorPin4,OUTPUT);
Serial.begin(115200);
SerialBT.begin("IOT"); //Bluetooth device name
Serial.println("The device started, now you can pair it with bluetooth!");
digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin2,LOW);
  digitalWrite(motorPin3,LOW);
  digitalWrite(motorPin4,LOW);
}

void loop() {
if (Serial.available()) {
SerialBT.write(Serial.read());
Serial.println("hello");
}
if (SerialBT.available()) {
state=SerialBT.read();
Serial.print("State :");
Serial.println(state);
 
if(state=="50")
  {
  digitalWrite(motorPin1,HIGH);
  digitalWrite(motorPin2,LOW);
  digitalWrite(motorPin3,HIGH);
  digitalWrite(motorPin4,LOW);
  }
if(state=="56")
  {
  digitalWrite(motorPin2,HIGH);
  digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin4,HIGH);
  digitalWrite(motorPin3,LOW);
  }
  if(state=="54")
  {
  digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin2,LOW);
  digitalWrite(motorPin3,HIGH);
  digitalWrite(motorPin4,LOW);
  }
  if(state=="52")
  {
  digitalWrite(motorPin1,HIGH);
  digitalWrite(motorPin2,LOW);
  digitalWrite(motorPin3,LOW);
  digitalWrite(motorPin4,LOW);
  }
if(state=="53")
  {
  digitalWrite(motorPin1,LOW);
  digitalWrite(motorPin2,LOW);
  digitalWrite(motorPin3,LOW);
  digitalWrite(motorPin4,LOW);
  }




}
}
