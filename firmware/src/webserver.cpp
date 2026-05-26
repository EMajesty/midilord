#include "webserver.h"
#include "config.h"
#include <ESPAsyncWebServer.h>
#include <WiFi.h>

static AsyncWebServer server(80);

static const char INDEX_HTML[] PROGMEM = R"html(
<!DOCTYPE html>
<html>
<head><meta charset="utf-8"><title>midilord</title></head>
<body>
  <h1>midilord</h1>
  <p>hell world</p>
</body>
</html>
)html";

void setupWebServer() {
    WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
    Serial.printf("AP: %s  IP: %s\n", WIFI_SSID, WiFi.softAPIP().toString().c_str());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *req) {
        req->send_P(200, "text/html", INDEX_HTML);
    });

    server.onNotFound([](AsyncWebServerRequest *req) {
        req->send(404, "text/plain", "not found");
    });

    server.begin();
    Serial.println("Web server started");
}

void loopWebServer() {}
