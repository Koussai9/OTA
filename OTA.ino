#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "S8 Plus";
const char* password = "1234567889";
unsigned long start;
unsigned long end;
unsigned long latence;

void setup() {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  Serial.begin(115200);
  Serial.println("Démarrage...");

  // Connexion au réseau Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("La connexion au Wi-Fi a échoué. Redémarrage...");
    delay(5000);
    ESP.restart();
  }

  // Configuration du service ArduinoOTA
  ArduinoOTA.setHostname("ESP8266-OTA");
  ArduinoOTA.setPassword((const char *)"123456");

  ArduinoOTA.onStart([]() {
    Serial.println("Mise à jour en cours...");
    start = millis();
  });
  ArduinoOTA.onEnd([]() {
    
    Serial.println("\nMise à jour terminée. Redémarrage...");
    end = millis();
    latence = end - start;
    Serial.print("Latence : "+String(latence));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Erreur (%u): ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Erreur d'authentification");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Erreur de début");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Erreur de connexion");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Erreur de réception");
    else if (error == OTA_END_ERROR) Serial.println("Erreur de fin");
  });
  ArduinoOTA.begin();

  Serial.println("Prêt pour la programmation OTA");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Gestion des mises à jour OTA
  ArduinoOTA.handle();
   digitalWrite(D1, HIGH); 
  digitalWrite(D2, LOW); 
  delay(1000);                     
  digitalWrite(D1, LOW);   
  digitalWrite(D2, HIGH);  
  delay(1000);                      
 
}