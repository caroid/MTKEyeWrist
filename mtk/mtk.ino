#include <LWiFi.h>
#include <LWiFiClient.h>

#define SITE_URL "10.0.1.70"
#define WIFI_AP "Mike's iPhone" // replace with your setting
#define WIFI_PWD "androidiphone" // replace with your setting
LWiFiClient c;
char buf[30];

void setup() {

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
    c.print("connection");
    Serial.println("Send:connection");
    delay(1000);
    c.print("test");
    Serial.println("Send:test");
    delay(2000);

    //Always Read
    unsigned char mesg[40];
    String tmp ="";
    
    int readsize = c.read(mesg,sizeof(mesg));

    for(int i=0; i<readsize; i++){
        Serial.print((char)mesg[i]);
        tmp = tmp + (char)mesg[i];
    }
    Serial.println(haha);

    if(tmp.substring(0,readsize) == "done"){
      Serial.println("Done recognized");     
    }      
  }
  
}


