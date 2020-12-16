#pragma once

#include <device.h>

typedef struct {
  const struct device *led_dev;
} led_t;


bool led_init();

void set_led_0(bool on_off);