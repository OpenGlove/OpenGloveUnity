
#include <Wire.h>

//Be sure to give each slave a unique address
int address = 2; 

void setup()
{
  Wire.begin(address);  // join i2c bus with address
  Wire.onRequest(deliverGloveInfo); // register event
}

void loop()
{
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void deliverGloveInfo()
{
  //declare sensors
  //U prefix indicates sensor is tracking the upper joint
  //L is lower joint
  int Uthumb,Lthumb,Uindex,Lindex,Umiddle,Lmiddle,Uring,Lring,Upinky,Lpinky;
  
  //Sensor values are mapped (m-prefix) to a value between 0-255 so they can be delivered as bytes
  byte mUthumb,mLthumb,mUindex,mLindex,mUmiddle,mLmiddle,mUring,mLring,mUpinky,mLpinky;
  
  
  //read sensors
  Uthumb = analogRead(0);
  Lthumb = analogRead(1);
  Uindex = analogRead(2);
  Lindex = analogRead(3);
  Umiddle = analogRead(4);
  Lmiddle = analogRead(5);
  Uring = analogRead(6);
  Lring = analogRead(7);
  Upinky = analogRead(8);
  Lpinky = analogRead(9);
  
  //map sensor values
  mUthumb = byte(map(Uthumb,0,1024,0,255));
  mLthumb = byte(map(Lthumb,0,1024,0,255));
  mUindex = byte(map(Uindex,0,1024,0,255));
  mLindex = byte(map(Lindex,0,1024,0,255));
  mUmiddle = byte(map(Umiddle,0,1024,0,255));
  mLmiddle = byte(map(Lmiddle,0,1024,0,255));
  mUring = byte(map(Uring,0,1024,0,255));
  mLring = byte(map(Lring,0,1024,0,255));
  mUpinky = byte(map(Upinky,0,1024,0,255));
  mLpinky = byte(map(Lpinky,0,1024,0,255));
  
  //send to master
  byte data[] = {mUthumb,mLthumb,mUindex,mLindex,mUmiddle,mLmiddle,mUring,mLring,mUpinky,mLpinky};
  Wire.write(data,10);
}

