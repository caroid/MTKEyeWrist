#include <LWiFi.h>
#include <LWiFiClient.h>
#include <Adafruit_ssd1306syp.h>

#define SDA_PIN 8
#define SCL_PIN 9
#define SITE_URL "10.0.1.22"
#define WIFI_AP "Mike's iPhone" // replace with your setting
#define WIFI_PWD "androidiphone" // replace with your setting
LWiFiClient c;
Adafruit_ssd1306syp display(SDA_PIN,SCL_PIN);
char buf[30];

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
void G_email()
{
  display.setTextSize(3);
  display.setCursor(20,20);
  display.println("Email");
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
}



void setup() {
  
  display.initialize();

  display.clear();
  drawEyeWrist();
  display.setTextSize(3);
  display.setCursor(20,20);
  display.println("Hello");
  display.drawLine(0,50,128,50,WHITE);
  display.update();

  Serial.begin(9600);
  while(!Serial)
  {
    delay(100);
  }

  LWiFi.begin();

  Serial.println();
  Serial.println("Connecting to AP...");
  if (LWiFi.connectWPA(WIFI_AP, WIFI_PWD) < 0) 
  {
    Serial.println("FAIL!");
    return;
  }

  Serial.print("Connecting to server...");
  if(!c.connect(SITE_URL, 8080))
  {
    Serial.println("FAIL!");
    return;
  }
  
  Serial.println("ok");
}

void loop() {
  if(c.connected()){
    //c.print("connection");
    //Serial.println("Send:connection");
    
    c.print("test");
    Serial.println("Send:test");
    delay(400);
    //Always Read
    unsigned char mesg[40];
    String tmp ="";
    int found=0;
    int readsize = c.read(mesg,sizeof(mesg));

    for(int i=0; i<readsize; i++){
        tmp = tmp + (char)mesg[i];
    }
    if(tmp){
      Serial.println(tmp); 
      found = tmp.indexOf(',');
      Serial.println(found);
    }
    
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
  }
}
