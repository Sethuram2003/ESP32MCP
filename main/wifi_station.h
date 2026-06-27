#ifndef WIFI_STATION_H
#define WIFI_STATION_H

#include "esp_err.h"

/**
 * @brief Initialize Wi-Fi in Station mode and connect to the configured AP.
 *
 * This function initializes the TCP/IP stack, creates the default event loop,
 * configures the Wi-Fi driver, and starts the connection process.
 *
 * @return ESP_OK on success, or an error code on failure.
 */
esp_err_t wifi_init_sta(void);

/**
 * @brief Block until Wi-Fi is connected and an IP address is obtained.
 *
 * @param timeout_ms Maximum time to wait in milliseconds.
 * @return ESP_OK if connected within timeout, ESP_ERR_TIMEOUT otherwise.
 */
esp_err_t wifi_wait_for_connection(uint32_t timeout_ms);

#endif /* WIFI_STATION_H */