#include <Arduino.h>
#include "phmeter.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define Offset -4.02           //deviation compensate
#define ASAM D7
#define NETRAL D6
#define BASA D5
#define WIFI D0

#define ledBasa()   digitalWrite(BASA,HIGH);digitalWrite(ASAM,LOW);digitalWrite(NETRAL,LOW);
#define ledNetral() digitalWrite(BASA,LOW);digitalWrite(ASAM,LOW);digitalWrite(NETRAL,HIGH);
#define ledAsam() digitalWrite(BASA,LOW);digitalWrite(ASAM,HIGH);digitalWrite(NETRAL,LOW);


char auth[] = "N58tGgJMm8Rz4XJT2OVQ3fNsQ3uDYQm7"; //anung
char ssid[] = "ardinista";            //nama wifi
char pass[] = "ardiasta";             //password wifi 


uint8_t kedip;
Phmeter Ph = Phmeter(A0);
BlynkTimer Timer1s; 

void sensorUpdate(){

  kedip++;
  if (kedip%2==0) digitalWrite(WIFI,HIGH);
  else digitalWrite(WIFI,LOW);


  Serial.print("Tegangan pH sensor = ");    //Test the serial monitor
  Serial.println(Ph.getVoltage());
  Serial.print("pH meter value = ");    //Test the serial monitor
  Serial.println(Ph.getPH());

  Blynk.virtualWrite(1,Ph.getVoltage());
  Blynk.virtualWrite(0,Ph.getPH());

  if (Ph.getPH() >= 8.5){
    ledBasa();
    Blynk.notify("Ph Air di atas normal");
  }
  else if (Ph.getPH() < 6.0){
    ledAsam();
    Blynk.notify("pH air di bawah normal ");
  }
  else {
    ledNetral();
  }
  
}
void setup(void)
{
  Ph.calibrate(Offset);
  pinMode(ASAM, OUTPUT);
  pinMode(BASA, OUTPUT);
  pinMode(NETRAL, OUTPUT);
  pinMode(WIFI, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  Timer1s.setInterval(1000L,sensorUpdate);
  
}
void loop(void)
{
  Blynk.run();
  Timer1s.run();
}
