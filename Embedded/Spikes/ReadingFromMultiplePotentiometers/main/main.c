/*Código derivado del repositorio original de Lê Trung Kiên. Archivo relevante: https://github.com/ltkdt/LTKDT-s_small_projects/blob/master/esp_idf_adc/main.c. Perfil en GitHub: https://github.com/ltkdt*/

#include <string.h>
#include <sdkconfig.h>
#include <esp_log.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <esp_adc/adc_oneshot.h>
#include <hal/adc_types.h>

#include <esp_adc/adc_cali_scheme.h>
#include <esp_adc/adc_cali.h>

TaskHandle_t ADCTaskHandle = NULL;

void ADCTask(void *arg) {
    int potentiometer_read, potentiometer_output;
    int potentiometer_read_2, potentiometer_output_2;
    adc_oneshot_unit_handle_t handle = NULL;
    adc_oneshot_unit_handle_t handle_2 = NULL;
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_2,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    adc_oneshot_unit_init_cfg_t init_config2 = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &handle));
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config2, &handle_2));
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
    adc_oneshot_chan_cfg_t config_2 = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(handle, ADC_CHANNEL_7, &config));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(handle_2, ADC_CHANNEL_7, &config_2));
    adc_cali_handle_t cali_handle = NULL;
    adc_cali_handle_t cali_handle_2 = NULL;
    adc_cali_line_fitting_config_t cali_config = {
        .unit_id = ADC_UNIT_2,
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT
    };
    adc_cali_line_fitting_config_t cali_config_2 = {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT
    };
    ESP_ERROR_CHECK(adc_cali_create_scheme_line_fitting(&cali_config, &cali_handle));
    ESP_ERROR_CHECK(adc_cali_create_scheme_line_fitting(&cali_config_2, &cali_handle_2));
    while (1) {
        ESP_ERROR_CHECK(adc_oneshot_read(handle, ADC_CHANNEL_7, &potentiometer_read));
        adc_cali_raw_to_voltage(cali_handle, potentiometer_read, &potentiometer_output);
        printf("%d\n", potentiometer_output);
        ESP_ERROR_CHECK(adc_oneshot_read(handle_2, ADC_CHANNEL_7, &potentiometer_read_2));
        adc_cali_raw_to_voltage(cali_handle_2, potentiometer_read_2, &potentiometer_output_2);
        printf("%d\n", potentiometer_output_2);
        vTaskDelay(10/portTICK_PERIOD_MS);
    } 
} 

void app_main(void)
{
    xTaskCreatePinnedToCore(ADCTask, "ADC Task", 4096, NULL, 10, &ADCTaskHandle, 0);
}