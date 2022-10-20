//libraries
#include <WiFi.h>
#include <WiFiUdp.h>

//initialize variables
const char* ssid = "yale wireless";
const char* password = "";

const char* udp_addy = "172.29.21.213";
const int udpport = 8092;

WiFiUDP udp;
int photo = 33;

void setup() {
  Serial.begin(115200);
  //setup connection and confirm
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){      
    Serial.print(".");
    delay(100);
  }
  Serial.println("");
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //read from light sensor
  int buffer = analogRead(photo);
  String val = String(buffer);
  //This initializes udp and transfer buffer
  udp.beginPacket(udp_addy, udpport);
  udp.print(val);
  udp.endPacket();
}
