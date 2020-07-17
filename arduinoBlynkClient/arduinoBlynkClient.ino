#define BLYNK_PRINT Serial

#include <WiFi101.h>
#include <ArduinoHttpClient.h>
#include <BlynkSimpleMKR1000.h>

const char ssid[] = "Haakam’s iPhone";//"MannAujla";//
const char pass[] = "123haakam";//"663012345";//

const char server[] = "my-road-conditions.herokuapp.com";
const int port = 80;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, port);

const char auth[] = "iH74nfKFF3MnA2GHucEhrYlg0IkeZ15z";

const int history_window = 10;

int status = WL_IDLE_STATUS;

/*float acc_x[history_window];
float acc_y[history_window];
float acc_z[history_window];

float delta_acc_x[history_window];
float delta_acc_y[history_window];
float delta_acc_z[history_window];*/

float x;
float y;
float z;

float dx;
float dy;
float dz;

float lng;
float lat;

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
}

BLYNK_WRITE(V0)
{
  dx = param[0].asFloat() - x;
  dy = param[1].asFloat() - y;
  dz = param[2].asFloat() - y;

  x = param[0].asFloat();
  y = param[1].asFloat();
  z = param[2].asFloat();

  /*for (int i = history_window; i > 0; i = i - 1) {
    delta_acc_x[i] = delta_acc_x[i - 1];
  }
  delta_acc_x[0] = x - acc_x[0];
  for (int i = history_window; i > 0; i = i - 1) {
    delta_acc_y[i] = delta_acc_y[i - 1];
  }
  delta_acc_y[0] = y - acc_y[0];
  for (int i = history_window; i > 0; i = i - 1) {
    delta_acc_z[i] = delta_acc_z[i - 1];
  }
  delta_acc_z[0] = z - acc_z[0];

  for (int i = history_window; i > 0; i = i - 1) {
    acc_x[i] = acc_x[i - 1];
  }
  acc_x[0] = x;
  for (int i = history_window; i > 0; i = i - 1) {
    acc_y[i] = acc_y[i - 1];
  }
  acc_y[0] = y;
  for (int i = history_window; i > 0; i = i - 1) {
    acc_z[i] = acc_z[i - 1];
  }
  acc_z[0] = z;*/

  /*Serial.print("x: ");
  Serial.print(x, 6);
  Serial.print(" y: ");
  Serial.print(y, 6);
  Serial.print(" z: ");
  Serial.println(z, 6);*/

  /*Serial.print("acc hisotry: ");
  for (int i = 0; i < history_window; i = i + 1) {
    Serial.print(acc[i]);
    Serial.print(", ");
  }
  Serial.print(acc[history_window]);
  Serial.print(" acc delta hisotry: ");
  for (int i = 0; i < history_window; i = i + 1) {
    Serial.print(delta_acc[i]);
    Serial.print(", ");
  }
  Serial.println(delta_acc[history_window]);*/
}

BLYNK_WRITE(V1)
{
  lat = param[0].asFloat();
  lng = param[1].asFloat();
}

BLYNK_WRITE(V2)
{
  int pothole = param.asInt();
  if (pothole) {
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