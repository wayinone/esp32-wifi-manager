set(
    COMPONENT_SRCS 
        "wifi_manager.cc"
        "servers/http_app.cc"
        "servers/dns_server.cc"
        "utils/json.cc"
        "utils/nvs_sync.cc"
        "utils/mdns_settings.cc"
    )

set(
    COMPONENT_REQUIRES 
        "esp_wifi" 
        "esp_http_server" 
        "nvs_flash" 
        "lwip" 
        "wpa_supplicant"
        "log"
        "mdns"
    )

set(COMPONENT_ADD_INCLUDEDIRS "." "utils" "servers")  # For all the .h files

set(COMPONENT_EMBED_FILES "html/style.css" "html/code.js" "html/index.html")

register_component()