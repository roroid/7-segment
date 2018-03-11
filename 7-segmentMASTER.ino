#include <Wire.h>
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
}
int nDevices, u;
int adrese[10];
int contor = 999;
void loop() {
  // put your main code here, to run repeatedly:
  scanare();//make a scann to see if aditional digits were added
  for (int j = 0; j <= contor; j++) {
    if (j <= (contor % powint(10, nDevices))) {
      numar(j);
      delay(100);
    }
  }

  delay(5000);
}


// transmit to device
void numar(int nr) {
  for (int i = 0; i < nDevices; i++) {
    u = ((nr / powint(10, i)) % 10);
    Wire.beginTransmission(adrese[nDevices - i - 1]);
    Wire.write(u);
    Wire.endTransmission();
  }
}

void scanare() {
  byte error, address;
  nDevices = 0;
  for (address = 1; address < 10; address++ )
  { Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    { adrese[nDevices] = address;
      nDevices++;
    }
  }
}

//function used for rais an int at a specific power
int powint(int x, int y)
{
  int val = x;
  for (int z = 0; z <= y; z++)
  {
    if (z == 0)
      val = 1;
    else
      val = val * x;
  }
  return val;
}
