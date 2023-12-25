 
#include <Arduino.h> //引入Arudino的標頭檔

// 定義馬達運行模式的全域變數
typedef enum{ //建立一個列舉，新的別名叫Modes，內容物包含前後左右停止
    Forward,  //前
    Backward, //後
    Left,     //左
    Right,    //右
    Stop,     //停止
} Modes; //新別名

class Motor {
    byte IB1, IA1, IB2, IA2; //控制板接腳編號
    
    public:
        Modes mode = Stop;  //記錄驅動模式；初始值為Stop
        //提前告知有Motor建構子跟drive function
        Motor(byte IB1, byte IA1, byte IB2, byte IA2); //建構子
        void drive(Modes mode, int pwmA = 0, int pwmB = 0); //行進的模式
};

/*
typedef enum  https://www.delftstack.com/zh-tw/howto/c/c-typedef-enum/
#endif  https://huenlil.pixnet.net/blog/post/24339151
*/
