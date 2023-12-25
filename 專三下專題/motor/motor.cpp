
#include "motor.h" //導入motor.h的內容
Motor::Motor(byte IB1, byte IA1, byte IB2, byte IA2){ //Motor的建構子
// 儲存接腳
  // this -> ENA = ENA;
  // this -> ENB = ENB;
  this -> IB1 = IB1;
  this -> IA1 = IA1;
  this -> IB2 = IB2;
  this -> IA2 = IA2;

// 全部接腳都設為輸出
  // pinMode(ENA, OUTPUT);
  // pinMode(ENB, OUTPUT);
  // pinMode(IN1, OUTPUT);
  // pinMode(IN2, OUTPUT);
  // pinMode(IN3, OUTPUT);
  // pinMode(IN4, OUTPUT);
}

void Motor::drive(Modes mode, int pwmA = 0, int pwmB = 0){ //Motor的drive
  // 限制馬達pwm的範圍，若是使用analog(類比)時才會用到
  // byte pwnA = constrain(pwmA, 0, 255); //constrain 限制pwm的範圍
  // byte pwmB = constrain(pwmB, 0, 255);

// 若馬達現在的模式與之前不同，先暫停0.1秒(Stop)
if(this -> mode != mode){
  this -> mode = mode; //更新之前馬達的值
  // 停止馬達
  analogWrite(IB1, pwmB);
  analogWrite(IA1, pwmB);
  analogWrite(IB2, pwmB);
  analogWrite(IA2, pwmB);
  delay(100);
  // Serial.println(mode); //為Forward ...
}

  switch(mode){ //mode裡面會有 Forward, Backward, Right, Left, Stop
  //前進和後退是相反的；
  // 前進  
    case Forward:
      analogWrite(IB1, pwmB);  //LOW
      analogWrite(IA1, pwmA);  //HIGH
      analogWrite(IB2, pwmB);  //LOW
      analogWrite(IA2, pwmA);  //HIGH
      break;

  // 後退
    case Backward:
      analogWrite(IB1, pwmA); //HIGH
      analogWrite(IA1, pwmB);  //LOW
      analogWrite(IB2, pwmA); //HIGH
      analogWrite(IA2, pwmB);  //LOW
      break;

  // 右轉
    case Right:
      analogWrite(IB1, pwmA); //HIGH
      analogWrite(IA1, pwmB);  //LOW
      analogWrite(IB2, pwmB);  //LOW
      analogWrite(IA2, pwmA); //HIGH
      break;
  // 左轉
    case Left:
      analogWrite(IB1, pwmB);  //LOW
      analogWrite(IA1, pwmA); //HIGH
      analogWrite(IB2, pwmA); //HIGH
      analogWrite(IA2, pwmB);  //LOW
      break;
  
  // 停止
    case Stop:
      default:
      analogWrite(IB1, pwmB); //LOW
      analogWrite(IA1, pwmB); //LOW
      analogWrite(IB2, pwmB); //LOW
      analogWrite(IA2, pwmB); //LOW
      break;
  }
}
