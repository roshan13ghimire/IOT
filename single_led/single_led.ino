void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(16,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(16,HIGH);
  delay(1000);
  digitalWrite(16,LOW);
  delay(1000);

  digitalWrite(12,HIGH);
  delay(1000);
  digitalWrite(12,LOW);
  delay(1000);

  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  delay(1000);
  
  
  

}
