#include "BluetoothSerial.h" 
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED) 
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it 
#endif 
BluetoothSerial SerialBT; 
String state; 
void setup() { 
  pinMode(17, OUTPUT); 
 // pinMode(4, OUTPUT); 
  Serial.begin(115200); 
  SerialBT.begin("james"); 
  //Bluetooth device name 
  Serial.println("The device started, now you can pair it with bluetooth!"); 
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
    if (state.equals("53")) { 
      digitalWrite(17, HIGH); 
      Serial.println("Light On"); 
    } 
    // if the state is 'LED1OFF' the led1 will turn off 
    else if (state.equals("54")){ 
      digitalWrite(17, LOW); 
      Serial.println("Light Off"); 
    } // if the state is 'LED2ON' the Led2 will turn on  
  }
  state=""; 
  delay(2000);
}
