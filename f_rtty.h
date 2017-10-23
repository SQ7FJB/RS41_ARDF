#include <stdint.h>
#include "config.h"

typedef enum {
  rttyZero = 0,
  rttyOne = 1,
  rttyEnd = 2
} rttyStates;
static const uint8_t RTTY_PRE_START_BITS = 10;

rttyStates send_rtty(char *znak);
extern uint8_t start_bits;