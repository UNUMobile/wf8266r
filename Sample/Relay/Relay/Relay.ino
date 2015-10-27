void setup() {
  // put your setup code here, to run once:
pinMode(5,OUTPUT);
pinMode(4,OUTPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(5,0);
  delay(1000);
  digitalWrite(5,1);
  delay(1000);

  digitalWrite(4,0);
  delay(1000);
  digitalWrite(4,1);
  delay(1000);

  digitalWrite(12,0);
  delay(1000);
  digitalWrite(12,1);
  delay(1000);  

  digitalWrite(13,0);
  delay(1000);
  digitalWrite(13,1);
  delay(1000);  

  digitalWrite(5,0);
  delay(1000);
  digitalWrite(4,0);
  delay(1000);  
  digitalWrite(12,0);
  delay(1000);
  digitalWrite(13,0);
  delay(1000);  

  digitalWrite(5,1);
  digitalWrite(4,1);
  digitalWrite(12,1);
  digitalWrite(13,1);
  delay(1000);  
}
