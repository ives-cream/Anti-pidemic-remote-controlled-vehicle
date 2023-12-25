#include <SoftwareSerial.h>

SoftwareSerial testSerial(11,12); //RX, TX
char data;

void setup() {
  Serial.begin(9600);
  testSerial.begin(9600);
  pinMode(11,INPUT);
  pinMode(12,OUTPUT);
  Serial.println("GO!");
}

void loop() {
   if (testSerial.available()){
     // Serial.write(testSerial.read());
      data = testSerial.read();
      Serial.println(data);
   }
}
      



// data = testSerial.available();
// switch (data) {
    // // Serial.println(testSerial.available());
    //   case '1': //61
    //     Forward();
    //     break;  
    //   case '2': //62
    //     Backward();
    //     break;
    //   case '3': //63
    //     Stop();
    //     break;
    // }
//----------------------------------------------------------------
/*
void setup(){
    Serial.begin(9600);
}
void loop(){
    Serial.print("Hello ");
    Serial.println("World");
    delay(1000);
}
*/