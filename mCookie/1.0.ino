#include <ESP8266.h>
#include <U8glib.h>
#ifdef ESP32
#error "This code is not recommended to run on the ESP32 platform! Please check your Tools->Board setting."
#endif

#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1284P__) || defined (__AVR_ATmega644P__) || defined(__AVR_ATmega128RFA1__)
#define EspSerial Serial1
#define UARTSPEED  115200
#endif

#if defined (__AVR_ATmega168__) || defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); /* RX:D2, TX:D3 */
short hour=0;     //用户取咖啡的时间
char order;
short Hour=0, Minute=0;     //设置时间

#define INTERVAL_LCD 20 //定义OLED刷新时间间隔 
unsigned long lcd_time = millis(); //OLED刷新时间计时器
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE); //设置OLED型号 
//-------字体设置，大、中、小
#define setFont_L u8g.setFont(u8g_font_7x13)
#define setFont_M u8g.setFont(u8g_font_osb21)
#define setFont_S u8g.setFont(u8g_font_fixed_v0r)
#define setFont_SS u8g.setFont(u8g_font_04b_03bn)


#define EspSerial mySerial
#define UARTSPEED  9600
#endif

#define SSID        F("JWC")
#define PASSWORD    F("12345678")
#define HOST_NAME   F("api.heclouds.com")
#define HOST_PORT   (80)
//设置WiFi名称及密码（千万别用中文），WiFi模块有时候会抽风连不上，多试几次就好

static const byte  GETDATA[]  PROGMEM = {
 "GET https://api.heclouds.com/devices/562233664/datapoints?datastream_id=order,hour,minute&limit=1 HTTP/1.1\r\nHost:api.heclouds.com\r\napi-key:7AHL6HLQEDOSQtTzwBMjw7kEuaw=\r\nConnection: close\r\n\r\n"
};
//onenet的域名是api.heclouds.com，562233664填写自己onenet的设备ID，datastream_id=___填写onenet上需要的数据名称，api-key:___填写自己的api-key

ESP8266 wifi(&EspSerial);
const int Relay =  6; 
void setup(void)
{
  Serial.begin(115200);
  delay(100);
  pinMode(Relay, OUTPUT);
  WifiInit(EspSerial, UARTSPEED);
}
void loop()
{
    online();
//    Serial.print("现在的时间是：");
//    Serial.print(Hour);
//    Serial.print(":");
//    Serial.print(Minute);
//    Serial.print('\n');
//    Serial.print("奶茶种类：");
//    Serial.print(order);
//    Serial.print('\n');
//    Serial.print("取餐时间：");
//    Serial.print(hour);
//    Serial.print("点");
//    Serial.print('\n');
// 调试时间是否与网络时间一致
    u8g.firstPage();
     do {
     setFont_L;
     u8g.setPrintPos(0, 10);
     u8g.print("CURRENT TIME:");
     u8g.setPrintPos(25, 25);
     u8g.print(Hour);
     u8g.setPrintPos(40, 25);
     u8g.print(':');
     u8g.setPrintPos(50, 25);
     u8g.print(Minute);
     u8g.setPrintPos(0, 40);
     u8g.print("PICK UP TIME:");
     u8g.setPrintPos(25, 55);
     u8g.print(hour);
     u8g.setPrintPos(40, 55);
     u8g.print(':');
     u8g.setPrintPos(50, 55);
     u8g.print("00");
     }while( u8g.nextPage() );
    if(order=='c'||order=='g'||order=='r'||order=='p')
    {
      if(Hour==(hour-1)&&Minute==30)
          {
            digitalWrite(Relay, HIGH);
            delay(200000);
            digitalWrite(Relay, LOW);
          }          
      else
          digitalWrite(Relay, LOW);
    }  
}
void online(void)
{
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
    Serial.print(F("create tcp ok\r\n"));
  } else {
    Serial.print(F("create tcp err\r\n"));
  }
  //判断是否连接成功
  wifi.sendFromFlash(GETDATA, sizeof(GETDATA)); //从Flash读取发送内容，节约内存
  uint8_t buffer[512] = {0};
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 20000);
  Serial.print("len:");
  Serial.print(len);
  Serial.print("\r\n");
 /*   if (len > 0) {
    Serial.print(F("Received:["));
    for (uint32_t i = 0; i < len; i++) {
      Serial.print((char)buffer[i]);
    }
    Serial.print(F("]\r\n"));
   }  
   查看收到的报文
    */              
  if (len > 0) {
                  short k=0,temp=0;
                  char hold;
                  for (uint32_t i = 0; i <len; i++) 
                  {
                          if((char)buffer[i]=='D'&&(char)buffer[i+1]=='a'&&(char)buffer[i+2]=='t'&&(char)buffer[i+3]=='e')
                          {
                            Hour=((short)buffer[i+23]-48)*10+(short)buffer[i+24]-40;
                            Minute=((short)buffer[i+26]-48)*10+(short)buffer[i+27]-48;
                          }
                          //读取报文时间作为系统时间
                          if((char)buffer[i]=='v'&&(char)buffer[i+1]=='a'&&(char)buffer[i+2]=='l'&&(char)buffer[i+3]=='u'&&(char)buffer[i+4]=='e')
                                  {
                                            if((short)buffer[i+8]>=65&&(short)buffer[i+8]<=122)
                                            {
                                                hold=buffer[i+8];
//                                                Serial.print("hold:");
//                                                Serial.print(hold);
//                                                Serial.print("\r\n");
                                            }
                                            else
                                            {
                                                temp=((short)buffer[i+8]-48)*10+((short)buffer[i+9]-48);
//                                                Serial.println("temp:");
//                                                Serial.println(temp);
//                                                Serial.print("\r\n");
             
                                           };
                                           if(k==0)
                                                 {
                                                 hour=temp;
//                                                 Serial.println("hour:");
//                                                 Serial.println(hour);
//                                                 Serial.print("\r\n");
                                                 k++;
                                                 }
                                             //读取取餐时间
                                            else 
//                                            {
//                                                  if(k==1) 
                                                   {
                                                     order=hold;
//                                                     Serial.println("order:");
//                                                     Serial.println(order);
//                                                     Serial.print("\r\n");
                                                     k++;
                                                   }
                                               //读取点餐种类
//                                                   else 
//                                                   {
//                                                       minute=temp;
//                                                       Serial.println("minute:");
//                                                       Serial.println(minute);
//                                                       Serial.print("\r\n");
//                                                       k++;
//                                                   }
//                                           }      
                                    } 
                              }
                       }
              delay(5000);
      }
