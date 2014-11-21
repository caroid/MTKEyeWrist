#include <LWiFi.h>
#include <LWiFiClient.h>
#include <Adafruit_ssd1306syp.h>

#define SDA_PIN 8
#define SCL_PIN 9
#define Shock 10
#define SITE_URL "192.168.1.109"
//#define WIFI_AP "Mike's iPhone" // replace with your setting
//#define WIFI_PWD "androidiphone" // replace with your setting
//#define WIFI_AP "HomeNet" // replace with your setting
//#define WIFI_PWD "ntpu49985052" // replace with your setting
#define WIFI_AP "Hsiu_iPhone" // replace with your setting
#define WIFI_PWD "newiphone5" // replace with your setting
unsigned long time;
LWiFiClient c;
Adafruit_ssd1306syp display(SDA_PIN,SCL_PIN);
char buf[30];
//int Virbration; // define numeric variables val
int flag_Time=0;
int flag_Clear=0;

uint32_t analogPin = A0;
int val = 0;

unsigned char mesg[40];
int readsize;

void DisplayActivation()
{
  display.clear();
  drawEyeWrist();
  display.setTextSize(3);
  display.setCursor(20,20);
  display.println("Hello");
  display.drawLine(0,50,128,50,WHITE);
  display.update();
}

void drawEyeWrist()
{
  //EyeWrist
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println("EyeWrist");
}

void drawPhone()
{
  //Device
  display.setTextSize(1);
  display.setCursor(50,54);
  display.println("Phone");
  display.fillRect(40,55,5,5,WHITE);
  display.update();
}
void drawGlass()
{
  //Device
  display.setTextSize(1);
  display.setCursor(50,54);
  display.println("Glass");
  display.fillRect(40,55,5,5,WHITE);
  display.update();
}
void drawTV()
{
  //Device
  display.setTextSize(1);
  display.setCursor(60,54);
  display.println("TV");
  display.fillRect(50,55,5,5,WHITE);
  display.update();
}
void G_up()
{
  display.setTextSize(3);
  display.setCursor(50,20);
  display.println("Up");
}
void G_down()
{
  display.setTextSize(3);
  display.setCursor(30,20);
  display.println("Down");
}
void G_left()
{
  display.setTextSize(3);
  display.setCursor(30,20);
  display.println("Left");
}
void G_right()
{
  display.setTextSize(3);
  display.setCursor(20,20);
  display.println("Right");
}
void G_click()
{
  display.setTextSize(3);
  display.setCursor(20,20);
  display.println("Click");
}
void G_back()
{
  display.setTextSize(3);
  display.setCursor(30,20);
  display.println("Back");
}
void G_email()
{
  display.setTextSize(3);
  display.setCursor(30,20);
  display.println("Play");
}
void G_music()
{
  display.setTextSize(3);
  display.setCursor(20,20);
  display.println("Music");
}
void G_map()
{
  display.setTextSize(3);
  display.setCursor(40,20);
  display.println("Map");
}
void GestureShow(String tmp)
{
  if(tmp == "swipe_right"){
      G_right();
  }
  else if(tmp == "swipe_left"){
      G_left();
  }
  else if(tmp == "swipe_up"){
      G_up();
  }
  else if(tmp == "swipe_down"){
      G_down();
  }
  else if(tmp == "email"){
      G_email();
  }
  else if(tmp == "map"){
      G_map();
  }
  else if(tmp == "music"){
      G_music();
  }
  else if(tmp == "click"){
      G_click();
  }
  else if(tmp == "back"){
      G_back();
  }
}
void setup() {

  //display
  display.initialize();
  display.clear();
  display.update();

  Serial.begin(9600);
  // while(!Serial)
  // {
  //   delay(100);
  // }

  LWiFi.begin();

  Serial.println();
  Serial.println("Connecting to AP...");
  if (LWiFi.connectWPA(WIFI_AP, WIFI_PWD) < 0) 
  {
    Serial.println("FAIL!");
    return;
  }

  Serial.print("Connecting to server...");
  if(!c.connect(SITE_URL, 8080))//port number may need to change
  {
    Serial.println("FAIL!");
    return;
  }
  
  Serial.println("ok");
}

void loop() {
  val=analogRead(analogPin);
  
  Serial.println(val);
  if (val < 10 && (millis()-time) >10000)
  {
    if(flag_Clear==0){
      display.clear();
      display.update();
      flag_Time=0;
      flag_Clear=1;
    }
  }
  else
  {
    Serial.println("Active");
    if(c.connected() && flag_Time){
      //c.print("test");
      //Serial.println("    Send:test");
      delay(600);
      //Always Read
      String tmp ="";
      int found=0;
      readsize = c.read(mesg,sizeof(mesg));
      
      if(readsize!=0){
        for(int i=0; i<readsize; i++){
            tmp = tmp + (char)mesg[i];
        }
        if(tmp!=""){
          //need to uncomment in real!!
          time = millis();
          Serial.print("    "); 
          Serial.println(tmp); 
          found = tmp.indexOf(',');

          if(tmp.substring(0,found) == "youtube"){
            display.clear();
            drawEyeWrist();
            GestureShow(tmp.substring(found+1,tmp.length()));
            display.drawLine(0,50,128,50,WHITE);
            drawTV();
          }
          else if(tmp.substring(0,found) == "mobile"){
            display.clear();
            drawEyeWrist();
            GestureShow(tmp.substring(found+1,tmp.length()));
            display.drawLine(0,50,128,50,WHITE);
            drawPhone();
          }
          else if(tmp.substring(0,found) == "glass"){
            display.clear();
            drawEyeWrist();
            GestureShow(tmp.substring(found+1,tmp.length()));
            display.drawLine(0,50,128,50,WHITE);
            drawGlass();
          }
          delay(1500);   
        }
        else
        {
          DisplayActivation();
          delay(1000);
        }
      }
    }
    else
    {
      DisplayActivation();
      delay(1000);
    }

    if(flag_Time==0){
      time = millis();
      flag_Time=1;    
      flag_Clear=0;
    }
  }
}
