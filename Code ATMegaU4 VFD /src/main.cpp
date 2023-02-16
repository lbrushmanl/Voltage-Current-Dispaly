#include <Arduino.h>

#define VOLTAGE A5
#define CURRENT A4

#define DATA 4
#define CLK 12
#define STR 6

#define GRID_NUMBER 11
#define VOLTAGE_CONVERSION_FACTOR 29.3255131965 // 30/1023 * 1000
#define CURRENT_CONVERSION_FACTOR 4.88758553 //5.8651026393 // 6/1023 * 1000

void display(uint16_t, uint16_t);

uint16_t voltage = 12345;
uint16_t current = 34577;

void setup() {
  Serial.begin(9600);
  pinMode(DATA, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(STR, OUTPUT);

  digitalWrite(STR, HIGH);
  digitalWrite(DATA, HIGH);
  digitalWrite(CLK, HIGH);

//Set up interrupt
cli();
TCCR1A = 0;
TCCR1B = 0;
TCNT1 = 0;

OCR1A = 1000;
TCCR1A |= (1 << WGM11);
TCCR1B |= (1 << CS12) | (1 << CS10);  
TIMSK1 |= (1 << OCIE1A);

sei();
}

ISR(TIMER1_COMPA_vect) 
{
  float vc = analogRead(VOLTAGE) * VOLTAGE_CONVERSION_FACTOR;
  float cc = analogRead(CURRENT) * CURRENT_CONVERSION_FACTOR;
  voltage = vc;
  current = cc;
}

void loop() {  
  display(voltage, current);
}

// Data Setup
// BCD		Grids
// A B C D DP G1 G2 G3 G4 G5 G7 G8 G9 G10 G11
// 0 0 0 1 0 0 1 1 1 1 1 1 1 1 1 0 0 


//As the level shifter I made is shit and acts as an inverter the code is inverted to how u would normal put data in to shift registers. Next time ill use the bidirectional level shifter
void display(uint16_t voltage, uint16_t current) 
{

  uint32_t bin = (voltage * 100000) + current;
  

  for (uint8_t grid_index = 0; grid_index < GRID_NUMBER; grid_index++)
  {
    uint16_t display_value = 0;
    // Extracts each value from a number
    display_value = (bin % 10);
    bin /= 10;

    // // Ensures that only spacific grids can be energises
    if (grid_index == 6)
    {
      grid_index = 7;
    } else if (grid_index == 4 || grid_index == 9) 
    {
      display_value += 1 << 4;
    }
    
    // Moves to the next grid
    display_value += 1 << (15 - grid_index);

    digitalWrite(STR, HIGH);
    for (uint8_t i = 0; i < 16; i++)  {
        digitalWrite(DATA, (display_value & 32768) == 0);
        display_value <<= 1;
        digitalWrite(CLK, LOW);
		    digitalWrite(CLK, HIGH);
    }		
    digitalWrite(STR, LOW);
    digitalWrite(STR, HIGH);
  }
}