idf_component_register(
    # REQUIRES log nvs_flash mdns wpa_supplicant lwip esp_http_server
    SRCS 
        "user_main.c"
        "hello_world_server.cc"    
)
