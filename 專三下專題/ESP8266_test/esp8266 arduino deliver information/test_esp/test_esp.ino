#include <SoftwareSerial.h>

SoftwareSerial NodeMcu_SoftSerial(D1, D2);

int data1;
float data2;
String data3;

void setup(){
    Serial.begin(115200);
    NodeMcu_SoftSerial.begin(115200);
}

void loop(){

    data3 = "Google";

    // NodeMcu_SoftSerial.print(data1); 
    // NodeMcu_SoftSerial.print("A");
    // NodeMcu_SoftSerial.print(data2, 5); 
    // NodeMcu_SoftSerial.print("B"); //print(資料, 小數點後幾位)
    NodeMcu_SoftSerial.print(data3); 
    NodeMcu_SoftSerial.print("Information");
    NodeMcu_SoftSerial.print("\n");
    delay(3000);
}
