#include <WiFi.h>          
#include <WebServer.h>     
#include <AutoConnect.h>

#ifndef LED_BUILTIN 
#define LED_BUILTIN 13
#endif

extern void portalSetup();
extern void portalLoop();
