#include <Arduino.h>
#include "Portal.h"
#include "TheLock.h"

WebServer Server;          
AutoConnect      Portal(Server);
AutoConnectConfig config;


extern TheLock lock;

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

static const char PAGE_LOCKACTION[] PROGMEM = R"(
{
  "uri": "/actions",
  "title": "Actions",
  "menu": true,
  "auth": "digest",
  "element": [
    {
      "name": "text",
      "type": "ACText",
      "value": "<h2>Select Lock Action</h2>",
      "style": "font-family:Arial;font-size:18px;font-weight:400;color:#191970"
    },
    {
      "name": "steps",
      "type": "ACInput",
      "value": "200",
      "placeholder": "number of steps",
      "label": "Steps"
    },
    {
        "name": "lock",
        "type": "ACSubmit",
        "value": "LOCK",
        "uri": "/lock"
    },
    {
        "name": "unlock",
        "type": "ACSubmit",
        "value": "UNLOCK",
        "uri": "/unlock"
    }
  ]
}
)";

const char PAGE_LOCK[] PROGMEM = R"(
{
  "uri": "/lock",
  "title": "Lock",
  "menu": false,
  "auth": "digest",
  "element": [
    {
      "name": "results",
      "type": "ACText"
    }
  ]
}
)";


const char PAGE_UNLOCK[] PROGMEM = R"(
{
  "uri": "/unlock",
  "title": "UnLock",
  "menu": false,
  "auth": "digest",
  "element": [
    {
      "name": "results",
      "type": "ACText"
    }
  ]
}
)";


void redirect(String uri)
{
  Server.sendHeader("Location", uri, true);
  Server.send(302, "text/plain", "");
  Server.client().stop();
}

void rootPage() {
  char content[] = "Hello, world";
  Server.send(200, "text/plain", content);

  Serial.println("root page served");

  redirect("/_ac");
}

void lockPage() {
  char content[] = "Locked";
  Server.send(200, "text/plain", content);

  lock.Lock();

  Serial.println("lock page served");
}

void unlockPage() {
  char content[] = "Unlocked";
  Server.send(200, "text/plain", content);

  lock.Unlock();
  Serial.println("unlock page served");
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

String onActions(AutoConnectAux& aux, PageArgument& args) {

  aux["steps"].as<AutoConnectInput>().value = "100";
  return String("");
}


String onLock(AutoConnectAux& aux, PageArgument& args) {
  Serial.println("lock page served: "+ args.arg("steps"));

  int valueA = args.arg("steps").toInt();

  lock.SetSteps(valueA);
  lock.Lock();

  return String("");
}


String onUnLock(AutoConnectAux& aux, PageArgument& args) {
  Serial.println("unlock page served: "+ args.arg("steps"));

  int valueA = args.arg("steps").toInt();

  lock.SetSteps(valueA);
  lock.Unlock();

  return String("");
}

void portalSetup()
{
  config.auth = AC_AUTH_DIGEST;
  config.authScope = AC_AUTHSCOPE_PARTIAL | AC_AUTHSCOPE_WITHCP;
  config.username = DEFAULT_USER;
  config.password = DEFAULT_PASSWD;
  config.ota = AC_OTA_BUILTIN;

    // Setup AutoConnect
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  config.apid = "ESP-" + String((uint32_t)(ESP.getEfuseMac() >> 32), HEX);
  config.psk = DEFAULT_AP_PASSWD;

  Serial.print("Defalt AP Name:  ");
  Serial.println(config.apid);

  Portal.onConnect(apConnectCallback);
  Portal.onDetect(apDetectCallback);
  Portal.whileCaptivePortal(whileCaptivePortal);

  config.ticker = true;
  config.tickerPort = LED_BUILTIN;
  config.tickerOn = LOW;

  Portal.config(config);
  Portal.load(FPSTR(PAGE_AUTH));
  Portal.load(FPSTR(PAGE_LOCKACTION));
  Portal.load(FPSTR(PAGE_LOCK));
  Portal.load(FPSTR(PAGE_UNLOCK));
  // Portal.load(FPSTR(PAGE_HELLO));

  Server.on("/", rootPage);
  // Server.on("/lock", lockPage);
  // Server.on("/unlock", unlockPage);

  Portal.on("/actions", onActions);
  Portal.on("/lock", onLock);
  Portal.on("/unlock", onUnLock);

  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }
}

void portalLoop() {
    Portal.handleClient();
}