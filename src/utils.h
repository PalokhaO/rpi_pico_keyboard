
#ifndef _UTILS_H_
#define _UTILS_H_

#include <pico/stdlib.h>
#include <hardware/timer.h>


#define EVERY_US(interval_us) \
  static uint32_t start_us = 0;\
  uint32_t curr = time_us_64();\
  if ( curr - start_us < interval_us) return;\
  start_us += interval_us;
#define EVERY_MS(interval_ms) EVERY_US(interval_ms * 1000)

bool board_button();
int board_led(bool state);

#endif
