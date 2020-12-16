#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <logging/log.h>
#include <devicetree.h>

#include "led.h"

#define LOG_LEVEL CONFIG_LED_LOG_LEVEL
LOG_MODULE_REGISTER(LED);

#define LED0_NODE DT_ALIAS(led0)

static led_t led;

bool led_init() {

  led.led_dev = device_get_binding(DT_GPIO_LABEL(LED0_NODE, gpios));
  if (led.led_dev == NULL) {
    LOG_ERR("LED binding error");
    return false;
  }
  
  int ret = gpio_pin_configure(led.led_dev, DT_GPIO_PIN(LED0_NODE, gpios), GPIO_OUTPUT_ACTIVE | DT_GPIO_FLAGS(LED0_NODE, gpios));
  if (ret < 0) {
    LOG_ERR("LED config error");
    return false;
  }

  return true;
}

void set_led_0(bool on_off) {
  gpio_pin_set(led.led_dev, DT_GPIO_PIN(LED0_NODE, gpios), (int)on_off);
}