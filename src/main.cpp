#include <Arduino.h>

#include <ps5Controller.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ps5.begin("10:18:49:fc:f0:ee"); //コントローラーのMACアドレス
  Serial.println("Ready.");
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
}

void loop() {
  // put your main code here, to run repeatedly:

  float max_vel = 6.0; //[m/min]
  float rot_max_vel = PI*60; //[rad/min]
  
  while (ps5.isConnected() == true) {
    //{pad,↑,↓,→,←,〇,◇,△,×,R1,L1,R3,L3}
    int Button1[13] = {
      ps5.Touchpad(),// 0
      ps5.Up(),// 1
      ps5.Down(),// 2
      ps5.Right(),// 3
      ps5.Left(),// 4
      ps5.Circle(),// 5
      ps5.Square(),// 6
      ps5.Triangle(),// 7
      ps5.Cross(),// 8
      ps5.R1(),// 9
      ps5.L1(),// 10
      ps5.R3(),// 11
      ps5.L3(),// 12
    }; 
    
    //{R2,L2,RSx,RSy,LSx,LSy}
    int Button2[6] = {
      ps5.R2Value(),// 0
      ps5.L2Value(),// 1
      ps5.RStickX(),// 2
      ps5.RStickY(),// 3
      ps5.LStickX(),// 4
      ps5.LStickY(),// 5
    };

    int i;
    for (i = 0; i < 13; i++) {
    Serial.println(Button1[i]);
    }

    for (i = 0; i < 6; i++) {
    Serial.println(Button2[i]);
    }
    uint8_t data[8];
    data[0] = (uint8_t)(ps5.R2Value());
    data[1] = (uint8_t)(ps5.L2Value());
    data[2] = (uint8_t)(ps5.RStickX());
    data[3] = (uint8_t)(ps5.LStickX());
    data[4] = (uint8_t)(ps5.RStickY());
    data[5] = (uint8_t)(ps5.LStickY());
    data[6] =
    (int)(ps5.Up()) << 6|
    (int)(ps5.Down()) << 5 |
    (int)(ps5.Right()) << 4 |
    (int)(ps5.Left()) << 3 |
    (int)(ps5.Options()) << 2 |
    (int)(ps5.Share()) << 1 |
    (int)(ps5.PSButton());
    data[7] =
    (int)(ps5.Touchpad()) << 6 |
    (int)(ps5.R1()) << 5 |
    (int)(ps5.L1()) << 4 |
    (int)(ps5.Circle()) << 3 |
    (int)(ps5.Square()) << 2 |
    (int)(ps5.Triangle()) << 1 |
    (int)(ps5.Cross());
    for(int i = 0; i < 8; i++)
    {
      if(data[i] == 0xFF) data[i]--;
    }
    Serial2.printf("%c", 0xFF);
    for(int i = 0; i < 8; i++) Serial2.printf("%c", data[i]);
    delay(10);
  }
}