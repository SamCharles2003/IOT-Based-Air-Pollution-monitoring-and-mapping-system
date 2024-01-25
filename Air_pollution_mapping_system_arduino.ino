#include <DHT.h>
#include <DHT_U.h>
#include<SoftwareSerial.h>
#define DHTTYPE    DHT11     // DHT 11
#define DHTPIN 4
DHT_Unified dht(DHTPIN, DHTTYPE);
SoftwareSerial esp8266(2,3);
void setup()
{

  esp8266.begin(9600);
  Serial.begin(9600);
  dht.begin();
  sensor_t sensor;
  pinMode(A0,INPUT);//MQ2
  pinMode(A1,INPUT);//MQ3
  pinMode(A2,INPUT);//MQ6
  pinMode(A3,INPUT);//MQ7

}
void loop()
{
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  int temperature= event.temperature;
  int mq2_raw=analogRead(A0);
  int mq3_raw=analogRead(A1);
  int mq6_raw=analogRead(A2);
  int mq7_raw=analogRead(A3);

  int mq2=map(mq2_raw,0,1023,0,100);
  int mq3=map(mq3_raw,0,1023,0,100);
  int mq6=map(mq6_raw,0,1023,0,100);
  int mq7=map(mq7_raw,0,1023,0,100);

  int average = 100-((mq2+mq3+mq6+mq7)/4);

  esp8266.print(String(mq2));
  esp8266.print(" ");
  esp8266.print(String(mq3));
  esp8266.print(" ");
  esp8266.print(String(mq6));  
  esp8266.print(" ");  
  esp8266.print(String(mq7));
  esp8266.print(" ");
  esp8266.print(String(average));
  esp8266.print(" "); 
  esp8266.print(String(temperature));   
  esp8266.print("\n");
  delay(1);

  Serial.print(String(mq2));
  Serial.print(" ");
  Serial.print(String(mq3));
  Serial.print(" ");
  Serial.print(String(mq6));  
  Serial.print(" ");  
  Serial.print(String(mq7));
  Serial.print(" ");
  Serial.print(String(average));
  Serial.print(" "); 
  Serial.print(String(temperature));   
  Serial.print("\n");



}