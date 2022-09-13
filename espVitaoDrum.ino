#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "VitaoDrum";
const char* password = "vitaoDrum";

const int piezo_caixa = 33;
const int piezo_chimbal = 32;
const int piezo_bumbo = 35;
const int piezo_tom = 34;
int caixa_value = 0;
int chimbal_value = 0;
int bumbo_value = 0;
int tom_value = 0;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len) {

  if (type == WS_EVT_CONNECT) {

    Serial.println("Websocket client connection received");

  } else if (type == WS_EVT_DISCONNECT) {

    Serial.println("Client disconnected");
  }
}

void setup() {
  Serial.begin(115200);

  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  server.begin();
}

void loop() {
  caixa_value = analogRead(piezo_caixa);
  chimbal_value = analogRead(piezo_chimbal);
  bumbo_value = analogRead(piezo_bumbo);
  tom_value = analogRead(piezo_tom);
  int caixa = map(caixa_value, 0, 4095, 0, 99);
  int chimbal = map(chimbal_value, 0, 4095, 0, 99);
  int bumbo = map(bumbo_value, 0, 4095, 0, 99);
  int tom = map(tom_value, 0, 4095, 0, 99);
  
    Serial.println(tom_value);
  if ( tom > 0) {
    ws.textAll("{\"caixa\":" + String(caixa) + ",\"chimbal\":" + String(chimbal) +",\"bumbo\":" + String(bumbo) + ",\"tom\":" + String(tom) +"}");
    
    
}


  delay(150);
}