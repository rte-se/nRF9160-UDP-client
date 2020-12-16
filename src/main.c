#include <zephyr.h>
#include <stdio.h>
#include <net/socket.h>
#include <logging/log.h>
#include <errno.h>

#include "modem.h"
#include "led.h"

#define LOG_LEVEL CONFIG_MAIN_LOG_LEVEL
LOG_MODULE_REGISTER(MAIN);

#define SEND_INTERVAL_MS 10000

static uint8_t receive_buffer[256];

static struct sockaddr_in local_addr;
static struct sockaddr_in remote_addr;


bool udp_echo_test(const char *message) {

  set_led_0(true);

  int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock < 0) {
    LOG_ERR("Error opening socket: %d", errno);
    return false;
  }

  int err = bind(sock, (struct sockaddr *)&local_addr,
     sizeof(local_addr));
  if (err < 0) {
    LOG_ERR("bind err: %d", err);
    close(sock);
    return false;
  }
  
  err = blocking_connect(sock, (struct sockaddr *)&remote_addr,
  		       sizeof(struct sockaddr_in));
  if (err < 0) {
    LOG_ERR("Connect error: %d %d", err, errno);
    close(sock);
    return false;
  }

  int send_res = send(sock, message, strlen(message), 0);
  LOG_INF("Sent %d chars: \"%s\"", send_res, message);
  if (send_res < 0) {
    LOG_ERR("Send error: %d %d", send_res, errno);
    close(sock);
    return false;
  }

  int recv_res = blocking_recv(sock, receive_buffer, 256, 0);
  LOG_INF("Received %d chars: \"%s\"", recv_res, log_strdup(receive_buffer));

  close(sock);
  set_led_0(false);
  return true;
}


void main(void) {
  int64_t next_send_time = SEND_INTERVAL_MS;

  LOG_INF("Initialising board");

  modem_init();

  if (NULL == led_init()) {
    LOG_INF("Unable to initialize LED");
  }

  LOG_INF("Board inited! %s", CONFIG_BOARD);

  local_addr.sin_family = AF_INET;
  local_addr.sin_port = htons(0);
  local_addr.sin_addr.s_addr = 0;

  remote_addr.sin_family = AF_INET;
  remote_addr.sin_port = htons(CONFIG_UDP_SERVER_PORT);
  net_addr_pton(AF_INET, CONFIG_UDP_SERVER_IP, &remote_addr.sin_addr);

  next_send_time = k_uptime_get();

  while (1) {

    if (k_uptime_get() >= next_send_time) {

      if (udp_echo_test("Hello on UDP!")) {
        LOG_INF("Echo ok!"); 
      } else {
        LOG_INF("Failed with echo");
      }

      next_send_time += SEND_INTERVAL_MS;
    }

    int64_t remaining = next_send_time - k_uptime_get();
    if (remaining < 0) {
      remaining = 0;
    }
    k_sleep(K_MSEC(remaining));
  }
}
