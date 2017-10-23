//
// Created by Admin on 2017-01-09.
//

#ifndef STM32_RTTY_APRS_H
#define STM32_RTTY_APRS_H

#ifdef __cplusplus
#include <stdint.h>
#include <stdlib.h>
#include "ublox.h"

extern "C" {
#endif
  void aprs_init();
  void aprs_timer_handler();
  uint8_t aprs_is_active();
  void aprs_send_position(GPSEntry gpsData, int8_t temperature, uint16_t voltage);
  void aprs_change_tone_time(uint16_t x);
  void aprs_test();
#ifdef __cplusplus
};
#endif
#endif //STM32_RTTY_APRS_H
