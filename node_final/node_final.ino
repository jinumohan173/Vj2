/* 
AUTHOR : JinuMohan
company : VJ2
DOC     :09-03-2019
TOC     : 12.00 AM
*/
//relay4 is series
//rl3 is parallel
//qo-series
//q1-parallel


#include <ESP8266WiFi.h>
#include <MQTT.h>
// pin 11 of 74HC595 (SHCP)
const int bit_clock_pin = D2;
// pin 12 of 74HC595 (STCP)
const int digit_clock_pin = D1;
// pin 14 of 74HC595 (DS)
const int data_pin = D0;

int count = 0;

int current_sensor1 = D3;
int current_sensor2 = D4;//change thid to D4 at final stage
int current_sensor3 = D5;
int current_sensor4 = D6;


// digit pattern for a 7-segment display
const byte digit_pattern[256] =
{
B11111111, //1
B11111110, //0
B11111101, //2
B11111100, //3
B11111011, //4
B11111010, //5
B11111001, //6
B11111000, //7
B11110111, //8
B11110110, //9
B11110101, //01
B11110100, //00
B11110011, //02
B11110010, //03
B11110001, //04
B11110000, //05
B11101111, //06
B11101110, //07
B11101101, //08
B11101100, //09
B11101011, //21
B11101010, //20
B11101001, //22
B11101000, //23
B11100111, //24
B11100110, //25
B11100101, //26
B11100100, //27
B11100011, //28
B11100010, //29
B11100001, //31
B11100000, //30
B11011111, //32
B11011110, //33
B11011101, //34
B11011100, //35
B11011011, //36
B11011010, //37
B11011001, //38
B11011000, //39
B11010111, //41
B11010110, //40
B11010101, //42
B11010100, //43
B11010011, //44
B11010010, //45
B11010001, //46
B11010000, //47
B11001111, //48
B11001110, //49
B11001101, //51
B11001100, //50
B11001011, //52
B11001010, //53
B11001001, //54
B11001000, //55
B11000111, //56
B11000110, //57
B11000101, //58
B11000100, //59
B11000011, //61
B11000010, //60
B11000001, //62
B11000000, //63
B10111111, //64
B10111110, //65
B10111101, //66
B10111100, //67
B10111011, //68
B10111010, //69
B10111001, //71
B10111000, //70
B10110111, //72
B10110110, //73
B10110101, //74
B10110100, //75
B10110011, //76
B10110010, //77
B10110001, //78
B10110000, //79
B10101111, //81
B10101110, //80
B10101101, //82
B10101100, //83
B10101011, //84
B10101010, //85
B10101001, //86
B10101000, //87
B10100111, //88
B10100110, //89
B10100101, //91
B10100100, //90
B10100011, //92
B10100010, //93
B10100001, //94
B10100000, //95
B10011111, //96
B10011110, //97
B10011101, //98
B10011100, //99
B10011011, //011
B10011010, //010
B10011001, //012
B10011000, //013
B10010111, //014
B10010110, //015
B10010101, //016
B10010100, //017
B10010011, //018
B10010010, //019
B10010001, //001
B10010000, //000
B10001111, //002
B10001110, //003
B10001101, //004
B10001100, //005
B10001011, //006
B10001010, //007
B10001001, //008
B10001000, //009
B10000111, //021
B10000110, //020
B10000101, //022
B10000100, //023
B10000011, //024
B10000010, //025
B10000001, //026
B10000000, //027
B01111111, //028
B01111110, //029
B01111101, //031
B01111100, //030
B01111011, //032
B01111010, //033
B01111001, //034
B01111000, //035
B01110111, //036
B01110110, //037
B01110101, //038
B01110100, //039
B01110011, //041
B01110010, //040
B01110001, //042
B01110000, //043
B01101111, //044
B01101110, //045
B01101101, //046
B01101100, //047
B01101011, //048
B01101010, //049
B01101001, //051
B01101000, //050
B01100111, //052
B01100110, //053
B01100101, //054
B01100100, //055
B01100011, //056
B01100010, //057
B01100001, //058
B01100000, //059
B01011111, //061
B01011110, //060
B01011101, //062
B01011100, //063
B01011011, //064
B01011010, //065
B01011001, //066
B01011000, //067
B01010111, //068
B01010110, //069
B01010101, //071
B01010100, //070
B01010011, //072
B01010010, //073
B01010001, //074
B01010000, //075
B01001111, //076
B01001110, //077
B01001101, //078
B01001100, //079
B01001011, //081
B01001010, //080
B01001001, //082
B01001000, //083
B01000111, //084
B01000110, //085
B01000101, //086
B01000100, //087
B01000011, //088
B01000010, //089
B01000001, //091
B01000000, //090
B00111111, //092
B00111110, //093
B00111101, //094
B00111100, //095
B00111011, //096
B00111010, //097
B00111001, //098
B00111000, //099
B00110111, //211
B00110110, //210
B00110101, //212
B00110100, //213
B00110011, //214
B00110010, //215
B00110001, //216
B00110000, //217
B00101111, //218
B00101110, //219
B00101101, //201
B00101100, //200
B00101011, //202
B00101010, //203
B00101001, //204
B00101000, //205
B00100111, //206
B00100110, //207
B00100101, //208
B00100100, //209
B00100011, //221
B00100010, //220
B00100001, //222
B00100000, //223
B00011111, //224
B00011110, //225
B00011101, //226
B00011100, //227
B00011011, //228
B00011010, //229
B00011001, //231
B00011000, //230
B00010111, //232
B00010110, //233
B00010101, //234
B00010100, //235
B00010011, //236
B00010010, //237
B00010001, //238
B00010000, //239
B00001111, //241
B00001110, //240
B00001101, //242
B00001100, //243
B00001011, //244
B00001010, //245
B00001001, //246
B00001000, //247
B00000111, //248
B00000110, //249
B00000101, //251
B00000100, //250
B00000011, //252
B00000010, //253
B00000001, //254
B00000000, //255

};






int Status_Read()
{
int switch1 = digitalRead(current_sensor1);
int switch2 = digitalRead(current_sensor2);
int switch3 = digitalRead(current_sensor3);
int switch4 = digitalRead(current_sensor4);

int current_status = switch1*1+switch2*2+switch3*4+switch4*8;

return  current_status;
}


const char ssid[] = "Jinumohan173";
const char pass[] = "jinu#9495";

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

}

void messageReceived(String &topic, String &payload) {
 Serial.println("incoming: " + topic + " - " + payload);


Serial.println(payload[0]);
Serial.println(payload[1]);
Serial.println(payload[2]);
int a1 = payload[0];
int a2 = payload[1];
int a3 = payload[2];
//Serial.println(a1);
int update_array = (a1-48)*100+(a2-48)*10+(a3-48)*1;
Serial.println("update_array ");
Serial.println(update_array);

update_one_digit(update_array);

 

}


void update_one_digit(int data)
{
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

  
update_one_digit(0);
Serial.begin(9600); 
WiFi.begin(ssid, pass);


  pinMode(data_pin, OUTPUT);
  pinMode(bit_clock_pin, OUTPUT);
  pinMode(digit_clock_pin, OUTPUT); 


  // You need to set the IP address directly.
  client.begin("192.168.1.104", net);
  client.onMessage(messageReceived);
  connect();
 
}



  




void loop() 
{
int previous_status = Status_Read();
delay(960);
int current_status = Status_Read();
Serial.println("looooopppppppp");

if(previous_status != current_status)
{
  client.loop();
  delay(20);
  Serial.println("state change******************************************");
  String current_status_data = "current_status_change R:#" ;  
  current_status_data += current_status;
  update_one_digit(0);
  Serial.println(current_status_data);
  client.publish("Master_control", current_status_data);
  Serial.println("data published ####################");
  delay(5000) ;
 // count = 0; 
  }
  else
  {
  Serial.println("current_status_data: ");
  String current_status_data = "current_status :*" ;
  current_status_data += current_status;
  client.publish("Master_control", current_status_data);
  Serial.println(current_status_data); 
  
   
  Serial.println("do nothing"); 
  client.loop();
  delay(1000);

   }

}
