## Backyard door key.

With the lack of remote keys, I came up with the idea to make a key based on ESP8266 on which the web server is running. The ESP8266 connects to a home wireless network. The server is accessed locally from any device and allows easy opening and closing of the yard door via an Internet browser. ESP8266 is installed directly in yard door motor box and use motor electronic for power supply. Additional electronics are needed; diode rectifier, 5 volt power stabilizer, transistor, relay and few resistors.

  ### Key features: 
   - Access from any device connected to the local home network. 
   - Control is done over internet browser. 
   - System status and signal straight information. 
   - Web page automatically closed after 20 seconds. 
  ### Further improvements: 
   - Status of door position; closed or open.
  ### Software:
   - Arduino based software use ESP8266WebServer to create server. HTML code use JavaScript and AJAX to update information on web page and do comunication with ESP8266.    
