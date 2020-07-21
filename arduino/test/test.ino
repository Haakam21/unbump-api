#define BLYNK_PRINT Serial

#include <SPI.h>
#include <WiFi101.h>
#include <ArduinoHttpClient.h>
#include <BlynkSimpleMKR1000.h>

const int button_pin = 7;

const char ssid[] = "MannAujla";//"Haakam’s iPhone";//
const char pass[] = "663012345";//"123haakam";//

const char server[] = "my-road-conditions.herokuapp.com";//"192.168.1.15";//
const int port = 80;//8080;//

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, port);

const char auth[] = "iH74nfKFF3MnA2GHucEhrYlg0IkeZ15z";

int status = WL_IDLE_STATUS;

float x;
float y;
float z;

float dx;
float dy;
float dz;

float lat;
float lng;

int pothole;

void setup()
{
  pinMode(button_pin, INPUT);
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
  if (pothole || digitalRead(button_pin)) {
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
  }
}

BLYNK_WRITE(V0)
{
  dx = param[0].asFloat() - x;
  dy = param[1].asFloat() - y;
  dz = param[2].asFloat() + 1 - z;

  x = param[0].asFloat();
  y = param[1].asFloat();
  z = param[2].asFloat() + 1;

  Serial.println("acc data updated");
}

BLYNK_WRITE(V1)
{
  lat = param[0].asFloat();
  lng = param[1].asFloat();

  Serial.println("gps data updated");
}

BLYNK_WRITE(V2)
{
  pothole = param.asInt();
}
