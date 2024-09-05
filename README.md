# esp32-wifi-manager V2

# Original esp32-wifi-manager
This repo is copied from [esp32-wifi-manager](https://github.com/tonyp7/esp32-wifi-manager). 
When use the code, I have encountered some problem (may be due to the newer esp-idf version). I then made some changes to fix bugs, and make some enhancement. Most of the original features were retained.

Note that currently, the official [Espressif wifi provisioning](https://github.com/espressif/esp-idf/tree/v5.3.1/examples/provisioning/wifi_prov_mgr) is through and app with either BLE or SoftAP. The component here use only SoftAP and not require additional app to be download for user.

# Usage
1. For first time setup, the device will entering AP mode, and user should select the SSID `esp32` in the wifi setting, with password `esp32pwd`
 
   <img src="./assets/change_wifi.PNG" alt="img" width="300">

2. Navigate to `10.10.0.1` to enter the wifi setting page.

    <img src="./assets/select_ssid.PNG" alt="img" width="300">

3. Select the your own SSID and enter password of your WIFI. Then `join`.

     <img src="./assets/enter_pw.PNG" alt="img" width="300">


4. (NEW FEATURE) Once success, your wifi credential is stored
   
   <img src="./assets/connect_success.PNG" alt="img" width="300">

   Hit "Close" will close the Access Point and your phone should automatically go back to your previous WIFI setting. Then you can hit the hyper link (in this case `192.168.1.7`) to access the hello world server provided by this example.

     <img src="./assets/hello_world.PNG" alt="img" width="300">

# Enhancement
* Re-arrange code so that it is easier to maintain and navigate.
* Clean up some bugs that prevent the build.
* Adding a new state `WM_READY_FOR_CUSTOM_PROCESS` and it will be triggered by the following two situations when the ESP device started:
  * When there is a pre-stored wifi credential and STA is connected.
  * When user entering wifi setting page (when wifi is on the AP mode), provide connect-able wifi credential, and hit `close` button in the page.
* Adding a close button  (`close-server` endpoint) in the wifi setting app, when successfully setup wifi password. Also provide the ip address that the STA mode is linked in the page.

  <img src="./assets/connect_success.PNG" alt="img" width="300">

  * 
  * This solves the issue of the web page hung when user entering the correct information. It was because the code was to turn off the AP mode immediately and there is no success signal return.
  * The `close-server` endpoint will trigger `WM_ORDER_STOP_AP` and then turn off the wifi setting page. 
    * It will then trigger `WM_READY_FOR_CUSTOM_PROCESS`

* Previously, after the wifi setting is done, with the linked ip address, user still access the wifi setting page, however, in my situations, I would like to spin up my own server:
  * I created a function `start_hello_world_webserver()` that spin up a very simple server. 
  * User can use the `wifi_manager_set_callback` when `WM_READY_FOR_CUSTOM_PROCESS` is triggered. E.g. 
  
  ```
  #include "wifi_manager.h"

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

  ```
    * This way, the custom webserver or process will be started once `WM_READY_FOR_CUSTOM_PROCESS` is triggered.
      * Previsously, the recommendation was to use `WM_EVENT_STA_GOT_IP` , however, when user just set up wifi password in the setting page, it will cause the service hang if we want to stop the wifi setting server (hence I implemented an extra api `close-server`)

# Configuration

This is what I use to test the code here.

#### ESP Device
esp32-cam (ESP32-CAM by AI Thinker). In PlatformIO's esp-idf extension, the target is `esp32`

#### IDE
I am building this esp-idf project on PlatformIO, with esp-idf extension.

#### esp-idf version
This is defined in `main/idf_component.yml`, currently I am running with ESP-IDF v5.3.0

# For Developer
To clean up the stored wifi credential, one can use
```
idf.py erase-flash
```
and then flash the device again.


# License
*esp32-wifi-manager* is MIT licensed. As such, it can be included in any project, commercial or not, as long as you retain original copyright. Please make sure to read the license file.
