# STM32_RS41_ARDF
STM32 &amp; SI4032 RS41 ARDF test

Use:
https://www.wyzbee.com/download/Utilities/Software/CoIDE-1.7.8.exe

And:
https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update/+download/gcc-arm-none-eabi-5_4-2016q3-20160926-win32.exe

Have a nice day ;)


# Description
Foxes are synchronized by GPS signal and send your  position  in specific time.


# Configuration
All configs in ```config.h```




* ```APRS_CALLSIGN``` APRS callsign
* ```APRS COMMENT```  APRS comment

* ``` No_FOX``` How much Foxes in the cycle. If 1 -> without APRS, ACW all time
* ```Fox```   0- MOE, 1- MOI, 2- MOS, 3- MOH, 4- MO5, 5-  MO (without APRS), 6..17 Hunters - only APRS

* ```APRS_FREQUENCY``` APRS frequency in MHz
* ```ACW_FREQUENCY```Fox MOE..MO5 frequency in MHz
* ```ACW_FREQUENCY``` Fox MO Mhz middle frequency
* ```Smoc``` Power 0-7, where 7 means 42.95 mW@434.150 MHz measured on E4406A
* ```ALLOW_DISABLE_BY_BUTTON``` Allow disabling device using button

