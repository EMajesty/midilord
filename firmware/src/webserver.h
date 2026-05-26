#pragma once

void setupWebServer();
// loopWebServer() is a no-op — ESPAsyncWebServer runs on FreeRTOS tasks.
void loopWebServer();
