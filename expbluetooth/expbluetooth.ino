#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
String state;
void setup() {
pinMode(15, OUTPUT);
Serial.begin(115200);
SerialBT.begin("hima"); //Bluetooth device name
Serial.println("The device started, now you can pair it with bluetooth!");
}
void loop() {
if (Serial.available())
{
SerialBT.write(Serial.read());
Serial.println("hello");
}
if (SerialBT.available()) {
state=SerialBT.read();
Serial.print("State :");
Serial.println(state);
if (state.equals("55")) {
digitalWrite(15, HIGH);
Serial.println("Light On");
}
// if the state is 'LED1OFF' the led1 will turn off
else if (state.equals("56")){
digitalWrite(15, LOW);
Serial.println("Light Off");
}
}
state="";
delay(1000);
}
