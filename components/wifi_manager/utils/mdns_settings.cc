// This file is modified from managed_components/espressif__mdns/examples/query_advertise/main/mdns_example_main.c

#include "mdns_settings.h"
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_netif_ip_addr.h"
#include "esp_mac.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "mdns.h"
#include "netdb.h"
#include "esp_err.h"

#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 1, 0)
/* CONFIG_LWIP_IPV4 was introduced in IDF v5.1, set CONFIG_LWIP_IPV4 to 1 by default for IDF v5.0 */

#ifndef CONFIG_LWIP_IPV4
#define CONFIG_LWIP_IPV4 1
#endif // CONFIG_LWIP_IPV4
#endif // ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 1, 0)

static const char *TAG = "WIFI_MDNS_SETTINGS";

/** Generate host name based on sdkconfig, optionally adding a portion of MAC address to it.
 *  @return host name string allocated from the heap
 */
static char *generate_hostname(char *hostname_raw, bool add_mac_to_hostname, char *add_additional_suffix)
{

    int hostname_size = strlen(hostname_raw) + strlen(add_additional_suffix) + 7 * (int)add_mac_to_hostname + 2;
    char hostname[hostname_size];
    if (add_mac_to_hostname)
    {
        uint8_t mac[6];
        esp_read_mac(mac, ESP_MAC_WIFI_STA);
        snprintf(hostname, hostname_size, "%s-%02X%02X%02X-%s", hostname_raw, mac[3], mac[4], mac[5], add_additional_suffix);
        return hostname;
    }
    else
    {
        snprintf(hostname, hostname_size, "%s-%s", hostname_raw, add_additional_suffix);
    }
    return strdup(hostname);
}

/**
 * @brief Check if the hostname is valid, The accept host name characters are: "a-z", "A-Z", "0-9", "-" and "_"
 * @return ESP_OK if the hostname is valid, otherwise ESP_ERR_INVALID_ARG
 */
esp_err_t is_hostname_valid(char *hostname)
{
    if (hostname == NULL)
    {
        return ESP_ERR_INVALID_ARG;
    }
    for (int i = 0; i < strlen(hostname); i++)
    {
        if (!((hostname[i] >= 'a' && hostname[i] <= 'z') || (hostname[i] >= 'A' && hostname[i] <= 'Z') || (hostname[i] >= '0' && hostname[i] <= '9') || hostname[i] == '-' || hostname[i] == '_'))
        {
            ESP_LOGE(TAG, "Invalid hostname character: %c", hostname[i]);
            return ESP_ERR_INVALID_ARG;
        }
    }
    return ESP_OK;
}

// initWifiMDNS requires to run this before initialize:
// nvs_flash_init();
// esp_netif_init();
// esp_event_loop_create_default();
void initWifiMDNS(char *hostname_raw, char *mdns_instance, bool add_mac_to_hostname, char *add_additional_suffix)
{
    ESP_ERROR_CHECK(is_hostname_valid(hostname_raw));
    char *hostname = generate_hostname(hostname_raw, add_mac_to_hostname, add_additional_suffix);

    // initialize mDNS
    ESP_ERROR_CHECK(mdns_init());
    // set mDNS hostname (required if you want to advertise services)
    ESP_ERROR_CHECK(mdns_hostname_set(hostname));
    ESP_LOGI(TAG, "mdns hostname set to: %s.%s", hostname, "local");
    // set default mDNS instance name
    ESP_ERROR_CHECK(mdns_instance_name_set(mdns_instance));
    free(hostname);
}
