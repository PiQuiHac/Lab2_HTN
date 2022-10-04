#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"

void print_studentID(void *pvParameter)
{
    while (1)
    {
        printf("Nguyen Duy Khanh - 1913743 \n");
        printf("Pham Quoc Hoa - 1913474 \n");
        printf("Pham Lam Thao - 1915196 \n");
        printf("Nguyen Quoc Hung - 1913610 \n");
        gpio_set_level(GPIO_NUM_2, 0);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
void read_button(void *param)
{
    gpio_pad_select_gpio(GPIO_NUM_17);
    gpio_pad_select_gpio(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_17, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(GPIO_NUM_17, GPIO_PULLUP_ONLY);
    bool currentStatus = 1, previousStatus = 1;
    int count = 0;

    while (1)
    {
        currentStatus = gpio_get_level(GPIO_NUM_17);
        if (currentStatus == previousStatus && currentStatus == 0)
        {
            if (count == 0)
            {
                printf("ESP32\n");
                gpio_set_level(GPIO_NUM_2, 1);
            }
            count++;
        }
        else
        {
            previousStatus = currentStatus;
            count = 0;
        }
        vTaskDelay(20 / portTICK_RATE_MS);
    }
}
void app_main(void)
{
    xTaskCreate(print_studentID, "Print student ID", 2048, NULL, 5, NULL);
    xTaskCreate(read_button, "Reading from button", 2048, NULL, 6, NULL);
}