#pragma once

#include <net/socket.h>

typedef struct {
  uint16_t current_band;
  uint16_t area_code;
  char current_operator[100];
  uint16_t mcc;
  uint16_t mnc;
  char cellid_hex[100];
  char ip_address[100];
  char modem_fw[100];
  uint16_t battery;
  uint16_t imei;
} modem_t;

typedef struct {
  modem_t modem;
  int64_t uptime;
} MESSAGE;

void modem_init();

void modem_sample(modem_t *modem);

int blocking_connect(int fd, struct sockaddr *local_addr, socklen_t len);

int blocking_recv(int fd, void *buf, size_t size, int flags);

int blocking_send(int fd, const void *buf, size_t size, int flags);