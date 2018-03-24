// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

// Set MAX_ADDR to the largest address you need
// to read. For example, for the 27C512 chips,
// you'll want to use a MAX_ADDR of 65536.
// (That's 512 * 1024 / 8.)
// A 27C256 would be 256 kilobits, or 256 * 1024 / 8 =
// 32768.
#define MAX_ADDR 0xFFFF

static const uint8_t address_pins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, A0, A1, A2, A3, A6};

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output

  for(int i = 0; i < 16; i++)
  {
    pinMode(address_pins[i], OUTPUT);
    digitalWrite(address_pins[i], LOW);
  }
}

void write_address(uint32_t addr)
{

  uint32_t mask = 0x01;
  for(int i = 0; i < 16; i++)
  {
    if((mask & addr) != 0) 
    {
      digitalWrite(address_pins[i], HIGH);
    }
    else
    {
      digitalWrite(address_pins[i], LOW);
    }
    mask = mask << 1;
  }
}

void loop() {

  uint32_t addr = 0;

  while(addr < MAX_ADDR)
  {
    for (int i = 0; i < 16; i++)
    {
      write_address(addr);
      delayMicroseconds(100);
      Wire.requestFrom(8, 1);
      while(Wire.available()) {
        char c = Wire.read();
        uint8_t b = (uint8_t) c;
        Serial.print(b, HEX);
        Serial.print(" ");
        addr++;
      }
    }
    Serial.println("");
  }

  while(1) {}
}
