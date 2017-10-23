# STM32_RTTY
STM32 &amp; SI4032 rtty test

Use:
https://www.wyzbee.com/download/Utilities/Software/CoIDE-1.7.8.exe

And:
https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update/+download/gcc-arm-none-eabi-5_4-2016q3-20160926-win32.exe

Have a nice day ;)

# Configuration
All configs in ```config.h```
Shift 450Hz

* ```CALLSIGN``` RTTY callsign
* ```APRS_CALLSIGN``` APRS callsign
* ```APRS_SSID``` APRS SSID - '1' -> 1, 'A' -> 10 etc.
* ```RTTY_TO_APRS_RATIO``` number of RTTY frames between each APRS frame
* ```RTTY_FREQUENCY``` RTTY frequency in MHz
* ```APRS_FREQUENCY``` APRS frequency in MHz
* ```RTTY_SPEED``` RTTY speed in bauds
* ```RTTY_7BIT``` Use 7 bit RTTY
* ```RTTY_USE_2_STOP_BITS``` use 2 stop bits
* ```Smoc``` Power 0-7, where 7 means 42.95 mW@434.150 MHz measured on E4406A
* ```tx_delay``` Delay between frames in milliseconds
* ```ALLOW_DISABLE_BY_BUTTON``` Allow disabling device using button