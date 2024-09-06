#ifndef WIFI_MDNS_SETTINGS_H_
#define WIFI_MDNS_SETTINGS_H_


/**
 * @brief Initialize mDNS hostname, this allows the device to be accessed by a hostname instead of an IP address.
 * Note the hostname is set to '{CONFIG_MDNS_HOSTNAME}.local' and one can set CONFIG_MDNS_HOSTNAME in idf.py menuconfig.
 * 
 * @note This function requires to run nvs_flash_init(), esp_netif_init(), and esp_event_loop_create_default() before initialize.
 * @note And wifi should be initialized after calling this function. Check the funtion initWifiSta() in wifi/station_mode.cc for reference.
 */
void initWifiMDNS(void);


#endif