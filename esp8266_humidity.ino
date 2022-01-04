#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#include "index.h"


#define DHTPIN  D3  // output pin for DHT22 sensor
#define DHTTYPE DHT22 // sensor is a DHT22 model


ESP8266WebServer server(80);    // initialize server with port 80 open
DHT dht(DHTPIN, DHTTYPE); // initialize a dht sensor object

const char *ssid = "ESP-AP";
const char *pass = "testpass0?";


// HTML handlers
void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s); // send web page
}

void handleHumidityLevel() {
  delay(2000);
  float humidity = dht.readHumidity();
  String humidityValue = String(humidity);

  server.send(200, "text/plain", humidityValue);
  Serial.println(humidity);
  Serial.println(humidityValue); 
}


// Setup initial WiFi connection only one time
void setup() {
  delay(1000);
  Serial.begin(115200);

  WiFi.softAP(ssid, pass);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.on("/readHumidity", handleHumidityLevel);
  server.begin();                         // start the server

  dht.begin();
}


// In endless loop, read humidity, update HTML, and serve to client
void loop() {
  server.handleClient();

  //delay(2000);                    // DHT22 needs ~2000 ms between reads
  //float h = dht.readHumidity();  // read humidty from sensor
  //String hString = String(h);

  //Serial.println(h);
  
  //server.send(200, "text/html", hString); // send the humidity data
  //server.handleClient();

}
