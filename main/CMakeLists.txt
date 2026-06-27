idf_component_register(SRCS "app_main.c" "mcp_server.c" "wifi_station.c"
                    INCLUDE_DIRS "." REQUIRES mcp-c-sdk nvs_flash esp_wifi esp_event esp_netif)
