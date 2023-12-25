/*
// 黑白線識別模組 FC-51

#include <IRremnote.h>
int Recv_Pin_Right = 12; //車子右邊的紅外線反射感測器
int Recv_Pin_Left = 13;  //車子左邊的紅外線反射感測器

IRrecv irrecvRight(Recv_Pin_Right); //宣告紅外線接收物件，叫irrecvRight
IRrecv irrecvLeft(Recv_Pin_Left); //宣告紅外線接收物件，叫irrecvLeft
decode_results = result; //宣告一個儲存接收值，叫result


void setup(){
    Serial.begin(9600);
// 啟動紅外線接收
    irrecvRight.enableIRIn();
    irrecvLeft.enableIRIn();
}
void loop(){
    if(irrecvRight.decode(&result) and irrecvLeft.decode(&result)){ 
        //decode 解析紅外線接收值，如果回傳true，代表有接收到新資料；result 儲存接收值
        Serial.println(result.value, HEX) //讀取解析後的值，16進位輸出
        irrecv.resume(); //準備接收下一筆資料
    }

}*/
