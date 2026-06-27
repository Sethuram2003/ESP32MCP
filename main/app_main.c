#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "components/Wifi/wifi_station.h"
#include "components/McpServer/mcp_server.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    /* 1. Initialize NVS */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    /* 2. Initialize and connect Wi-Fi */
    ESP_ERROR_CHECK(wifi_init_sta());

    /* Optional: block until we have an IP before starting MCP */
    ret = wifi_wait_for_connection(30000);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to connect to Wi-Fi within timeout");
        return;
    }
    ESP_LOGI(TAG, "Wi-Fi connected, proceeding to start MCP server...");

    /* 3. Initialize and start MCP server */
    ESP_ERROR_CHECK(mcp_server_app_init());
    ESP_ERROR_CHECK(mcp_server_app_start());

    /* 4. Keep the main task alive */
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}