#include <WiFi.h> 
#include <SFE_BMP180.h> 
#include <Wire.h> 
#define trigPin 13 
#define echoPin 12 
#define led1 14 
#define led2 34 
// You will need to create an SFE_BMP180 object, here called "pressure" SCL to GPIO22, SDA  to GPIO 21: 
SFE_BMP180 pressure; 
#define ALTITUDE 1655.0 // Altitude of SparkFun's HQ in Boulder, CO. in meters 
const char* ssid = "ONLYCSE";//"VSES";//Enter the ssid of your router const char* password = "keepsmile";//"gnir33nignEtr@mS";//Enter the password of your router 
const char* host = "api.thingspeak.com"; 
const char* privateKey1 = "SSERIGKBMMZRGYH9";//write key 
String line,line1; 
int duration, distance; 
 double T,P,p0,a; 
 void setup() { 
 Serial.begin(115200); 
 Serial.println("REBOOT");  
 pinMode(trigPin, OUTPUT); 
 pinMode(echoPin, INPUT); 
 pinMode(led1, INPUT); 
 pinMode(led2, INPUT); 
 Serial.print("Ultrasonic Sensor Starting!!!"); 
 Serial.println(""); 
 // Initialize the sensor (it is important to get calibration values stored on the device). 
 if (pressure.begin()) 
 Serial.println("BMP180 init success"); 
 else 
 {
Iot lab manual CSE Dept., SRKREC. Page 34 of 51 
 // Oops, something went wrong, this is usually a connection problem,  // see the comments at the top of this sketch for the proper connections. 
 Serial.println("BMP180 init fail\n\n"); 
 while(1); // Pause forever. 
 } 
 // We start by connecting to a WiFi network 
 Serial.println(); 
 Serial.println(); 
 Serial.print("Connecting to "); 
 Serial.println(ssid); 
  
 WiFi.begin(ssid, password); 
  
 while (WiFi.status() != WL_CONNECTED) { 
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
 digitalWrite(trigPin, HIGH); 
 delay(1000); 
 digitalWrite(trigPin, LOW); 
 duration = pulseIn(echoPin, HIGH); 
 distance =(duration/2) * 0.0343;// time * speed of sound(0.0343cm/microsec)  Serial.print("Distance is"); 
Serial.println(distance); 
 if (distance < 10) 
 { 
 digitalWrite(led1, LOW);
Iot lab manual CSE Dept., SRKREC. Page 35 of 51 
 Serial.println("Low"); 
 } 
 else if (distance <= 100) 
 { 
 Serial.println("Half"); 
 digitalWrite(led1, HIGH); 
 } 
 else  
 { 
 digitalWrite(led2, HIGH); 
 Serial.println("Out of Range"); 
 Serial.println(""); 
 } 
 char status; 
 // Loop here getting pressure readings every 10 seconds. 
 // If you want sea-level-compensated pressure, as used in weather reports,  // you will need to know the altitude at which your measurements are taken.  // We're using a constant called ALTITUDE in this sketch: 
  
// Serial.println(); 
// Serial.print("provided altitude: "); 
// Serial.print(ALTITUDE,0); 
// Serial.print(" meters, "); 
// Serial.print(ALTITUDE*3.28084,0); 
// Serial.println(" feet"); 
  
 // If you want to measure altitude, and not pressure, you will instead need  // to provide a known baseline pressure. This is shown at the end of the sketch. 
 // You must first get a temperature measurement to perform a pressure reading.   
 // Start a temperature measurement: 
 // If request is successful, the number of ms to wait is returned.  // If request is unsuccessful, 0 is returned. 
 status = pressure.startTemperature(); 
 if (status != 0) 
 {
Iot lab manual CSE Dept., SRKREC. Page 36 of 51 
 // Wait for the measurement to complete: 
 delay(status); 
 // Retrieve the completed temperature measurement: 
 // Note that the measurement is stored in the variable T. 
 // Function returns 1 if successful, 0 if failure. 
 status = pressure.getTemperature(T); 
 if (status != 0) 
 { 
 // Print out the measurement: 
 Serial.print("temperature: "); 
 Serial.print(T,2); 
 Serial.print(" deg C, "); 
 Serial.print((9.0/5.0)*T+32.0,2); 
 Serial.println(" deg F"); 
  
 // Start a pressure measurement: 
 // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).  // If request is successful, the number of ms to wait is returned. 
 // If request is unsuccessful, 0 is returned. 
 status = pressure.startPressure(3); 
 if (status != 0) 
 { 
 // Wait for the measurement to complete: 
 delay(status); 
 // Retrieve the completed pressure measurement: 
 // Note that the measurement is stored in the variable P. 
 // Note also that the function requires the previous temperature measurement (T).  // (If temperature is stable, you can do one temperature measurement for a number of  pressure measurements.) 
 // Function returns 1 if successful, 0 if failure. 
 status = pressure.getPressure(P,T); 
 if (status != 0) 
 { 
 // Print out the measurement: 
 Serial.print("absolute pressure: ");
Iot lab manual CSE Dept., SRKREC. Page 37 of 51 
 Serial.print(P,2); 
 Serial.print(" mb, "); 
 Serial.print(P*0.0295333727,2); 
 Serial.println(" inHg"); 
 // The pressure sensor returns abolute pressure, which varies with altitude.  // To remove the effects of altitude, use the sealevel function and your current altitude.  // This number is commonly used in weather reports. 
 // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.  // Result: p0 = sea-level compensated pressure in mb 
 p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)  Serial.print("relative (sea-level) pressure: "); 
 Serial.print(p0,2); 
 Serial.print(" mb, "); 
 Serial.print(p0*0.0295333727,2); 
 Serial.println(" inHg"); 
 // On the other hand, if you want to determine your altitude from the pressure reading,  // use the altitude function along with a baseline pressure (sea-level or other).  // Parameters: P = absolute pressure in mb, p0 = baseline pressure in mb.  // Result: a = altitude in m. 
// 
// a = pressure.altitude(P,p0); 
// Serial.print("computed altitude: "); 
// Serial.print(a,0); 
// Serial.print(" meters, "); 
// Serial.print(a*3.28084,0); 
// Serial.println(" feet"); 
 } 
 else Serial.println("error retrieving pressure measurement\n"); 
 } 
 else Serial.println("error starting pressure measurement\n"); 
 } 
 else Serial.println("error retrieving temperature measurement\n"); 
 } 
 else Serial.println("error starting temperature measurement\n"); 
 upload(); 
 delay(15000); 
}
Iot lab manual CSE Dept., SRKREC. Page 38 of 51 
void upload() 
{ 
 Serial.print("connecting to "); 
 Serial.println(host); 
  
 // Use WiFiClient class to create TCP connections 
 WiFiClient client; 
 const int httpPort = 80; 
  
 if (!client.connect(host, httpPort)) { 
 Serial.println("connection failed"); 
 return; 
 } 
  
 // We now create a URI for the request 
 String url = "/update"; 
 url += "?api_key="; 
 url += privateKey1; 
 url += "&field1="; 
 url += distance; 
 url += "&field2="; 
 url += T; 
 url += "&field3="; 
 url += P; 
 Serial.print("Requesting URL: "); 
 Serial.println(url); 
 // This will send the request to the server 
 client.print(String("GET ") + url + " HTTP/1.1\r\n" +  "Host: " + host + "\r\n" +  
 "Connection: close\r\n\r\n"); 
 delay(1000); 
 // Read all the lines of the reply from server and print them to Serial  while(client.available()) 
 { 
 String line1 = client.readStringUntil('\r'); 
 Serial.print(line1); 
 } 
 Serial.println(); 
 Serial.println("closing connection");}
