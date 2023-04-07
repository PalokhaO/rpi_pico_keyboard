#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "pico/cyw43_arch.h"

int main() {

  bi_decl(bi_program_description("This is a test binary."));
  bi_decl(bi_1pin_with_name(CYW43_WL_GPIO_LED_PIN, "On-board LED"));
  
  stdio_init_all();
  if (cyw43_arch_init()) {
      printf("Wi-Fi init failed");
      return -1;
  }
  while (true) {
      cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
      sleep_ms(250);
      cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
      sleep_ms(250);
  }
}
