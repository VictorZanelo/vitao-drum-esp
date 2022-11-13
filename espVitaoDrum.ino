#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "VitaoDrum";
const char* password = "vitaoDrum";

const int piezo_snare = 33;
const int piezo_hihat = 32;
const int piezo_kick = 35;
const int piezo_tom = 34;

int snare_value = 0;
int hihat_value = 0;
int kick_value = 0;
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
  snare_value = analogRead(piezo_snare);
  hihat_value = analogRead(piezo_hihat);
  kick_value = analogRead(piezo_kick);
  tom_value = analogRead(piezo_tom);

  int snare = snare_value;
  int hihat = hihat_value;
  int kick = kick_value;
  int tom = tom_value;
  

  if (snare > 50 || hihat > 50 || kick > 50 || tom > 50 ) {
    Serial.print("caixa" + String(snare) + " ");
    Serial.print("hihat" + String(hihat) + " ");
    Serial.print("kick" + String(kick) + " ");
    Serial.print("tom" + String(tom) + " ");

    ws.textAll("{\"snare\":" + String(snare) + ",\"hihat\":" + String(hihat) + ",\"kick\":" + String(kick) + ",\"tom\":" + String(tom) + "}");
  }
  delay(30);
}