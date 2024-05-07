#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#include "wifi_setting.h"
#define PIN 27        //INが接続されているピンを指定
#define NUMPIXELS 74  //LEDの数を指定
const int digitSegments[10][18] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 },  // 0
  { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },  // 1
  { 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },  // 2
  { 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1 },  // 3
  { 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1 },  // 4
  { 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1 },  // 5
  { 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // 6
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1 }   // 9
};

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);  //800kHzでNeoPixelを駆動

int flag;//:を点滅させるフラグ
unsigned long previousTime;
unsigned long ntptime;

struct tm timeInfo;  //時刻を格納するオブジェクト


void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (WiFi.begin(ssid, password) != WL_DISCONNECTED) {
    ESP.restart();
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  Serial.println("Connected to the WiFi network!");

  configTime(9 * 3600L, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");  //NTPの設定

  //wifi 取得周期
  //  prev = 0;         // 前回実行時刻を初期化
  //  interval = 100;   // 実行周期を設定


  pixels.begin();  //NeoPixelを開始
  int flag = 1;
  ntpacces();
}



void ShowTime(int hour, int minute) {
  /* ShowTime関数は、構造型(struct)の変数を受け取れるので、ShowTime関数の中に、LED画面に表示するコードを追加する。*/
  int time_4_digits = hour * 100 + minute;
  //Serial.println(time_4_digits);
  int s[4];
  for (int i = 3; i >= 0; i--) {
    s[i] = time_4_digits % 10;
    time_4_digits = (time_4_digits - s[i]) / 10;
  }

  // Serial.print(s[0]);
  // Serial.print(s[1]);
  // Serial.print(s[2]);
  // Serial.println(s[3]);


  pixels.clear();

  //  int digitSegments1 = digitSegments[s[i]][x] - 1;
  for (int i = 0; i < 4; i++) {     //各ケタ
    for (int j = 0; j < 18; j++) {  //1ケタ分のLED（18個）の表示
      int index = i * 18 + j;
      // if (i == 2) {
      //   pixels.setPixelColor(index + 2, pixels.Color(100 * digitSegments[s[i]][j], 100 * digitSegments[s[i]][j], 100 * digitSegments[s[i]][j]));
      // } else if (i == 3) {
      //   pixels.setPixelColor(index + 2, pixels.Color(100 * digitSegments[s[i]][j], 100 * digitSegments[s[i]][j], 100 * digitSegments[s[i]][j]));
      // } else {
      //   pixels.setPixelColor(index, pixels.Color(100 * digitSegments[s[i]][j], 100 * digitSegments[s[i]][j], 100 * digitSegments[s[i]][j]));
      // }

      if (i == 2) {
        pixels.setPixelColor(index + 2, pixels.ColorHSV(index * (65535/74), 255, 200 * digitSegments[s[i]][j]));//hue(色),色彩、明るさ
      } else if (i == 3) {
        pixels.setPixelColor(index + 2, pixels.ColorHSV(index * (65535/74), 255, 200 * digitSegments[s[i]][j]));
      } else {
        pixels.setPixelColor(index, pixels.ColorHSV(index * (65535/74), 255, 200 * digitSegments[s[i]][j]));
      }
    }
  }
  

  pixels.setPixelColor(36, pixels.Color(flag*100, flag*100, flag*100));//1の時[:]点灯
  pixels.setPixelColor(37, pixels.Color(flag*100, flag*100, flag*100));


  pixels.show();  //LEDに色を反映
  
  
}


void loop() {

  Clock();//1秒カウントアップ
  ShowTime(timeInfo.tm_hour, timeInfo.tm_min);
  if(millis() - ntptime > 180*1000){//ntpをとった時間から180秒たったら
    ntpacces();
  }
  
}

void Clock(){
  if (millis() - previousTime >= 1000) {   //プログラムが経過した時間が1秒経ったら
    previousTime = millis();   //基準時間に現在時間を代入
    flag = flag ^1; //1秒ごとに点灯
    timeInfo.tm_sec+=1; //1秒カウントアップ
    if(timeInfo.tm_sec == 60){
      timeInfo.tm_sec = 0;
      timeInfo.tm_min += 1;
      if(timeInfo.tm_min == 60){
        timeInfo.tm_min = 0;
        timeInfo.tm_hour += 1;
        if (timeInfo.tm_hour == 24){
          timeInfo.tm_hour = 0;
        }
      }
    }
  }
}

void ntpacces(){
  getLocalTime(&timeInfo);  //tmオブジェクトのtimeInfoに現在時刻を入れ込む
  Serial.println("ntpAcces!");
  ntptime = millis();
  Serial.print(timeInfo.tm_hour);
  Serial.print(timeInfo.tm_min);
  Serial.print(timeInfo.tm_sec);
}
