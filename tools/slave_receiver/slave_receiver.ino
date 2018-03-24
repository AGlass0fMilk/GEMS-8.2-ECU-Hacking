// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event

  for(int i = 2; i < 10; i++)
  {
    digitalWrite(i, HIGH);
    pinMode(i, INPUT);
  }
}

int get_data(void)
{  
  uint8_t dataLine = 0;
  uint8_t mask = 0x1;

  for(int i = 2; i < 10; i++)
  {
    if(digitalRead(i) == HIGH)
    {
      dataLine |= mask;
    }
    mask = mask << 1;
  }
  return dataLine;
}

void loop() {
  //delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(get_data());
  // as expected by master
}
