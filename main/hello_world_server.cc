
#include "hello_world_server.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "esp_err.h"

static const char TAG[] = "HELLO_WORLD_SERVER";

httpd_handle_t server = NULL;


esp_err_t hello_world_index_handler(httpd_req_t *req){
    ESP_LOGI(TAG, "Serving Hello World page");

    const char* response = "<html><body><h1>Hello World!</h1></body></html>";
    httpd_resp_set_type(req, "text/html");
    return httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);
}

static const httpd_uri_t index_uri = {
  .uri       = "/",
  .method    = HTTP_GET,
  .handler   = hello_world_index_handler,
  .user_ctx  = NULL
};

void start_hello_world_webserver(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    // ESP_LOGI(TAG, "Starting custom server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &index_uri);
    } else {
        ESP_LOGE(TAG, "Error starting server!");
    }
}

