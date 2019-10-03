/**
************************************************************
* @file         Gizwits + ArduinoUnoR3 Library 
* @brief        Datapoints handle , Gizwits Process
* @author       Gizwits
* @date         2017-08-01
* @version      V03030000
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
  v2.3
***********************************************************/
#define STEPS 100//步进电机每转步长为100

#include <Wire.h>
#include <AM2320.h>  //加载温度i2c温度传感器库
#include <pt.h>
#include "Gizwits.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include "U8glib.h"   //预加载OLED显示屏控制库
#include"Beep_tone.h" //预加载音乐库
#include <Stepper.h> //预加载步进电机控制库
#include "am2320huoqu.h"
//#include "Adafruit_Sensor.h"
//#include "Adafruit_AM2320.h"


Gizwits myGizwits;
Stepper dianji_one(STEPS, 3, 5, 4, 6); //引脚安装正常顺序接，定义引脚时中间两个要调换位置
Stepper dianji_two(STEPS, 8, 10, 9, 11); //引脚安装正常顺序接，定义引脚时中间两个要调换位置

int sudu = 60; //步进电机速度为60转/min
int i;
int jiezou = 0; //节奏
int yingyuekaishi = 0;
int xuaniufuwei = 0;
int zhuangtaipanduan = 0;
int cishu = 0;

long s = 0;   //储存当前角度

unsigned long shengyu_time; //剩余时间
unsigned long varR_set_the_time = 0;
unsigned long shengyu_time_two;//转化用
unsigned long varR_dianji_one = s;
unsigned long varW_time_left = shengyu_time_two; //Add Sensor Data Collection
//Add Sensor Data Collection
bool varR_submit = 0;
bool varR_ignition = 0;


long p;
static int protothread1_flag, protothread2_flag, protothread3_flag, protothread4_flag, protothread5_flag, protothread6_flag, protothread7_flag; //线程1、2、3
static struct pt pt1, pt2, pt3, pt4, pt5, pt6 , pt7;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); // I2C / TWI
//U8GLIB_SSD1306_128X64 u8g(13, 11, 10, 9);   //D0=13  D1=11 RES=5V DC=9 CS=10
/**
  Serial Init , Gizwits Init
  @param none
  @return none
*/
//以下为温度传感器
/*
  double Fahrenheit(double celsius)
  {
  return 1.8 * celsius + 32;
  }    //摄氏温度度转化为华氏温度

  double Kelvin(double celsius)
  {
  return celsius + 273.15;
  }     //摄氏温度转化为开氏温度

  // 露点（点在此温度时，空气饱和并产生露珠）
  // 参考: http://wahiduddin.net/calc/density_algorithms.htm
  double dewPoint(double celsius, double humidity)
  {
  double A0 = 373.15 / (273.15 + celsius);
  double SUM = -7.90298 * (A0 - 1);
  SUM += 5.02808 * log10(A0);
  SUM += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / A0))) - 1) ;
  SUM += 8.1328e-3 * (pow(10, (-3.49149 * (A0 - 1))) - 1) ;
  SUM += log10(1013.246);
  double VP = pow(10, SUM - 3) * humidity;
  double T = log(VP / 0.61078); // temp var
  return (241.88 * T) / (17.558 - T);
  }

  // 快速计算露点，速度是5倍dewPoint()
  // 参考: http://en.wikipedia.org/wiki/Dew_point
  double dewPointFast(double celsius, double humidity)
  {
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity / 100);
  double Td = (b * temp) / (a - temp);
  return Td;
  }
*/
//#include "dht11.h"

//dht11 DHT11;

//#define DHT11PIN 2

//以上为温度传感器程序
void start() {
  u8g.setFont(u8g_font_fur11);          // 设定字体
  u8g.drawStr(35, 10, "Welcome");        //定位、输入
  u8g.setFont(u8g_font_courR08);            //设定字体
  u8g.drawStr(7, 30, "Timingprogram V1.96");
  u8g.setFont(u8g_font_baby);
  u8g.drawStr(5, 50, "Temperature (oC): ");
  u8g.setPrintPos(90, 50);
  u8g.print(th.t);
  u8g.drawStr(5, 60, "Humidity (%):  ");
  u8g.setPrintPos(90, 60);
  u8g.print(th.h);

}
/*
  void work1() {                               //倒计时开始
  u8g.setFont(u8g_font_fur11);
  u8g.drawStr(20, 40, "start the timer");
  u8g.setPrintPos(40, 55);
  u8g.print(varR_set_the_time);
  u8g.drawStr(90, 55, "min");
  }
*/
void work2() {
  u8g.setFont(u8g_font_fur11);
  u8g.drawStr(20, 30, "Set the time");
  u8g.setFont(u8g_font_tpss);
  u8g.setPrintPos(40, 55);
  u8g.print(shengyu_time / 10);
  u8g.drawStr(90, 55, "S");
}

void work3() {
  i = 0 ;
  i = i - s;
  p = i * 256 / 45 * 4;
  s = s + i;
  for (; p > 0; p = p - 40) {
    dianji_one.step(40);
  }
}

void song() {
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2);
  }
}


static int protothread1(struct pt *pt) {
  PT_BEGIN(pt);
  while (1) {
    PT_WAIT_UNTIL(pt, myGizwits.hasBeenSet(EVENT_submit));
    myGizwits.read(EVENT_set_the_time, &varR_set_the_time);
    shengyu_time = varR_set_the_time * 60 * 10;
    /*
      u8g.firstPage();
      do
      {
       work1();                        //运行start函数
      } while (u8g.nextPage());
    */
    delay(2000);
    PT_YIELD(pt);
  }
  PT_END(pt);
}

static int protothread2(struct pt *pt) {
  PT_BEGIN(pt);
  while (1) {
    PT_WAIT_UNTIL(pt, shengyu_time > 0 );
    for (; shengyu_time > 0; shengyu_time = shengyu_time - 2) {
      u8g.firstPage();
      do
      {
        work2();                        //运行work函数
      } while (u8g.nextPage());
      delay(100);
      shengyu_time_two = shengyu_time;
      myGizwits.write(VALUE_time_left, varW_time_left);
      PT_YIELD(pt);
    }
    xuaniufuwei = 1;
    yingyuekaishi = 1;
  }
  PT_END(pt);
}

static int protothread3(struct pt *pt) {  //偏心轮旋转
  PT_BEGIN(pt);
  PT_WAIT_UNTIL(pt, myGizwits.hasBeenSet(EVENT_ignition));
  myGizwits.read(EVENT_ignition, &varR_ignition); //Address for storing data
  i = varR_ignition ;
  i = i - s;
  p = i * 256 / 45 * 4;
  s = s + i;
  if (p > 0) {
    for (; p > 0; p = p - 40) {
      dianji_two.step(40);
      PT_YIELD(pt);
    }
  }
  if (p < 0) {
    p = -p;
    for (; p > 0; p = p - 40) {
      dianji_two.step(-40);
      PT_YIELD(pt);
    }
  }
  PT_END(pt);
}

static int protothread4(struct pt *pt) {         //电机复位
  PT_BEGIN(pt);
  while (1) {
    PT_WAIT_UNTIL(pt, xuaniufuwei == 1 );
    i = 0;
    i = i - s;
    p = i * 256 / 45 * 4;
    s = s + i;
    for (; p < 0; p = p + 40) {
      dianji_one.step(-40);
      PT_YIELD(pt);
    }
    //xuaniufuwei=0;
  }
  PT_END(pt);
}

static int protothread5(struct pt *pt) {
  PT_BEGIN(pt);
  while (1) {
    PT_WAIT_UNTIL(pt, yingyuekaishi == 1);
    for (; cishu < 10; cishu++) {
      for (; jiezou < length; jiezou++) {
        if (notes[i] == ' ') {
          delay(beats[i] * tempo); // rest
        } else {
          playNote(notes[i], beats[i] * tempo);
        }

        // pause between notes
        delay(tempo / 3);
      }
      cishu = 0;
      PT_YIELD(pt);
    }
    //yingyuekaishi =0;
  }
  PT_END(pt);
}

static int protothread6(struct pt *pt) {
  PT_BEGIN(pt);
  PT_WAIT_UNTIL(pt, myGizwits.hasBeenSet(EVENT_dianji_one));
  myGizwits.read(EVENT_dianji_one, &varR_dianji_one); //Address for storing data
  i = varR_dianji_one ;
  i = i - s;
  p = i * 256 / 45 * 4;
  s = s + i;
  if (p > 0) {
    for (; p > 0; p = p - 40) {
      dianji_one.step(40);
      PT_YIELD(pt);
    }
  }
  if (p < 0) {
    p = -p;
    for (; p > 0; p = p - 40) {
      dianji_one.step(-40);
      PT_YIELD(pt);
    }
  }
  PT_END(pt);
}

static int protothread7(struct pt *pt) {         //电机复位
  PT_BEGIN(pt);
  while (1) {
    PT_WAIT_UNTIL(pt, xuaniufuwei == 1 );
    u8g.firstPage();
    do
    {
      start();                        //运行start函数
    } while (u8g.nextPage());
    PT_YIELD(pt);
  }
  PT_END(pt);
}
/**
  Arduino loop
  @param none
  @return none
*/
void setup() {
  // put your setup code here, to run once:

  //Serial.begin(9600);
  //pinMode(24, INPUT);
  //pinMode(8, INPUT);
  //  int chk = DHT11.read(DHT11PIN);
  pinMode(speakerPin, OUTPUT);
  dianji_one.setSpeed(sudu);
  //dianji_two.setSpeed(sudu);
  myGizwits.setBindMode(WIFI_RESET_MODE);
  u8g.firstPage();
  do
  {
    start();                        //运行start函数
  } while (u8g.nextPage());
  //song();
  //delay(5000);
  //myGizwits.setBindMode(WIFI_AIRLINK_MODE);
  //myGizwits.setBindMode(WIFI_SOFTAP_MODE);
  // mySerial.println("GoKit init  OK \n");
  myGizwits.begin();

}


void loop() {
  protothread1(&pt1);
  protothread2(&pt2);
  protothread3(&pt3);
  protothread4(&pt4);
  protothread5(&pt5);
  protothread6(&pt6);

  //Read_T_H();
  th.Read();

  unsigned long varW_yanwu = analogRead(A1);
  myGizwits.write(VALUE_yanwu, varW_yanwu);
  unsigned long varW_time_left = shengyu_time / 10; //Add Sensor Data Collection
  myGizwits.write(VALUE_time_left, varW_time_left);
  unsigned long varW_Temperature = th.t; //Add Sensor Data Collection
  myGizwits.write(VALUE_Temperature, varW_Temperature);
  unsigned long varW_humidity = th.h;//Add Sensor Data Collection
  myGizwits.write(VALUE_humidity, varW_humidity);
  unsigned long varW_huoyan = analogRead(A0);//Add Sensor Data Collection
  myGizwits.write(VALUE_huoyan, varW_huoyan);
  /*
    if (digitalRead(24) == LOW) //Trigger Condition
    {
    delay(10);
    while (digitalRead(24) == LOW);
    myGizwits.setBindMode(WIFI_AIRLINK_MODE);  //0x01:Enter AP Mode;0x02:Enter Airlink Mode
    //  Serial.println("START_RESET");
    }
  */
  //Serial.println((float)DHT11.temperature);
  /* if (analogRead(A0) > 400 || analogRead(A1) > 400) {
     xuaniufuwei = 1;
     yingyuekaishi = 1;
     //zhuangtaipanduan=1;
    }
    else{
      xuaniufuwei = 0;
     yingyuekaishi = 0;
    }
  */
  myGizwits.process();
}
