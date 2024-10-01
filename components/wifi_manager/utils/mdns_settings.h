#ifndef WIFI_MDNS_SETTINGS_H_
#define WIFI_MDNS_SETTINGS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize mDNS hostname, this allows the device to be accessed by a hostname instead of an IP address.
 * 
 * @param hostname The hostname to be used.
 * @param instance The instance name to be used.
 * @param add_mac_to_hostname If true, the last 3 bytes of the MAC address will be added to the hostname.
 * @param additional_suffix Additional suffix to be added to the hostname. We will add a hyphen between the hostname and the additional suffix.
 * 
 * @note This function requires to run nvs_flash_init(), esp_netif_init(), and esp_event_loop_create_default() before initialize.
 * @note And wifi should be initialized after calling this function. Check the function initWifiSta() in wifi/station_mode.cc for reference.
 */
void initWifiMDNS(char* hostname, char* instance, bool add_mac_to_hostname, char* add_additional_suffix);



#ifdef __cplusplus
}
#endif

#endif