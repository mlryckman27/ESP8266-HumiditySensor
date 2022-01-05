
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#include "index.h"


#define DHTPIN  D3  // output pin for DHT22 sensor
#define DHTTYPE DHT22 // sensor is a DHT22 model

DHT dht(DHTPIN, DHTTYPE); // initialize a dht sensor object

ESP8266WebServer server(80);    // initialize server with port 80 open
const char *ssid = "ESP-AP";
const char *pass = "testpass0?";

float humidity = 0.0;


// HTML handlers
void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s); // send web page
}

void handleReadHumidity() {
  humidity = dht.readHumidity();
  server.send(200, "text/plain", String(humidity));
  Serial.println(humidity); 
}


// Setup initial WiFi connection only one time
void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.softAP(ssid, pass);
  Serial.println(WiFi.localIP());
  
  server.on("/", HTTP_GET, handleRoot);
  server.on("/humidity", HTTP_GET, handleReadHumidity);
  server.begin();                         // start the server
}


// In endless loop, read humidity, update HTML, and serve to client
void loop() {
  server.handleClient();
}
