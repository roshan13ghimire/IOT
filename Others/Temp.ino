#include "DHT.h"
#define DHTPIN 15     
#define DHTTYPE DHT11  
DHT dht (DHTPIN, DHTTYPE);

float h,t;

void setup() {
  Serial.begin(115200);
 }

void loop() 
{
  h = dht.readHumidity();
  t = dht.readTemperature();
 Serial.print("temperature:");
 Serial.println(t);
 Serial.print("Humidity:");
 Serial.println(h);
 delay(1000);
}
