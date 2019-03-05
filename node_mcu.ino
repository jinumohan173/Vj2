
//relay4 is series
//rl3 is parallel
//qo-series
//q1-parallel

#include <pt.h>
#include <ESP8266WiFi.h>
#include <MQTT.h>
// pin 11 of 74HC595 (SHCP)
const int bit_clock_pin = D2;
// pin 12 of 74HC595 (STCP)
const int digit_clock_pin = D1;
// pin 14 of 74HC595 (DS)
const int data_pin = D0;

int current_sensor1 = D3;
int current_sensor2 = D4;//change thid to D4 at final stage
int current_sensor3 = D5;
int current_sensor4 = D6;


// digit pattern for a 7-segment display
const byte digit_pattern[16] =
{
  B00111111,  // 0 parallel relay and series relay on
  B11111111,  // 1 parallel relay and series relay off
  B01111111,  // 2 series relay on parallel relay off
  B00000000,  // 3 series relay off parallel relay on
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111,  // 9
  B01110111,  // A
  B01111100,  // b
  B00111001,  // C
  B01011110,  // d
  B01111001,  // E
  B01110001   // F
};

unsigned int counter = 0;




int Status_Read()
{
int switch1 = digitalRead(current_sensor1);
int switch2 = digitalRead(current_sensor2);
int switch3 = digitalRead(current_sensor3);
int switch4 = digitalRead(current_sensor4);

int current_status = switch1*1+switch2*2+switch3*4+switch4*8;

return  current_status;
}


const char ssid[] = "kk_nivas";
const char pass[] = "9495989074";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("arduino", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("R1");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
if(payload=="S1ON")
{
  Serial.println("switch one on");
   update_one_digit(0);
  }
  if(payload=="S1OFF")
{
  Serial.println("switch one off");
   update_one_digit(1);
  }
}


void update_one_digit(int data)
{
  
 // int i;
  byte pattern;
  
  // get the digit pattern to be updated
  pattern = digit_pattern[data];

  // turn off the output of 74HC595
  digitalWrite(digit_clock_pin, LOW);
  
  // update data pattern to be outputed from 74HC595
  // because it's a common anode LED, the pattern needs to be inverted
  shiftOut(data_pin, bit_clock_pin, LSBFIRST, ~pattern);
  
  // turn on the output of 74HC595
  digitalWrite(digit_clock_pin, HIGH);
}


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); 

WiFi.begin(ssid, pass);


  pinMode(data_pin, OUTPUT);
  pinMode(bit_clock_pin, OUTPUT);
  pinMode(digit_clock_pin, OUTPUT); 

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("192.168.1.4", net);
  client.onMessage(messageReceived);
  connect();
 
}

void loop() {

  int i;
  unsigned int digit_base;
  char a = Serial.read();
  counter++;
  
  digit_base = 16;

client.loop();
int previous_status = Status_Read();
delay(1000);
int current_status = Status_Read();

if(previous_status != current_status)
{
  String current_status_data = "current_status_change :c" ;
  
  current_status_data += current_status;

  String previous_status_data = "previous_status_change :p"  ;
  
  previous_status_data += previous_status;
  Serial.println("current_status:c");
  Serial.println(current_status_data);
  Serial.println("state changes");
  Serial.println("data publishing ");
  Serial.println("previous_status:p");
  Serial.println(previous_status_data);
  client.publish("Master_control", current_status_data);
  client.publish("Master_control", previous_status_data);
  }
else{

  String current_status_data = "current_status :*" ;
  
  current_status_data += current_status;
  client.publish("Master_control", current_status_data);

  Serial.println("do nothing");
  client.subscribe("R1");
  }


 

}
