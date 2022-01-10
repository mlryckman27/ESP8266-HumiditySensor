
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#include "index.h"


#define DHTPIN  D3  // output pin for DHT22 sensor
#define DHTTYPE DHT22 // sensor is a DHT22 model

DHT dht(DHTPIN, DHTTYPE); // initialize a dht sensor object

ESP8266WebServer server(80);    // initialize server with port 80 open
const char *ssid = "HOME3-2G";
const char *pass = "Winter11*";

float humidity = 0.0;


/* HTML handlers */
void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s); // send web page
}

/* handle reading humidty from DHT22 and sending data as plain text to server */
void handleReadHumidity() {
  humidity = dht.readHumidity();
  server.send(200, "text/plain", String(humidity));
  Serial.println(humidity); // send humidity date to serial output for debugging
}


/* Setup initial WiFi connection only one time and begin DHT22 sensor */
void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  
  server.on("/", HTTP_GET, handleRoot);
  server.on("/humidity", HTTP_GET, handleReadHumidity);
  server.begin();                         // start the server
}


/* In endless loop, read humidity, update HTML, and serve to client */
void loop() {
  server.handleClient();
}
