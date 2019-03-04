
#include <pt.h>
#include <ESP8266WiFi.h>
#include <mqtt.h>
// pin 11 of 74HC595 (SHCP)
const int bit_clock_pin = D2;
// pin 12 of 74HC595 (STCP)
const int digit_clock_pin = D1;
// pin 14 of 74HC595 (DS)
const int data_pin = D0;

int current_sensor1 = D3;
int current_sensor2 = D7;//change thid to D4 at final stage
int current_sensor3 = D5;
int current_sensor4 = D6;

int Status_Read()
{
int switch1 = digitalRead(current_sensor1);
int switch2 = digitalRead(current_sensor2);
int switch3 = digitalRead(current_sensor3);
int switch4 = digitalRead(current_sensor4);

int current_status = switch1*1+switch2*2+switch3*4+switch4*8;

return  current_status;
}




void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 
}

void loop() {


int previous_status = Status_Read();
delay(1000);
int current_status = Status_Read();

if(previous_status != current_status)
{
  Serial.println("current_status: ");
  Serial.println(current_status);
  Serial.println("state changes");
  Serial.println("data publishing ");
  Serial.println("previous_status: ");
  Serial.println(previous_status);
  }
else{
  Serial.println("do nothing");
  }

}
