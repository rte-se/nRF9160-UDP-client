#include <zephyr.h>
#include <modem/lte_lc.h>
#include <modem/modem_info.h>
#include <logging/log.h>
#include <stdio.h>

#include "modem.h"

#define LOG_LEVEL CONFIG_MODEM_LOG_LEVEL
LOG_MODULE_REGISTER(MODEM);

struct modem_param_info modem_param;
static MESSAGE last_message;

void modem_init() {
  int err;

#if defined(CONFIG_LTE_LINK_CONTROL)
  if (!IS_ENABLED(CONFIG_LTE_AUTO_INIT_AND_CONNECT)) {
    LOG_INF("LTE Link Connecting...");
    err = lte_lc_init_and_connect();
    __ASSERT(err == 0, "LTE link could not be established.");
    LOG_INF("LTE Link Connected!");
  }
#endif /* defined(CONFIG_LTE_LINK_CONTROL) */

  err = modem_info_init();
  __ASSERT(err == 0, "Modem info module could not be initialized.");
  err = modem_info_params_init(&modem_param);
  __ASSERT(err == 0, "Modem info parameter structure could not be initialized.");
}

void modem_sample(modem_t *modem) {
  int err;

  // Null out

  err = modem_info_params_get(&modem_param);
  if (err == 0) {
    modem->current_band = modem_param.network.current_band.value;
    modem->area_code = modem_param.network.area_code.value;
    memcpy(&modem->current_operator, &modem_param.network.current_operator.value_string, 100);
    modem->mcc = modem_param.network.mcc.value;
    modem->mnc = modem_param.network.mnc.value;
    memcpy(&modem->cellid_hex, &modem_param.network.cellid_hex.value_string, 100);
    memcpy(&modem->ip_address, &modem_param.network.ip_address.value_string, 100);
    memcpy(&modem->modem_fw, &modem_param.device.modem_fw.value_string, 100);
    modem->battery = modem_param.device.battery.value;
    modem->imei = modem_param.device.imei.value;
  }
}

void board_dump_modem_message(uint8_t *buffer, int len) {

  modem_sample(&last_message.modem);
  last_message.uptime = k_uptime_get() / 1000;

  snprintf(buffer, len, "%lld,%d,%d,%s,%d,%d,%s,%s,%s,%d,%d",
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

int blocking_connect(int fd, struct sockaddr *local_addr, socklen_t len)
{
	int err;

	do {
		err = connect(fd, local_addr, len);

	} while (err < 0 && errno == EAGAIN);

	return err;
}

int blocking_recv(int fd, void *buf, size_t size, int flags)
{
	int err;

	do {
		err = recv(fd, buf, size, flags);
	} while (err < 0 && errno == EAGAIN);

	return err;
}

int blocking_send(int fd, const void *buf, size_t size, int flags)
{
	int err;

	do {
		err = send(fd, buf, size, flags);
	} while (err < 0 && errno == EAGAIN);

	return err;
}
