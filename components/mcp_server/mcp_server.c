#include "mcp_server.h"

#include "esp_log.h"
#include "esp_mcp_engine.h"
#include "esp_mcp_mgr.h"
#include "esp_mcp_tool.h"
#include "esp_mcp_property.h"

static const char *TAG = "MCP_SERVER_APP";

static esp_mcp_t *s_mcp = NULL;
static esp_mcp_mgr_handle_t s_mcp_handle = 0;

static esp_mcp_value_t greeting_tool_callback(const esp_mcp_property_list_t *properties)
{
    (void)properties;
    return esp_mcp_value_create_string("Hello! This is your ESP32 MCP server.");
}

esp_err_t mcp_server_app_init(void)
{
    ESP_ERROR_CHECK(esp_mcp_create(&s_mcp));

    esp_mcp_tool_t *tool = esp_mcp_tool_create(
        "greet",
        "Returns a friendly greeting (ignores parameters)",
        greeting_tool_callback
    );
    ESP_ERROR_CHECK(esp_mcp_add_tool(s_mcp, tool));

    esp_mcp_mgr_config_t config = {0};
    config.transport = esp_mcp_transport_http_server;
    config.instance = s_mcp;
    
    void *transport_config = NULL;
    esp_err_t err = esp_mcp_transport_http_server.create_config(NULL, &transport_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create HTTP server transport config: %s", esp_err_to_name(err));
        return err;
    }
    config.config = transport_config;

    ESP_ERROR_CHECK(esp_mcp_mgr_init(config, &s_mcp_handle));

    ESP_LOGI(TAG, "MCP server initialized");
    return ESP_OK;
}

esp_err_t mcp_server_app_start(void)
{
    ESP_ERROR_CHECK(esp_mcp_mgr_start(s_mcp_handle));
    ESP_LOGI(TAG, "MCP server started");
    return ESP_OK;
}