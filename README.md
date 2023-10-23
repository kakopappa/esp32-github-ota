# ESP32 Github OTA Update

This repo demonstrates how to download a OTA bin file from GitHub and update it self. 

**This library supports only ESP32.**

1. Program checks for `VERSION_URL` for an update which returns an integer. recommened using something like YYYYMMDDRR where R = release of the day
2. Check the returned version aginst current firmware version `current_fw_version`
3. If a newer version is returned, update.

## Minimal example
```c
// #define ENABLE_ESP32_GITHUB_OTA_UPDATE_DEBUG Uncomment to enable logs.

#include <WiFiClientSecure.h>
#include "HttpReleaseUpdate.h"
#include "ESP32GithubOtaUpdate.h"

const char* OTA_FILE_LOCATION = "https://raw.githubusercontent.com/username/repo/main/esp32_latest.bin";
const char* VERSION_URL = "https://raw.githubusercontent.com/username/repo/main/version.txt";
const int current_fw_version = 2024092302;  // YYYYMMDDRR where R = release of the day

#define SSID  "" // Your WiFi SSID
#define PASS  "" // Your WiFi Password

ESP32GithubOtaUpdate otaUpdate;
 
void setupWiFi() {
  #if defined(ESP8266)
    WiFi.setSleepMode(WIFI_NONE_SLEEP); 
    WiFi.setAutoReconnect(true);
  #elif defined(ESP32)
    WiFi.setSleep(false); 
    WiFi.setAutoReconnect(true);
  #endif

  WiFi.begin(SSID, PASS);
  Serial.printf("[WiFi]: Connecting to %s", SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  Serial.printf("connected\r\n");
}

void setupOtaUpdate() {
  otaUpdate.setOTADownloadUrl(OTA_FILE_LOCATION);
  otaUpdate.setVersionCheckUrl(VERSION_URL);
  otaUpdate.setCurrentFirmwareVersion(current_fw_version);
  otaUpdate.setUpdateCheckInterval(60); // Check every 60 seconds.
  otaUpdate.begin();
}

void setup() {
  Serial.begin(9600);
  setupWiFi(); 
  setupOtaUpdate();
}

void loop() {
  delay(10000);
}

```
