#define BLYNK_PRINT Serial

#include <WiFi101.h>
#include <ArduinoHttpClient.h>
#include <BlynkSimpleMKR1000.h>

const char ssid[] = "MannAujla";//"Haakam’s iPhone";
const char pass[] = "663012345";//"123haakam";

const char server[] = "192.168.1.15";
const int port = 8081;

WiFiClient wifi;
WebSocketClient client = WebSocketClient(wifi, server, port);

const char auth[] = "iH74nfKFF3MnA2GHucEhrYlg0IkeZ15z";

int status = WL_IDLE_STATUS;

float x;
float y;
float z;

float dx;
float dy;
float dz;

int pothole;

void setup()
{
  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.print("Connecting to: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);
  }

  Blynk.begin(auth, ssid, pass);

  Serial.print("Connecting to: ");
  Serial.println(server);
  client.begin();
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V0)
{
  dx = param[0].asFloat() - x;
  dy = param[1].asFloat() - y;
  dz = param[2].asFloat() - y;

  x = param[0].asFloat();
  y = param[1].asFloat();
  z = param[2].asFloat();

  if (client.connected()) {
    String data = "{\"acc_x\":" + String(x, 6) + ",\"acc_y\":" + String(y, 6) + ",\"acc_z\":" + String(z, 6) + ",\"acc_dx\":" + String(dx, 6) + ",\"acc_dy\":" + String(dy, 6) + ",\"acc_dz\":" + String(dz, 6) + ",\"pothole\":" + String(pothole) + "}";

    Serial.print("Logging: ");
    Serial.println(data);

    client.beginMessage(TYPE_TEXT);
    client.print(data);
    client.endMessage();

    int messageSize = client.parseMessage();
    if (messageSize > 0) {
      String message = client.readString();
      Serial.print("Received:");
      Serial.println(message);
    }
  }
}

BLYNK_WRITE(V2)
{
  pothole = param.asInt();
}
