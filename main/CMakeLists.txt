idf_component_register(
    # REQUIRES log nvs_flash mdns wpa_supplicant lwip esp_http_server
    SRCS 
        "user_main.c"
        "wifi_manager/wifi_manager.cc"
        "wifi_manager/utils/nvs_sync.cc"
        "wifi_manager/utils/json.cc"
        "wifi_manager/servers/dns_server.cc"
        "wifi_manager/servers/http_app.cc"
        "hello_world_server.cc"    
            
    EMBED_FILES 
        "wifi_manager/html/style.css" 
        "wifi_manager/html/code.js" 
        "wifi_manager/html/index.html"        
)
