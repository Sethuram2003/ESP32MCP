#ifndef MCP_SERVER_APP_H
#define MCP_SERVER_APP_H

#include "esp_err.h"

/**
 * @brief Initialize the MCP server engine and register tools.
 *
 * Creates the MCP engine, registers tools, and prepares the manager config.
 *
 * @return ESP_OK on success, or an error code on failure.
 */
esp_err_t mcp_server_app_init(void);

/**
 * @brief Start the MCP server manager (HTTP transport).
 *
 * @return ESP_OK on success, or an error code on failure.
 */
esp_err_t mcp_server_app_start(void);

#endif /* MCP_SERVER_APP_H */