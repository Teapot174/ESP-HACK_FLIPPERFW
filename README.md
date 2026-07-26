# Flipper Zero ESP-HACK Port
![ESP-HACK](port.jpg)
Flipper Zero firmware port for ESP-HACK. Can work unstable.

## How to Flash

Download .bin from releases and flash to 0x0 with [esp.huhn.me](https://esptool.spacehuhn.com/). Also copy files from sdcard.zip to your SD (FAT32).

## Hardware
https://github.com/Teapot174/ESP-HACK

## Build (Windows)

### SH1106
```bat
python winbuild.py build --board wroom-sh
```
### SSD1306
```bat
python winbuild.py build --board wroom-ssd
```
