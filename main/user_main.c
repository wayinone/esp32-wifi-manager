/*
Copyright (c) 2017-2019 Tony Pottier

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

@file main.c
@author Tony Pottier
@brief Entry point for the ESP32 application.
@see https://idyl.io
@see https://github.com/tonyp7/esp32-wifi-manager
*/

#include "esp_system.h"
#include "esp_log.h"
#include "hello_world_server.h"

#include "wifi_manager.h"
#include "mdns_settings.h"


static const char TAG[] = "main";

/**
 * @brief this is an exemple of a callback that you can setup in your own app to get notified of wifi manager event.
 */
void cb_connection_ok(void *pvParameter)
{
	ip_event_got_ip_t *param = (ip_event_got_ip_t *)pvParameter;

	/* transform IP to human readable string */
	char str_ip[16];
	esp_ip4addr_ntoa(&param->ip_info.ip, str_ip, IP4ADDR_STRLEN_MAX);

	ESP_LOGI(TAG, "I have a connection and my IP is %s!", str_ip);
}

void cb_start_custom_server(void *pvParameter)
{
	start_hello_world_webserver();
	
}

void app_main()
{
	/* start the wifi manager */
	wifi_manager_start();
	/* register a callback for the start of the custom server */
	wifi_manager_set_callback(WM_READY_FOR_CUSTOM_PROCESS, &cb_start_custom_server);
}
