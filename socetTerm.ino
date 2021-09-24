#include <wificonnect.h>  //https://github.com/tretyakovsa/wificonnect
WIFICONNECT MyWiFi;
#include <ESP8266HTTPUpdateServer.h> //Содержится в пакете
ESP8266HTTPUpdateServer httpUpdater; 
#include <ESP8266httpUpdate.h>       //Содержится в пакете

const String ssid       = "";
const String ssidPass   = "";
const String ssidAP     = "WebSockets";
const String ssidApPass = "";
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>    //https://github.com/Links2004/arduinoWebSockets
WebSocketsServer webSocket = WebSocketsServer(82);
ESP8266WebServer HTTP(80);
const String webForth =
  "<!DOCTYPE html>\n\r"
  "<html>\n\r"
  " <head>\n\r"
  " <meta charset=\"UTF-8\">\n\r"
  " <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\" />\n\r"
  " <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n\r"
  "  <title>WebSocket</title>\n\r"
  "  <style>html,body,div,p,textarea{margin:0;padding:0;border:0;}textarea,body,html{width:100%;height:99%;}textarea{border-style:none;border-color:Transparent;overflow:auto;}</style>\n\r"
  " </head>\n\r"
  " <body>\n\r"
  "  <script>\n\r"
  "   var connection = new WebSocket('ws://'+window.location.host+':82', ['arduino']);\n\r"
  "   connection.onopen = function () {\n\r"
  "    document.getElementById('console').value += 'Connected...'+'\\n';\n\r"
  "   }\n\r"
  "   connection.onmessage = function (e) {\n\r"
  "    document.getElementById('console').value += e.data+'\\n';\n\r"
  "    document.getElementById('console').scrollTop = document.getElementById('console').scrollHeight;\n\r"
  "   }\n\r"
  "   function onChange() {\n\r"
  "    if (window.event.keyCode === 13) {\n\r"
  "     var console = document.getElementById('console').value;\n\r"
  "     connection.send(console.split('ok>')[console.split('ok>').length-1]);\n\r"
  "     return true;\n\r"
  "    }\n\r"
  "   }\n\r"
  "  </script>\n\r"
  "  <textarea id=\"console\" onkeypress=\"onChange();\" cols=\"30\" rows=\"30\"></textarea>\n\r"
  " </body>\n\r"
  "</html>\n\r";


void setup()
{

  Serial.begin(9600);
  Serial.println();
  MyWiFi.init(ssid, ssidPass, ssidAP, ssidApPass); // Основные данные для wifi
  MyWiFi.start();        // Запустим WiFi
  if (MyWiFi.modeSTA()) { // Если подключились
    Serial.println("Connect "+ssid+" "+ MyWiFi.StringIP());
  } else  Serial.println("AP ="+ssidAP+" "+ MyWiFi.StringIP());
   HTTP.on("/", HTTP_GET, []() {
     HTTP.send(200, "text/html", webForth);
  });
 
 HTTP.begin();
  initWebSocket();
  httpUpdater.setup(&HTTP);

Serial.flush();
  //Serial.swap(); // переключит выходы serial на ноги GPIO15-TXD GPOI13-RXD
Serial.flush();


   
}

void loop() {
  MyWiFi.loop(); // DNS в режиме AP
  HTTP.handleClient();
  if (Serial.available()) {
   sendWS( String((char)Serial.read()) );
  }
  webSocket.loop();
}

void sendWS(String broadcast) {
  webSocket.broadcastTXT(broadcast);
}
