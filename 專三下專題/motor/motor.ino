/*
//right motor
//IA1 輸入 H，IB1 輸入 L，(OA1 OB1)馬達正轉
//IB2 輸入 L，IA2 輸入 H，(OA1 OB1)馬達反轉
//left motor
//IB1 輸入 H，IA1 輸入 L，(OA2 OB2)馬達正轉
//IB2 輸入 L，IA2 輸入 H，(OA2 OB2)馬達反轉


//IB1(IN1)=7 pwmA, IA1(IN2)=8, IB2(IN3)=9 pwmB, IA2(IN4)=10

#include </Users/wei/Desktop/三下專題/motor/motor.h>
#include </Users/wei/Desktop/三下專題/motor/HCSOR05.h>
// #include <Arduino.h>
// #include <HCSR05.h>

// 定義接腳；
//左輪
#define IB1 A5  //IN1 A5 6  IB1 | 11 b2
#define IA1 A4  //IN2 A4 7  IA1 | 10 b1
//右輪
#define IB2 A3  //IN3 A3 8  IB2 | 6  a2
#define IA2 A2  //IN4 A2 9  IA2 | 5  a1


#define echo 10
#define trig 11

const byte pwm = 200; //馬達pwn的輸出值
int thresh = 10;      //距離上限10公分
long distance;        //偵測距離
HCSR05 sr05(trig, echo);  //超音波trig, echo
Motor motor(IB1, IA1, IB2, IA2); //呼叫Motor的建構子

void setup(){
  // 馬達接腳設為輸出
  pinMode(IB1, OUTPUT);
  pinMode(IA1, OUTPUT);
  pinMode(IB2, OUTPUT);
  pinMode(IA2, OUTPUT);
  // 超音波接腳設定
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  //剛起步時先Stop；只跑一次
  motor.drive(Stop, pwm, 0);
  Serial.begin(9600); //串列數據傳輸的傳輸速率(每秒9600彼特/秒)
}

void loop(){
  distance = sr05.ping(); //超音波偵測到的距離
// motor.drive(Forward, pwm, 0);
// delay(5000);
//可以用 analogWrite(腳位, 255); 或 digitalWrite(接腳, HIGH); //但接腳必須要接在analog(digital)、255為HIGH, 0為LOW

//避障功能
// if(distance > thresh) //若距離大於10cm左轉
//  {
//    motor.drive(Forward, pwm, 0); //直走
//  }
//  else{
//    motor.drive(Left, 50, 0); //左轉
//  }
//  delay(500);

//------------------------------------
      //右正 0a1,0b1
//      analogWrite(IB1, 0);  //LOW
//      analogWrite(IA1, 200); //HIGH
      //左反 0a2,0b2
//      analogWrite(IB2, 200); //HIGH
//      analogWrite(IA2, 0);  //LOW
      //右反 0a1,0b1
//      analogWrite(IB2, 0);  //LOW
//      analogWrite(IA2, 150); //HIGH
      //左正 0a2,0b2
//      analogWrite(IB1, 150); //HIGH
//      analogWrite(IA1, 0);  //LOW
      

}
*/
//------------------------------------------
/*
  //超音波(最直接的方法)
  digitalWrite(trig, LOW);
  delayMicroseconds(8);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  distance = pulseIn(echo, HIGH) / 58.00;
  Serial.println(distance);
  delay(500);
*/

/*
#include </Users/wei/Desktop/自走車/motor/motor.h>
#include </Users/wei/Desktop/自走車/motor/HCSOR05.h>

// 定義接腳
#define IB1 A5  //IN1 A5 6  IB1 | 11 b2
#define IA1 A4  //IN2 A4 7  IA1 | 10 b1
#define IB2 A3  //IN3 A3 8  IB2 | 6  a2
#define IA2 A2  //IN4 A2 9  IA2 | 5  a1
#define echo 10
#define trig 11


const byte pwm = 200; //馬達pwn的輸出值
int thresh = 10;      //距離上限10公分
long distance;        //偵測距離
HCSR05 sr05(trig, echo);  //超音波trig, echo
Motor motor(IB1, IA1, IB2, IA2); //呼叫Motor的建構子

const byte IRPins[] = {12, 13}; //黑白感測器的腳位右12左13
const byte IRnum = sizeof(IRPins);     //黑白感測器的數量
byte oldIR = 0; //先前感測器的狀況

byte checkIR(){
  byte IR = 0;
  for(byte i = 0 ; i < IRnum ; i++){
    //把黑白感測器合成二進位，用左移運算子將資料移到指定的位置
    IR |= digitalRead(IRPins[i]) << i; //先讀取黑白感測器的感測值，左移i位後；再做 or邏輯
  }
  Serial.print("IR:");
  Serial.println(IR);
  return IR;
}

void setup(){
  // 馬達接腳設為輸出
  pinMode(IB1, OUTPUT);
  pinMode(IA1, OUTPUT);
  pinMode(IB2, OUTPUT);
  pinMode(IA2, OUTPUT);
  // 黑白感測器接腳設為輸入
//  for(byte i = 0 ; i < IRnum ; i++){
//    pinMode(IRnum[i], INPUT);
//  }
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  // 超音波接腳設定
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  //剛起步時先Stop；只跑一次
  motor.drive(Stop, pwm, 0);
  Serial.begin(9600); //串列數據傳輸的傳輸速率(每秒9600彼特/秒)
}

void loop(){
  byte IR = checkIR();
  distance = sr05.ping(); //超音波偵測到的距離
// motor.drive(Forward, pwm, 0);
// delay(5000);
//可以用 analogWrite(腳位, 255); 或 digitalWrite(接腳, HIGH); //但接腳必須要接在analog(digital)、255為HIGH, 0為LOW

  if(IR = 3){
    IR = oldIR;
  }
  else if(distance > thresh) //若距離大於10cm左轉
  {
    motor.drive(Forward, pwm, 0); //直走
  }
  else if(distance <= thresh) {
    motor.drive(Left, pwm, 0); //左轉
  }
  else{
    oldIR = IR;
  }
  
  switch (IR){
    case 0:
      motor.drive(Forward, 40, 40);
    case 3:
      motor.drive(Forward, 40, 40);
      break;
    case 1:
      motor.drive(Left, 60, 30);
      break;
    case 2:
      motor.drive(Right, 30, 60);
      break;
  default:
    motor.drive(Stop);
    break;
  }
  delay(5000);
}
*/
