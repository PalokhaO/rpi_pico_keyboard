
#ifndef _LEDS_H_
#define _LEDS_H_

#include <pico/stdlib.h>

#define SER_PIN 22
#define OE_PIN 21
#define RCLK_PIN 0
#define SRCLK_PIN 1


void leds_init();
void leds_enable(bool enabled);
void leds_write(uint16_t mask);

#endif
