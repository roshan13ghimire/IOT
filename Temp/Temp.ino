#include "DHT.h"
#define DHTPIN 4    
#define DHTTYPE DHT11  
DHT dht (DHTPIN, DHTTYPE);

float h,t;

void setup() {   // single execution --> Eg: power on/off 
  Serial.begin(115200); 
 }

void loop() // multiple execution
{
  h = dht.readHumidity();
  t = dht.readTemperature();
 Serial.print("temperature:");
 Serial.println(t);
 Serial.print("Humidity:");
 Serial.println(h);
 delay(10000);
}
