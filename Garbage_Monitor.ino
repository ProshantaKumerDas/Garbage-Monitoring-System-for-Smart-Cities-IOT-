//**********
  Proshanta Kumer Das
//**********
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Servo.h>   //servo library
  Servo servo;    
  
//----------- Enter you Wi-Fi Details---------//
char ssid[] = "UIU"; //SSID
char pass[] = "xyz"; // Password
//-------------------------------------------//

const int trigger = 16;  // Nodemcu D0
const int echo = 5;     // Nodemcu D1
int trigPin = 14;      // Nodemcu D5
  int echoPin = 12;   // Nodemcu D6 
  int servoPin = 2;  // Nodemcu D4
  int blue = 15;    // nodemcu D7
  int buz = 13;    // nodemcu D8
int red = 4;      // Nodemcu D2
int green = 0;   // Nodemcu D3
long T;
float distance;

long duration, dist, average;   
  
  long aver[3]; //array for average
WiFiClient  client;

unsigned long myChannelField = xyz; // Channel ID
const int ChannelField = 1; // Which channel to write data
const char * myWriteAPIKey = "xyz"; // Your write API Key

void setup()
{
  Serial.begin(115200);
  servo.attach(servoPin);  
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(red, OUTPUT); 
  pinMode(green, OUTPUT); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(blue, OUTPUT); 
  pinMode(buz, OUTPUT); 
  
    servo.write(0);         //close cap on power on
       
     delay(100);
        
    servo.detach();
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}


  void measure() 
  {  
   
    digitalWrite(trigPin, LOW);
    
    delayMicroseconds(5);
    
    digitalWrite(trigPin, HIGH);
    
    delayMicroseconds(15);
    
    digitalWrite(trigPin, LOW);
    
    pinMode(echoPin, INPUT);
    
    duration = pulseIn(echoPin, HIGH);
    
    dist = (duration/2) / 29.1;    //obtain distance
    
  }

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
   long duration, distance;
   digitalWrite(blue,HIGH);
   
   for (int i=0;i<=2;i++) 
    {  
       
     measure();               
       
    aver[i]=dist;            
       
     delay(10);              //delay between measurements
      
  }
   
if ( dist<20 ) {

    digitalWrite(blue,LOW);
     
    servo.attach(servoPin);
      
    delay(1);
     
    servo.write(0); 
     
    delay(4000);       
     
    servo.write(150);
     
    delay(2000);
     
    servo.detach();     
   
  }
digitalWrite(trigger, LOW);
delay(1);
digitalWrite(trigger, HIGH);

delayMicroseconds(10);

digitalWrite(trigger, LOW);

T = pulseIn(echo, HIGH);
  distance = T * 0.034;

  Serial.print("Distance in cm: ");
  Serial.println(distance);

if (distance >= 5 && distance <=8 )
{ 
  digitalWrite(green,LOW);  
  digitalWrite(red,HIGH);
  tone(buz,2000,500);
}

else if (distance < 5)
{ 
  digitalWrite(red,HIGH);
  tone(buz,2000,500);
  digitalWrite(green,LOW);
}

else if(distance>8){
digitalWrite(buz,LOW);
digitalWrite(red,LOW);
digitalWrite(green,HIGH);

}
ThingSpeak.writeField(myChannelField, ChannelField, distance, myWriteAPIKey);
  delay(1000);
}
