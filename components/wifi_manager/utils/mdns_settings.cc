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

#define MDNS_INSTANCE CONFIG_MDNS_INSTANCE

/** Generate host name based on sdkconfig, optionally adding a portion of MAC address to it.
 *  @return host name string allocated from the heap
 */
static char *generate_hostname(void) {
    #ifndef CONFIG_MDNS_ADD_MAC_TO_HOSTNAME
        return strdup(CONFIG_MDNS_HOSTNAME);
    #else
        uint8_t mac[6];
        char   *hostname;
        esp_read_mac(mac, ESP_MAC_WIFI_STA);
        if (-1 == asprintf(&hostname, "%s-%02X%02X%02X", CONFIG_MDNS_HOSTNAME, mac[3], mac[4], mac[5])) {
            abort();
        }
        return hostname;
    #endif
}

// initWifiMDNS requires to run this before initialize:
// nvs_flash_init();
// esp_netif_init();
// esp_event_loop_create_default();
void initWifiMDNS(void)
{   
    char *hostname = generate_hostname();
    //initialize mDNS    
    ESP_ERROR_CHECK( mdns_init() );
    //set mDNS hostname (required if you want to advertise services)
    ESP_ERROR_CHECK( mdns_hostname_set(hostname) );
    ESP_LOGI(TAG, "mdns hostname set to: %s.%s", hostname, "local");
    //set default mDNS instance name
    ESP_ERROR_CHECK( mdns_instance_name_set(MDNS_INSTANCE) );
    free(hostname);
}
