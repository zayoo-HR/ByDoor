#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>

#include "configuration.h"
#include "index.h"

#ifdef __mdns__
  #include <ESP8266mDNS.h>
#endif

//Define relay ON state in ie. 0.5s. Short timing will not trigere door electronic. 
#define ACTIVE_TIME 0.5

//Replace with your network credentials
const char* ssid = __SSID__;
const char* password = __PASSWORD__;
boolean relay = false; //Ovdje se cuva stanje releja

// NETWORK: Static IP details...

#ifndef __mdns__
  IPAddress ip(IPADDRESS); //Enter static IP adress
  IPAddress gateway(GATEWAY); //Enter Gateway 
  IPAddress subnet(MASK); //Enter subnet mask
#endif
// Vremenski rele koji će isključivati rele nakon nekog perioda.
Ticker timeRelay;

ESP8266WebServer server (80);

//This function is started when device establish connection with server.
//Function sends index html code to device .

void handleRoot(){
  server.send(200,"text/html", MAIN_page );
  //Network scan is started to determin signal strenght.
  WiFi.scanNetworks(true, false);
}

void relayOFF(){
  digitalWrite(RELAY_PIN, LOW);
  relay = false;
  timeRelay.detach();
  #ifdef __debug__
  Serial.println("Relay set to OFF state, timer disabled.");
  #endif
}

void handleActivation(){
  #ifdef __debug__
  Serial.println("Relay triggered...");
  #endif
  //Check that the timer is not already active.
  //Relay activation on pin 0, ie D3
  if(relay == false){
    server.send(200,"text/html", "Change of door state");
    digitalWrite(RELAY_PIN, HIGH);
    relay = true;
    //Timer start, will count ACTIV_TIME and then start function relayOFF. 
    timeRelay.attach(ACTIVE_TIME, relayOFF);
    #ifdef __debug__
      Serial.println("Relay is ON, timer for deactivation started");
    #endif
  }else{
    server.send(200,"text/html", "Hey, take it easy.");
    #ifdef __debug__
      Serial.println("debug: Activation of an already active relay is prevented.");
    #endif
  }
    
  }

void handleStatus(){
  int n = WiFi.scanComplete(); 
  String RSSI = "xx";
  #ifdef __debug__
    Serial.println("debug: 1s timer ");
  #endif

  if(n>0){
    for (int i=0; i < n ; i++){
      if(WiFi.SSID(i) == __SSID__){
        RSSI = String(WiFi.RSSI(i));
        break;
      }
    }
  }
  
  if (relay == false){
    server.send(200,"text/html",String("System ready. "+RSSI+" dBm."));
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // ESP8266 output pin on which reley is connected. Pin 0 (D3)
  pinMode(RELAY_PIN, OUTPUT);
  // Init Relay. Set to OFF.
  digitalWrite(RELAY_PIN, LOW);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // Static IP Setup Info Here...
  WiFi.mode(WIFI_STA);
  #ifndef __mdns__
    WiFi.config(ip, gateway, subnet); 
  #endif 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  #ifdef __mdns__
    if(MDNS.begin(MDNS_WEB_ADRESS)){
      #ifdef __debug__
        Serial.println("MDNS responder started.");
      #endif
    }
  #endif

  //Which function is triggered by client requests.  
  server.on("/", handleRoot); 
  server.on("/activation", handleActivation);
  server.on("/status", handleStatus);
  server.begin(); //Start server.
  Serial.println("HTTP Server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  #ifdef __mdns__
    MDNS.update();
  #endif
}
