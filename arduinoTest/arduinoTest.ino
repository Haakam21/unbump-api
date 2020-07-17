#include <WiFi101.h>
#include <ArduinoHttpClient.h>

const char ssid[] = "Haakam’s iPhone";//"MannAujla";
const char pass[] = "123haakam";//"663012345";

const char server[] = "my-road-conditions.herokuapp.com";
const int port = 80;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, port);

int status = WL_IDLE_STATUS;

void setup()
{
  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.print("Connecting to: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);
  }
}

void loop()
{
  String route = "/api/potholes";
  String contentType = "application/json";
  String postData = "{\"latitude\": 0, \"longitude\": 0}";

  Serial.print("POST data: ");
  Serial.println(postData);

  client.post(route, contentType, postData);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
  
  delay(100000);
}
