//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
//#include <ArduinoJson.h>
#include <ESP8266WiFi.h> 
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
 
//#include "config.h"  // Sustituir con datos de vuestra red
//#include "API.hpp"
//#include "ESP8266_Utils.hpp"

const char* ssid = "armandt";
const char* password = "NgfyoiGl19";
const char* host = "192.168.1.68";

 
void setup () {
  Serial.begin(115200);
  delay(10);
 
  // Conectamos a la red WiFi
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  /* Configuramos el ESP8266 como cliente WiFi. Si no lo hacemos 
     se configurará como cliente y punto de acceso al mismo tiempo */
  WiFi.mode(WIFI_STA); // Modo cliente WiFi
  WiFi.begin(ssid, password);
 
  // Esperamos a que estemos conectados a la red WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  
  Serial.print("connecting to ");
  Serial.println(host);
 
  WiFiClient client;
  const int httpPort = 3300; // Puerto HTTP
  if (!client.connect(host, httpPort)) {
    // ¿hay algún error al conectar?
    Serial.println("Ha fallado la conexión");
    return;
  }else{
    HTTPClient http;                                                                                  
    http.begin("http://192.168.1.68:3300/interruptores/5f90f2b85b8af0200afcc642");

    int httpCode = http.GET();         //Send the request
    String payload = http.getString(); //Get the request response payload
    if (httpCode > 0)
    {
      String payload2 = payload;
      char json[500];
      payload2.toCharArray(json, 500);

      Serial.println("Respuesta de la peticion");
      Serial.println(payload2);
      StaticJsonDocument<256> doc;

      deserializeJson(doc, json);

    String interruptor = doc["interruptor"];
    int est = doc["data"]["interruptor"]["estado"];
    int val=digitalRead(5);
     Serial.println("Respuesta de la peticion"+est);
    if(est!=val){
      post("5f90f2b85b8af0200afcc642",val);
      delay(1000);
     }
     delay(1000);
    
    
    }
  }
  
 
}

void post(String id, int est) {
  HTTPClient http;
  String json;
  String server = "http://192.168.1.68:3300/interruptores/"+id;

  StaticJsonDocument<256> doc;
  doc["estado"] = String(est);
  serializeJson(doc, json);
  
  http.begin(server);
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
}
