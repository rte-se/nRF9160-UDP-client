#pragma once

#include "modem.h"

typedef struct {
  modem_t modem;
  int64_t uptime;
} MESSAGE;

void board_init(void);

void board_dump_modem_message(uint8_t *buffer, int len);
