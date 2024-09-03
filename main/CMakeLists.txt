idf_component_register(
    # REQUIRES log nvs_flash mdns wpa_supplicant lwip esp_http_server
    SRCS 
        "user_main.c"
        "include/wifi_manager.cc"
        "include/dns_server.cc"
        "include/http_app.cc"
        "include/nvs_sync.cc"
        "include/json.cc"
    
    
    EMBED_FILES 
        "include/style.css" 
        "include/code.js" 
        "include/index.html"        
)
