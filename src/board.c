#include <stdio.h>

#include <zephyr.h>
#include <logging/log.h>

#include "board.h"
#include "modem.h"
#include "led.h"

#define LOG_LEVEL CONFIG_BOARD_LOG_LEVEL
LOG_MODULE_REGISTER(BOARD);

enum {
  MESSAGE_MODEM,
  MESSAGE_SENSORS,
};

static MESSAGE last_message;

void board_init() {
  LOG_INF("Initialising board");

  modem_init();

  if (NULL == led_init()) {
    LOG_INF("Unable to initialize LED, darkness follows.");
  }

}

void board_dump_modem_message(uint8_t *buffer, int len) {

  modem_sample(&last_message.modem);
  last_message.uptime = k_uptime_get() / 1000;

  snprintf(buffer, len, "%d,%lld,%d,%d,%s,%d,%d,%s,%s,%s,%d,%d",
    MESSAGE_MODEM,
    last_message.uptime,
    last_message.modem.current_band,
    last_message.modem.area_code,
    last_message.modem.current_operator,
    last_message.modem.mcc,
    last_message.modem.mnc,
    last_message.modem.cellid_hex,
    last_message.modem.ip_address,
    last_message.modem.modem_fw,
    last_message.modem.battery,
    last_message.modem.imei);
}
