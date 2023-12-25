//正確版(尚未刪減過的)

// #include <ESP8266WiFi.h>          //引用library
// #include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

SoftwareSerial NodeMcu_SoftSerial(D1, D2); //ESP8266 D1->12,D2->11
ESP8266WebServer server(80);      //在埠口80建立網站伺服器，server是個自動的伺服器物件

//wifi名稱 與 wifi密碼
String ssid = "wifi名稱";       //ivescream
String password = "wifi密碼";   //ivescream
char Send_Information;          //esp8266 arduino deliver information
String HTML = "\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <title>防疫遙控車</title>\
    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js\"></script>\
    <script>\
        var IP = \"192.168.1.101\";\
         $(document).ready(function() {\
            $(\"#Forward\").mousedown(function() {\
                alert(`http://${IP}/Forward`);\
                window.location.replace(`http://${IP}/Forward`);\
            });\
            $(\"#Backward\").mousedown(function() {\
                alert(`http://${IP}/Backward`);\
                window.location.replace(`http://${IP}/Backward`);\
            });\
            $(\"#Left\").mousedown(function() {\
                alert(`http://${IP}/Left`);\
                window.location.replace(`http://${IP}/Left`);\
            });\
            $(\"#Right\").mousedown(function() {\
                alert(`http://${IP}/Right`);\
                window.location.replace(`http://${IP}/Right`);\
            });\
            $(\"#Stop\").mousedown(function() {\
                alert(`http://${IP}/Stop`);\
                window.location.replace(`http://${IP}/Stop`);\
            });\
            $(\"#RealTimeCall\").mousedown(function() {});\
            $(\"#RealTimeVideo\").mousedown(function() {});\
            $(\"button\").mouseleave(function() {\
            });\
        });\
    </script>\
    <style>\
        table {\
            color: white;\
            width: 300px;\
            height: 300px;\
            border: 1px solid black;\
            background-color: #6495ED;\
            margin: 0px 10px;\
        }\
        tr td {\
            width: 70px;\
            height: 70px;\
            text-align: center;\
            padding: 8px;\
        }\
        iframe {\
            width: 600;\
            height: 200px;\
            background-color: beige;\
        }\
        button {\
            color: black;\
            background-color: aquamarine;\
            width: 70px;\
            height: 70px;\
        }\
    </style>\
</head>\
<body>\
    <h1>防疫遙控車UI介面</h1>\
    <iframe></iframe>\
    <br><br>\
    <h1>自走車網頁遙控器</h1>
    <iframe></iframe>
    </br>\
    </br>\
    <table>\
        <tr>\
            <td></td>\
            <td> <button id=\"Forward\">前進</button></td>\
            <td></td>\
        </tr>\
        <tr>\
            <td>\
                <button id=\"Left\">左轉</button></td>\
            <td>\
                <button id=\"Stop\">急剎</button></td>\
            <td><button id=\"Right\">右轉</button></td>\
        </tr>\
        <tr>\
            <td></td>\
            <td><button id=\"Backward\">後退</button>\
            </td>\
            <td></td>\
        </tr>\
    </table>\
    <div></div>\
</body>\
</html>";

//Server
void Server(){
    // WiFi.mode(WIFI_AP);            //設為STA模式(WiFi終端)；用來上網讀取資料
    delay(100);                     //等待0.1秒以免速度太快打結
    Serial.print("Cinnecting to ");
    Serial.println(ssid);          //顯示即將連接的WiFi名稱
    //連接動態IP位址
    WiFi.begin(ssid, password);    //使用wifi和password開始連線；
    //WiFi.begin(ssid);            //連接的wifi不需要密碼
//連接靜態IP位址

  while(WiFi.status() != WL_CONNECTED){ //還沒連線時會一直跳出.；WiFi.status() 連接狀態 WL_CONNECTED 代表以連接的常數
    delay(1000);
    Serial.print("."); //以表示等待連線
    }
    Serial.println();
    Serial.println("WiFi connected"); //連接成功
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());   //伺服器被分到的區網IP
    Serial.print("WiFi RSSI");
    Serial.println(WiFi.RSSI() + "dBm");      //WiFi強度(Received Signal Strength Indication)；強度在-67dBm以上最好，-80dBm以下代表網路很不穩定
}

//初始頁面
void handleRoot(){ // \"就能在字串中當作單純的符號來看待
    Send_Information = 101; //e
    server.send(200, "text/html", HTML);
//  server.send(狀態碼, 內容類型, 內容)

}

//Forward前進
void Forward(){
    Send_Information = 97; //a，也可以是'a'
    server.send(200, "text/html", HTML);
    digitalWrite(LED_BUILTIN, LOW);
}

void Backward(){
    Send_Information = 98; //b，也可以是'b'
    server.send(200, "text/html", HTML);
    digitalWrite(LED_BUILTIN, HIGH);
}

void Left() {
    Send_Information = 99; //c，也可以是'c'
    server.send(200, "text/html", HTML);
}
void Right(){
    Send_Information = 100; //d，也可以是'd'
    server.send(200, "text/html", HTML);
}
void Stop(){
    Send_Information = 101; //e，也可以是'd'
    server.send(200, "text/html", HTML);
}
void RealTimeCall(){}
void RealTimeVideo(){}
void setup() {
    Serial.begin(9600);
    NodeMcu_SoftSerial.begin(9600);
    // pinMode(D1, OUTPUT);
    // pinMode(D2, INPUT); 
    pinMode(LED_BUILTIN, OUTPUT);
    Server();
  //頁面
    server.on("/", handleRoot);                 //處理首頁的路由器
    server.on("/Forward", Forward);             //前
    server.on("/Backward", Backward);           //後
    server.on("/Left", Left);                   //左
    server.on("/Right", Right);                 //右
    server.on("/Stop", Stop);                   //停
    server.on("/RealTimeCall", RealTimeCall);   //通話
    server.on("/RealTimeVideo", RealTimeVideo); //視訊

//------------------------------------------------
//處理Get或Set請求；參數，測試成功
//   server.on("/sw", [](){
//     String state =server.arg("led"); //伺服器物件.arg("Get或Post參數名稱")
//     if(state == "on"){
//       digitalWrite(LED_BUILTIN, LOW);
//     }else if(state == "off"){
//       digitalWrite(LED_BUILTIN, HIGH);
//     }
//     server.send(200, "text/html", "Len is <b>" + state + "</b>.");
//   });
    server.begin(); //啟動網站伺服器
}

void loop() {
    while(true) {
        server.handleClient(); //處理客戶端連線，若是沒有它以上做的都是白工
        Serial.println(Send_Information);
        NodeMcu_SoftSerial.print(Send_Information);
        // NodeMcu_SoftSerial.print("Information");
        // Serial.print("Information");
        NodeMcu_SoftSerial.print("\n");
        delay(1000);    
    }
}


/*
 ESP8266 Arduino Core  https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html
http://www.taichi-maker.com/homepage/iot-development/iot-dev-reference/esp8266-c-plus-plus-reference/
*/
