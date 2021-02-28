#include <ThingSpeak.h>
#include <WiFi.h>
WiFiClient  client;
const char* ssid = "digAbug";//Enter the ssid of your router 
const char* password = "digabug@9";//Enter the password of your router  
const char* host = "api.thingspeak.com"; 
const char* privateKey = "0JI4JDB0HXS05J3F";//read key 
const char* privateKey1 = "4PVWXTJ1LQAQEDR6";//write key  
void setup() 
{ 
  Serial.begin(115200);  
  pinMode(4, OUTPUT);
  ThingSpeak.begin(client); 
  delay(10); 
}
 // We start by connecting to a WiFi network  
  Serial.println();  
  Serial.println(); 
  Serial.print("Connecting to "); 
  Serial.println(ssid);     
  WiFi.begin(ssid, password);   
  while (WiFi.status() != WL_CONNECTED)
  {    
    delay(500);   
    Serial.print("."); 
  }  
  Serial.println(""); 
  Serial.println("WiFi connected");  
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
  }
  
  void loop()
  { 
  int d= ThingSpeak.readIntField( 626082,1);  
  Serial.print(d); 
  if(d==1)
  {
    digitalWrite(4,HIGH);
    Serial.print("LED ON");
    Serial.println("");
    } 
    if(d==0)  
{
  digitalWrite(4,LOW); 
  Serial.print("LED OFF"); 
  Serial.println(""); 
}  
delay(1000); 
} 
  } 
