// pin 11 of 74HC595 (SHCP)
const int bit_clock_pin = D2;
// pin 12 of 74HC595 (STCP)
const int digit_clock_pin = D1;
// pin 14 of 74HC595 (DS)
const int data_pin = D0;

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

void setup()
{
  pinMode(data_pin, OUTPUT);
  pinMode(bit_clock_pin, OUTPUT);
  pinMode(digit_clock_pin, OUTPUT); 
  Serial.begin(115200); 
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

void loop()
{ 
  
  int i;
  unsigned int digit_base;
  char a = Serial.read();
  counter++;
  
  digit_base = 16;

if(a=='A'){
  update_one_digit(0);  
  }
  // get the value to be displayed and update one digit
if(a=='B'){
  update_one_digit(2);  
  }

  if(a=='C'){
  update_one_digit(5);  
  }
   update_one_digit(0);  
  delay(10000);
  update_one_digit(1);  
   
  delay(10000);
  update_one_digit(2);

    delay(10000);
  update_one_digit(3);

delay(10000);
  
}

