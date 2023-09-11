/*
 * esp.c
 *
 * Created on: Aug 31, 2023
 * Author: Dell
 */

#include "../../common/bit_math.h"
#include "../../common/std_types.h"
#include "../../MCAL/uart/uart.h"

#define OK_validation 0
#define connected_validation 1
#define wifi_connected_validation 2  // Corrected the typo here

u8 ESP_validation(u8 validation, u8 time_out) {
    u8 arr[10] = {0};
    u8 i = 0;
    u8 result = 0;
    u8 temp = 0;

    while (i < 2) {  // Changed i<=1 to i<2 to ensure we read 2 characters
        temp = ESP_usart_receive_byte(time_out);  // Corrected the function name

        if (temp != 255) {
            arr[i] = temp;
            i++;
        }
    }

    switch (validation) {
    case OK_validation:
        if (arr[0] == 'O' && arr[1] == 'K') {  // Fixed the condition
            result = 1;
        }
        break;
    case connected_validation:
        if (arr[0] == 'C' && arr[1] == 'O') {
            result = 2;
        }
        break;
    case wifi_connected_validation:
        if (arr[0] == 'W' && arr[1] == 'I') {
            result = 3;
        }
        break;
    }

    return result;
}

void esp_init(void) {
    usart_init(1);  // Fixed the function name
    u8 result = 0;

    while (result == 0) {
        usart_send_string(1, "ATE0\r\n");
        result = ESP_validation(OK_validation, 1000);  // Added validation argument and a timeout
    }

     while (result_1 == 0) {
         usart_send_string(1, "AT+CWMODE=1\r\n");
         result_1 = ESP_validation(connected_validation, 1000);
     }
}

void esp_wifi_connection(u8* username, u8* password) {
    u8 result = 0;

    while (result == 0) {
        // Use the provided username and password variables in the command
        usart_send_string(1, "AT+CWJAP_CUR=\"");
        usart_send_string(1, username);
        usart_send_string(1, "\",\"");
        usart_send_string(1, password);
        usart_send_string(1, "\"\r\n");

        result = ESP_validation(wifi_connected_validation, 10000);  // Added validation argument and a longer timeout
    }
}

void esp_server(u8* username, u8* password) {
    u8 result = 0;

    while (result == 0) {
        // Use the provided username and password variables in the command
        usart_send_string(1, "AT+CIPSEND=\"");
        usart_send_string(1, username);
        usart_send_string(1, "\",\"");
        usart_send_string(1, password);
        usart_send_string(1, "\"\r\n");

        result = ESP_validation(connected_validation, 10000);  // Added validation argument and a longer timeout
    }
}
