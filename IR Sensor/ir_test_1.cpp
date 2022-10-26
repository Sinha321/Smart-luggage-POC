//ir sensor code
void setup()
{
  pinMode(13,OUTPUT);  // configuring pin 13 as output pin
  pinMode(3,INPUT);    //configuring pin 3 as input pin
  Serial.begin(9600);  //baudrate
}
void loop()
{
  if(digitalRead(3)==LOW)
  {
    digitalWrite(13,HIGH);
    delay(10);   //delay of 10 microseconds
  }
  else
  {
     digitalWrite(13,LOW);
    delay(10);   //delay of 10 microseconds
    
  }
  
}
