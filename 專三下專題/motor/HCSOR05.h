#ifndef HCSR05.h
#define HCSQ05.h

class HCSR05
{
  byte trig;
  byte echo;
  public:
  HCSR05(byte trigPin, byte echoPin){
    trig = trigPin; //trig可改成this->trig;
    echo = echoPin; //echo可改成this->echo;
    
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
  }
  float ping(){  //操音波感測
    unsigned long d;
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    d = pulseIn(echo, HIGH, 23200);
    return d/58.0;
  }
};
#endif
