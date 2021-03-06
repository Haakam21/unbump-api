#define BLYNK_PRINT Serial

#include <SPI.h>
#include <WiFi101.h>
#include <ArduinoHttpClient.h>
#include <BlynkSimpleMKR1000.h>

const char ssid[] = "Haakam’s iPhone";
const char pass[] = "123haakam";

const char server[] = "my-road-conditions.herokuapp.com";
const int port = 80;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, port);

const char auth[] = "tCFbjZNOJziULJ566V0SG3mRXh74n7WW";

int status = WL_IDLE_STATUS;

float acc_x;
float acc_y;
float acc_z;

float acc_dx;
float acc_dy;
float acc_dz;

float lng;
float lat;
float spd;

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

  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  Blynk.run();
  
  if (acc_z >= 0.19 || acc_dz >= 0.92) {
    recordPothole();
  }
}

BLYNK_WRITE(V0)
{
  acc_dx = param[0].asFloat() - acc_x;
  acc_dy = param[1].asFloat() - acc_y;
  acc_dz = param[2].asFloat() + 1 - acc_z;

  acc_x = param[0].asFloat();
  acc_y = param[1].asFloat();
  acc_z = param[2].asFloat() + 1;
}

BLYNK_WRITE(V1)
{
  lat = param[0].asFloat();
  lng = param[1].asFloat();
  spd = param[3].asFloat();
}

void recordPothole()
{
  digitalWrite(LED_BUILTIN, HIGH);

  String route = "/api/potholes";
  String contentType = "application/json";
  String postData = "{\"latitude\":" + String(lat, 6) + ",\"longitude\":" + String(lng, 6) + "}";

  Serial.print("Data: ");
  Serial.println(postData);

  client.post(route, contentType, postData);

  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  digitalWrite(LED_BUILTIN, LOW);
}
