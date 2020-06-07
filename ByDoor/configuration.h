//Configuration file.

//Define PIN of ESP8266 board on which relay is connected.
//Check WEB for pin configuration.
//Relay cannot be directly connected, check electrical schematic for further details.

#define RELAY_PIN 0 

//#define __debug__

//If your devices suports mDNS uncoment __mdns__.

//#define __mdns__
#ifdef __mdns__
#define MDNS_WEB_ADRESS "espdoor"
#endif

//Define static IP address for your local network. 
// Check on your WiFi ruter DHCP range.
// Put static IP outside DHCP range. 

#ifndef __mdns__
#define IPADDRESS xxx,xxx,x,x
#define GATEWAY xxx,xxx,x,x
#define MASK 255,255,255,0
#endif

//Define SSID and PASSWORD for your local wifi network. 
#define __SSID__ "enter yours SSID"
#define __PASSWORD__ "enter yours password"
