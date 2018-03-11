
#include "Seg7.h"
#include <Wire.h>

Seg7 s7;
int x, oldx;
void setup() {
  //Address handling pins
  pinMode(8, OUTPUT);  pinMode(6, INPUT);  pinMode(7, INPUT);
  digitalWrite(8, HIGH);

  int adress = 1;//here we establish the adress of the digit
  if (digitalRead(6) == HIGH) adress += 1;//here we establish the adress of the digit
  if (digitalRead(7) == HIGH) adress += 2;//here we establish the adress of the digit

  s7.set_cathode(true);
  s7.attach(10, 13, A1, A3, A0, 12, 11, A2); // attach a single 7-segment display
  /*below are the pin config
             A[10]
            _____
           |     |
    [12]F  |_____|  B[11]
           |G[13]|
    [A1]E  |_____|  C[A0]
                  o DP[A3]
             D[A2]
  */

  Serial.begin(9600);
  Serial.print(adress);
  Wire.begin(adress);                // join i2c bus with address #2
  Wire.onReceive(receiveEvent); // register event
  x = 0;
  oldx = x;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (oldx != x) {//only update if we have a change
    s7.write(x);
    oldx = x;
  }
  //delay(100);
}

//what is received via I2C is shoun on the display
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
  }
  x = Wire.read();    // receive byte as an integer
}
