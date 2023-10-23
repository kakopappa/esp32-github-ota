# ESP32 Github OTA Update

This repo demonstrates how to download a OTA bin file from GitHub and update it self. 

**This library supports only ESP32.**

1. Program checks for `VERSION_URL` for an update which returns an integer. recommened using something like YYYYMMDDRR where R = release of the day
2. Check the returned version aginst current firmware version `current_fw_version`
3. If a newer version is returned, update.