# ESP32 Github OTA Update

This repo demonstrates how to download an OTA bin file from GitHub and update itself. 

**This library supports only ESP32.**

1. The program checks for `version_check_url` for an update that returns an integer (happens in a seperate RTOS task). recommended using something like YYYYMMDDRR where R = release of the day
2. Check the returned version against the current firmware version `current_fw_version`
3. If a newer version is returned, update.

## Minimal example
```c
// #define ENABLE_ESP32_GITHUB_OTA_UPDATE_DEBUG Uncomment to enable logs.

#include <WiFiClientSecure.h>
#include "HttpReleaseUpdate.h"
#include "ESP32GithubOtaUpdate.h"

const char* ota_file_url = "https://raw.githubusercontent.com/username/repo/main/esp32_latest.bin";
const char* version_check_url = "https://raw.githubusercontent.com/username/repo/main/version.txt";
const int current_fw_version = 2024092302;  // YYYYMMDDRR where R = release of the day
const int update_check_interval = 60; // Check every 60 seconds.

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
  otaUpdate.setOTADownloadUrl(ota_file_url);
  otaUpdate.setVersionCheckUrl(version_check_url);
  otaUpdate.setCurrentFirmwareVersion(current_fw_version);
  otaUpdate.setUpdateCheckInterval(update_check_interval);
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
