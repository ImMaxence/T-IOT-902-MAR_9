#include "httpsTransmitter/httpsTransmitter.h"
#include <ArduinoJson.h>

HttpsTransmitter::HttpsTransmitter()
{
}

HttpsTransmitter::~HttpsTransmitter()
{
}

bool HttpsTransmitter::begin()
{
  return connectToWiFi();
}

String HttpsTransmitter::buildMessage(String message)
{
  DynamicJsonDocument doc(1024);
  JsonArray array = doc.to<JsonArray>();

  String objectsStr[100]; // Tableau pour stocker les objets
  int numObjects = 0;

  // Séparer les objets
  int start = 0;
  while (true)
  {
    int end = message.indexOf('_', start);
    if (end == -1)
    {
      objectsStr[numObjects++] = message.substring(start);
      break;
    }
    objectsStr[numObjects++] = message.substring(start, end);
    start = end + 1;
  }

  // Créer les objets JSON
  for (int i = 0; i < numObjects; i++)
  {
    JsonObject obj = array.createNestedObject();
    String valuesStr = objectsStr[i];
    unsigned long now = millis();
    int start = 0;
    int j = 0;
    String keys[] = {"name", "unit", "value"};
    while (true)
    {
      int end = valuesStr.indexOf('|', start);
      if (end == -1)
      {
        obj[keys[j]] = valuesStr.substring(start).toFloat();
        break;
      }
      if (j == 0 || j == 1)
      {
        obj[keys[j]] = valuesStr.substring(start, end);
      }
      else
      {
        obj[keys[j]] = valuesStr.substring(start, end).toFloat();
      }
      start = end + 1;
      j++;
    }
    obj["timestamp"] = now;
  }

  String jsonStr;
  serializeJson(doc, jsonStr);
  return jsonStr;
}

bool HttpsTransmitter::sendMessage(String &message)
{
  if (message.length() < 1)
    return false;

  if (!isConnectedToWiFi())
  {
    Serial.println("Pas connecté au WiFi");
    return false;
  }

  String jsonStr = buildMessage(message);
  Serial.println("envoie de :");
  Serial.println(jsonStr);

  https.begin(wifiClient, HTTPS_SERVER_URL);
  wifiClient.setInsecure();
  // wifiClient.setCACert(HTTPS_ROOT_CA_CERTIFICATE);

  https.addHeader("Content-Type", "application/json");
  int httpResponseCode = https.POST(jsonStr);

  if (httpResponseCode > 0)
  {
    Serial.print("Code HTTP : ");
    Serial.println(httpResponseCode);
    String response = https.getString();
    Serial.println("Réponse du serveur : ");
    Serial.println(response);
  }
  else
  {
    Serial.print("Erreur lors de l'envoi de la requête : ");
    Serial.println(https.errorToString(httpResponseCode));
  }

  https.end();

  return httpResponseCode > 0;
}

bool HttpsTransmitter::connectToWiFi()
{
  WiFi.begin(HTTPS_SSID, HTTPS_PASSWORD);
  Serial.println("Connexion en cours...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connexion en cours...");
  }

  Serial.println("Connecté au réseau WiFi");

  return true;
}

bool HttpsTransmitter::isConnectedToWiFi()
{
  return WiFi.status() == WL_CONNECTED;
}
