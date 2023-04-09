
#ifndef _UTILS_H_
#define _UTILS_H_

#include <pico/stdlib.h>
#include <hardware/timer.h>

#define EVERY(interval_ms) \
  static uint32_t start_ms = 0;\
  uint32_t curr = time_us_64()/1000;\
  if ( curr - start_ms < interval_ms) return;\
  start_ms += interval_ms;

bool board_button();
int board_led(bool state);

#endif
