
/* ESP8266 Humidty Sensor by MLR
 *  This system updates humidtiy using a DHT22 sensor.
 *  Humidity is sent to an ESP8266 webserver
 *  and displayed on an HTML webpage.
 *  Updates occur every 2000 ms, in accordance
 *  with DHT22 specifications.
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#include "index.h"


#define DHTPIN  D3                                      // output pin for DHT22 sensor
#define DHTTYPE DHT22                                   // sensor is a DHT22 model


DHT dht(DHTPIN, DHTTYPE);                               // initialize a dht sensor object
float humidity = 0.0;

ESP8266WebServer server(80);                            // initialize server with port 80 open
const char *ssid = "";
const char *pass = "";


/* HTML handlers */
void handleRoot() {
  String s = MAIN_page;                                 // Main HTML webpage
  server.send(200, "text/html", s);                     // send HTML webpage
}

/* handle reading humidty from DHT22 
 * and sending data as plain text to server 
 */
void handleReadHumidity() {
  humidity = dht.readHumidity();              
  server.send(200, "text/plain", String(humidity));
  Serial.println(humidity);                             // send humidity data to serial output for debugging
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
  server.on("/humidity", HTTP_GET, handleReadHumidity); // send humidity data to sever on request from client
  server.begin();                                       // start the web server
}


/* Endless loop to handle client requests */
void loop() {
  server.handleClient();                                // handle request from client web browser
}
