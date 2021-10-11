#include <Arduino.h>
#include <WiFi.h>          
#include <WebServer.h>     
#include <AutoConnect.h>


WebServer Server;          
AutoConnect      Portal(Server);
AutoConnectConfig config;


#define DEFAULT_AP "esp32d"
#define DEFAULT_AP_PASSWD "987654321abc"

#define DEFAULT_USER "user"
#define DEFAULT_PASSWD "password"

static const char PAGE_HELLO[] PROGMEM = R"(
{
  "uri": "/hello",
  "title": "Hello",
  "menu": true,
  "element": [
    {
      "name": "text",
      "type": "ACText",
      "value": "Hello, word",
      "style": "font-family:Arial;font-size:18px;font-weight:400;color:#191970"
    }
  ]
}
)";

static const char PAGE_AUTH[] PROGMEM = R"(
{
  "uri": "/auth",
  "title": "Auth",
  "menu": true,
  "auth": "digest",
  "element": [
    {
      "name": "text",
      "type": "ACText",
      "value": "AutoConnect has authorized",
      "style": "font-family:Arial;font-size:18px;font-weight:400;color:#191970"
    }
  ]
}
)";


void rootPage() {
  char content[] = "Hello, world";
  Server.send(200, "text/plain", content);

  Serial.println("root page served");
}

void apConnectCallback (IPAddress& localIP)
{
  Serial.print("AP connected IP:");
  Serial.println(localIP);
}


unsigned long captiveStart;
bool apDetectCallback (IPAddress& localIP)
{
  Serial.print("Captive portal starting IP:");
  Serial.println(localIP);
  captiveStart = millis();

  return true;
}

bool whileCaptivePortal()
{
  Serial.print("Captive portal still running for:");
  Serial.println(  (millis() - captiveStart) / 1000);

  return true;
}

void portalSetup()
{
  config.auth = AC_AUTH_DIGEST;
  config.authScope = AC_AUTHSCOPE_PARTIAL | AC_AUTHSCOPE_WITHCP;
  config.username = DEFAULT_USER;
  config.password = DEFAULT_PASSWD;

    // Setup AutoConnect
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  Portal.config(DEFAULT_AP, DEFAULT_AP_PASSWD);
  Portal.onConnect(apConnectCallback);
  Portal.onDetect(apDetectCallback);
  Portal.whileCaptivePortal(whileCaptivePortal);

  Portal.config(config);
  Portal.load(FPSTR(PAGE_HELLO));
  Portal.load(FPSTR(PAGE_AUTH));

  Server.on("/", rootPage);
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }
}

void portalLoop() {
    Portal.handleClient();
}