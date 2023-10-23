#pragma once

#ifdef ENABLE_ESP32_GITHUB_OTA_UPDATE_DEBUG
  #ifdef DEBUG_ESP_PORT
    #define DEBUG_ESP32GOA(...) DEBUG_ESP_PORT.printf( __VA_ARGS__ )
  #else
    #define DEBUG_ESP32GOA(...) if(Serial) Serial.printf( __VA_ARGS__ )
  #endif
#else
  #define DEBUG_ESP32GOA(x...) if (false) do { (void)0; } while (0)
#endif

class ESP32GithubOtaUpdate {
  public:
    void setOTADownloadUrl(const char* otaDownloadUrl);
    void setVersionCheckUrl(const char* versionCheckUrl);
    void setCurrentFirmwareVersion(int currentFirmwareVersion);
    void setUpdateCheckInterval(int updateCheckInterval);
    void begin();    
    void checkForOTA();
          
  private:
    void setClock();    
    bool doVersionCheck();
    void doFirmwareUpdate();

    static constexpr auto *rootCACertificate = \
      "-----BEGIN CERTIFICATE-----\n"
      "MIIEvjCCA6agAwIBAgIQBtjZBNVYQ0b2ii+nVCJ+xDANBgkqhkiG9w0BAQsFADBh\n"
      "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
      "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
      "QTAeFw0yMTA0MTQwMDAwMDBaFw0zMTA0MTMyMzU5NTlaME8xCzAJBgNVBAYTAlVT\n"
      "MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxKTAnBgNVBAMTIERpZ2lDZXJ0IFRMUyBS\n"
      "U0EgU0hBMjU2IDIwMjAgQ0ExMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKC\n"
      "AQEAwUuzZUdwvN1PWNvsnO3DZuUfMRNUrUpmRh8sCuxkB+Uu3Ny5CiDt3+PE0J6a\n"
      "qXodgojlEVbbHp9YwlHnLDQNLtKS4VbL8Xlfs7uHyiUDe5pSQWYQYE9XE0nw6Ddn\n"
      "g9/n00tnTCJRpt8OmRDtV1F0JuJ9x8piLhMbfyOIJVNvwTRYAIuE//i+p1hJInuW\n"
      "raKImxW8oHzf6VGo1bDtN+I2tIJLYrVJmuzHZ9bjPvXj1hJeRPG/cUJ9WIQDgLGB\n"
      "Afr5yjK7tI4nhyfFK3TUqNaX3sNk+crOU6JWvHgXjkkDKa77SU+kFbnO8lwZV21r\n"
      "eacroicgE7XQPUDTITAHk+qZ9QIDAQABo4IBgjCCAX4wEgYDVR0TAQH/BAgwBgEB\n"
      "/wIBADAdBgNVHQ4EFgQUt2ui6qiqhIx56rTaD5iyxZV2ufQwHwYDVR0jBBgwFoAU\n"
      "A95QNVbRTLtm8KPiGxvDl7I90VUwDgYDVR0PAQH/BAQDAgGGMB0GA1UdJQQWMBQG\n"
      "CCsGAQUFBwMBBggrBgEFBQcDAjB2BggrBgEFBQcBAQRqMGgwJAYIKwYBBQUHMAGG\n"
      "GGh0dHA6Ly9vY3NwLmRpZ2ljZXJ0LmNvbTBABggrBgEFBQcwAoY0aHR0cDovL2Nh\n"
      "Y2VydHMuZGlnaWNlcnQuY29tL0RpZ2lDZXJ0R2xvYmFsUm9vdENBLmNydDBCBgNV\n"
      "HR8EOzA5MDegNaAzhjFodHRwOi8vY3JsMy5kaWdpY2VydC5jb20vRGlnaUNlcnRH\n"
      "bG9iYWxSb290Q0EuY3JsMD0GA1UdIAQ2MDQwCwYJYIZIAYb9bAIBMAcGBWeBDAEB\n"
      "MAgGBmeBDAECATAIBgZngQwBAgIwCAYGZ4EMAQIDMA0GCSqGSIb3DQEBCwUAA4IB\n"
      "AQCAMs5eC91uWg0Kr+HWhMvAjvqFcO3aXbMM9yt1QP6FCvrzMXi3cEsaiVi6gL3z\n"
      "ax3pfs8LulicWdSQ0/1s/dCYbbdxglvPbQtaCdB73sRD2Cqk3p5BJl+7j5nL3a7h\n"
      "qG+fh/50tx8bIKuxT8b1Z11dmzzp/2n3YWzW2fP9NsarA4h20ksudYbj/NhVfSbC\n"
      "EXffPgK2fPOre3qGNm+499iTcc+G33Mw+nur7SpZyEKEOxEXGlLzyQ4UfaJbcme6\n"
      "ce1XR2bFuAJKZTRei9AqPCCcUZlM51Ke92sRKw2Sfh3oius2FkOH6ipjv3U/697E\n"
      "A7sKPPcw7+uvTPyLNhBzPvOk\n"
      "-----END CERTIFICATE-----\n";

  const char* _otaDownloadUrl; 
  const char* _versionCheckUrl;
  int _currentFirmwareVersion;
  int _updateCheckInterval = 60; // 60 seconds.   
};

void ESP32GithubOtaUpdate::setUpdateCheckInterval(int updateCheckInterval) {
    _updateCheckInterval = updateCheckInterval;
}

void ESP32GithubOtaUpdate::setOTADownloadUrl(const char* otaDownloadUrl) {
    _otaDownloadUrl = otaDownloadUrl;
}

void ESP32GithubOtaUpdate::setVersionCheckUrl(const char* versionCheckUrl) {
    _versionCheckUrl = versionCheckUrl;
}

void ESP32GithubOtaUpdate::setCurrentFirmwareVersion(int currentFirmwareVersion) {
    _currentFirmwareVersion = currentFirmwareVersion;
}

void ESP32GithubOtaUpdate::doFirmwareUpdate() {
  DEBUG_ESP32GOA("[doFirmwareUpdate()]: Downloading new firmware update ..\r\n");

  WiFiClientSecure client;
  client.setCACert(rootCACertificate);
  client.setTimeout(12);
  client.setHandshakeTimeout(8);
   
  {  // WiFiClientSecure needs to be destroyed after HttpReleaseUpdate
    HttpReleaseUpdate httpUpdate;
    httpUpdate.rebootOnUpdate(true);

    httpUpdate.onStart([](void) {
       DEBUG_ESP32GOA("[doFirmwareUpdate()]: Start downloading..\r\n");
    });
    httpUpdate.onEnd([](bool success) {
      DEBUG_ESP32GOA("[doFirmwareUpdate()]: Downloading ended.\r\n");
      //if (success) SPIFFS.remove("/update");
    });
    httpUpdate.onProgress([](int progress, int total) {
      DEBUG_ESP32GOA("[doFirmwareUpdate()]: Downloading: %d\r\n", (progress / (total / 100)));
    });
    auto ret = httpUpdate.update(client, _otaDownloadUrl);
    switch (ret) {
      case HTTP_UPDATE_FAILED:
        DEBUG_ESP32GOA("[doFirmwareUpdate()]: Http Update Failed (Error=%d): %s\r\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
        break;
      case HTTP_UPDATE_NO_UPDATES:
        DEBUG_ESP32GOA("[doFirmwareUpdate()]: No Update!\r\n");
        break;
      case HTTP_UPDATE_OK:
        DEBUG_ESP32GOA("[doFirmwareUpdate()]: Update OK!\r\n");
        break;
    }
  }
}

bool ESP32GithubOtaUpdate::doVersionCheck() { 
  DEBUG_ESP32GOA("[doVersionCheck()]: Checking for new firmware update ..\r\n");

  bool isUpdateAvailable = false;
  WiFiClientSecure *client = new WiFiClientSecure;

  if(client) {
    client->setCACert(rootCACertificate);
    client->setTimeout(12);
    {
       // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is 
      HTTPClient https;
      if (https.begin(*client, _versionCheckUrl)) {
        int httpCode = https.GET();  

        if (httpCode > 0) {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String server_fw_version = https.getString();            
            int new_fw_version_int = server_fw_version.toInt();            
            DEBUG_ESP32GOA("[doVersionCheck()]: Current FW version: %d. Server FW version: %d \r\n", _currentFirmwareVersion, new_fw_version_int);
            
            if (_currentFirmwareVersion == new_fw_version_int) {
              DEBUG_ESP32GOA("[doVersionCheck()]: Device is already on latest firmware version: %d\r\n", _currentFirmwareVersion);                            
            } else {
              DEBUG_ESP32GOA("[doVersionCheck()]: New firmware version available version!\r\n");
              isUpdateAvailable = true;
            }
          }
        } else {
          DEBUG_ESP32GOA("[doVersionCheck()]: GET... failed, error: %s\r\n", https.errorToString(httpCode).c_str());
        }  
        https.end();
      } else {
        DEBUG_ESP32GOA("[doVersionCheck()]: Unable to connect\r\n");
      }      
    } // End extra scoping block  
    delete client;
  } else {
    DEBUG_ESP32GOA("[doVersionCheck()]: Unable to create WiFiClientSecure client!!\r\n");
  } 

  return isUpdateAvailable;
}

void ESP32GithubOtaUpdate::checkForOTA()
{
    for (;;)
    {
      if(doVersionCheck()) {
        doFirmwareUpdate();
      }
      vTaskDelay((_updateCheckInterval * 1000) / portTICK_PERIOD_MS);
    }
}

void ESP32GithubOtaUpdate::setClock() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");  // UTC
  DEBUG_ESP32GOA("Waiting for NTP time sync: ");

  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    yield();
    delay(500);
    DEBUG_ESP32GOA(".");
    now = time(nullptr);
  }
  DEBUG_ESP32GOA("\r\n");

  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  DEBUG_ESP32GOA("Current time: %s\r\n", asctime(&timeinfo));
}

void ESP32GithubOtaUpdate::begin() {
  setClock();

  xTaskCreate([](void* o){ static_cast<ESP32GithubOtaUpdate*>(o)->checkForOTA(); },
          "ESP32OTAUpdateTask",    // Name of the task (for debugging)
          1024 * 8,                // Stack size (bytes)
          this,                   // Parameter to pass
          5,                      // Task priority
          NULL);                    // Task handle
}
