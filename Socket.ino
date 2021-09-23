// webSocket

void initWebSocket() {
  // start webSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type) {
    case WStype_DISCONNECTED:
      //sendOptions(webSocketS,getOptionsInt(webSocketS)-1);
      break;
    case WStype_CONNECTED: {
        IPAddress ip = webSocket.remoteIP(num);
        //sendOptions(webSocketS,getOptionsInt(webSocketS)+1);
        //sendOptions(webSocketS, num);
        //USE_SERIAL.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // send message to client
        //String broadcast =invitationPrint();
        //webSocket.sendTXT(num, broadcast);
      }
      break;
    case WStype_TEXT:
     
      break;
  }
}
