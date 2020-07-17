#define BLYNK_PRINT Serial

#include <WiFi101.h>
#include <ArduinoHttpClient.h>
#include <BlynkSimpleMKR1000.h>

const char ssid[] = "Haakam’s iPhone";//"MannAujla";//
const char pass[] = "123haakam";//"663012345";//

const char server[] = "73.145.227.47";//"192.168.1.15";
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
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);

  digitalWrite(LED_BUILTIN, HIGH);

  while (status != WL_CONNECTED) {
    Serial.print("Connecting to: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);
  }

  Blynk.begin(auth, ssid, pass);

  Serial.print("Connecting to: ");
  Serial.println(server);
  client.begin();

  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V0)
{
  dx = param[0].asFloat() - x;
  dy = param[1].asFloat() - y;
  dz = param[2].asFloat() + 1 - y;

  x = param[0].asFloat();
  y = param[1].asFloat();
  z = param[2].asFloat() + 1;

  if (client.connected()) {
    digitalWrite(LED_BUILTIN, LOW);
    
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
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    
    Serial.print("Connecting to: ");
    Serial.println(server);
    client.begin();
  }
}

BLYNK_WRITE(V2)
{
  pothole = param.asInt();
}
