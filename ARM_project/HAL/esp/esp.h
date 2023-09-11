#ifndef ESP_H_
#define ESP_H_

#include "../../common/std_types.h"

// Function to validate ESP response
u8 ESP_validation(u8 validation, u8 time_out);

// Initialize ESP module
void esp_init(void);

// Establish Wi-Fi connection
void esp_wifi_connection(u8* username, u8* password);

// Configure ESP as a server
void esp_server(u8* username, u8* password);

#endif /* ESP_H_ */
