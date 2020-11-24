#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h> // editado

Adafruit_NeoPixel tira = Adafruit_NeoPixel(60,2,NEO_GRB + NEO_KHZ800) ; // editado


ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

const int led = 16;
const int ledd = 15;
bool stateTira = false;

void handleRoot();              // function prototypes for HTTP handlers
void handleRoott();
void handleLED();
void tiraaama();
void tiraaazu();
void tiraaroj();
void tiraaver();
void tiraaros();
void handleNotFound();

void setup(void){
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  pinMode(led, OUTPUT);
  pinMode(ledd, OUTPUT);

  wifiMulti.addAP("40205361", "leidygarzon");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/1", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/2", HTTP_GET, handleRoott);
  server.on("/3", HTTP_GET, tiraa);
  server.on("/3amarillo", HTTP_GET, tiraaama);
  server.on("/3azul", HTTP_GET, tiraaazu);
  server.on("/3rojo", HTTP_GET, tiraaroj);
  server.on("/3verde", HTTP_GET, tiraaver);
  server.on("/3rosado", HTTP_GET, tiraaros);
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();                    // Listen for HTTP requests from clients
}

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  digitalWrite(led,!digitalRead(led));      // Change the state of the LED
  String estado = (String) digitalRead(led);
  server.sendHeader("Access-Control-Allow-Origin","*");
  server.send(200,  "text/plain",estado);
  Serial.print(estado);
}
void handleRoott() {                         // When URI / is requested, send a web page with a button to toggle the LED
  digitalWrite(ledd,!digitalRead(ledd));      // Change the state of the LED
  String estado = (String) digitalRead(ledd);
  server.sendHeader("Access-Control-Allow-Origin","*");
  server.send(200,  "text/plain",estado);
  Serial.print(estado);
}
void tiraa() {                         // When URI / is requested, send a web page with a button to toggle the LED
  if(stateTira){
    tira.begin();
    tira.show();
    tira.setBrightness(100);
    for(int i = 0; i < 60 ; i++){
      tira.setPixelColor(i,0,0,0);
      tira.show();
    }
    server.sendHeader("Access-Control-Allow-Origin","*");
    server.send(200,  "text/plain","tira led apagada");
    stateTira = false;
    }else{
      tira.begin();
      tira.setBrightness(100);
      for(int i = 0; i < 60 ; i++){
        tira.setPixelColor(i,255,255,255);
        tira.show();
        }
      server.sendHeader("Access-Control-Allow-Origin","*");
      server.send(200,  "text/plain","tira led encendida");
      stateTira = true;
      
     }
}
void tiraaama() {                         // When URI / is requested, send a web page with a button to toggle the LED
  stateTira = true;
  tira.begin();
  for(int i = 0; i < 60 ; i++){
    tira.setPixelColor(i,255,255,0);
    tira.show();
    }
  server.sendHeader("Access-Control-Allow-Origin","*");
  server.send(200,  "text/plain","tira led amarilla");
}
void tiraaazu() {                         // When URI / is requested, send a web page with a button to toggle the LED
  stateTira = true;
  tira.begin();
  for(int i = 0; i < 60 ; i++){
    tira.setPixelColor(i,0,0,255);
    tira.show();
    }
  server.sendHeader("Access-Control-Allow-Origin","*");
  server.send(200,  "text/plain","tira led azul");
}
void tiraaroj() {                         // When URI / is requested, send a web page with a button to toggle the LED
  stateTira = true;
  tira.begin();
  for(int i = 0; i < 60 ; i++){
    tira.setPixelColor(i,255,0,0);
    tira.show();
    }
  server.sendHeader("Access-Control-Allow-Origin","*");
  server.send(200,  "text/plain","tira led rojo");
}
void tiraaver() {                         // When URI / is requested, send a web page with a button to toggle the LED
  stateTira = true;
  tira.begin();
  for(int i = 0; i < 60 ; i++){
    tira.setPixelColor(i,0,128,0);
    tira.show();
    }
  server.sendHeader("Access-Control-Allow-Origin","*");
  server.send(200,  "text/plain","tira led verde");
}
void tiraaros() {                         // When URI / is requested, send a web page with a button to toggle the LED
  stateTira = true;
  tira.begin();
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< tira.numPixels(); i++) {
      tira.setPixelColor(i, Wheel(((i * 256 / tira.numPixels()) + j) & 255));
    }
    tira.show();
    delay(5);
  }
  server.sendHeader("Access-Control-Allow-Origin","*");
  server.send(200,  "text/plain","tira led rosado");
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return tira.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return tira.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return tira.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}