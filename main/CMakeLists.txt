idf_component_register(
    SRCS "app_main.c"
    INCLUDE_DIRS "."
    REQUIRES 
        wifi_station
        mcp_server
        nvs_flash
)