#include "uart.h"
#include <esp_adc/adc_oneshot.h>
#include <hal/adc_types.h>
#include "freertos/FreeRTOS.h"
#include <esp_adc/adc_cali_scheme.h>
#include <esp_adc/adc_cali.h>


/* Variables */
int potentiometer_read, potentiometer_output;
int potentiometer_read_2, potentiometer_output_2;
adc_oneshot_unit_handle_t handle = NULL;
adc_oneshot_unit_handle_t handle_2 = NULL;
adc_cali_handle_t cali_handle = NULL;
adc_cali_handle_t cali_handle_2 = NULL;
int configured_second = 0;
#define MILLISECONDS_BETWEEN_CHECKS 10


/* Configuraciones */
adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_2,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
adc_oneshot_unit_init_cfg_t init_config2 = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
adc_oneshot_chan_cfg_t config_2 = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
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

void configure_second_test() {
    if (configured_second == 1) {
        return;
    } 
    
    /* Configuración de unidades ADC */
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &handle));
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config2, &handle_2));
    
    /* Configuración de canales */
    ESP_ERROR_CHECK(adc_oneshot_config_channel(handle, ADC_CHANNEL_7, &config));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(handle_2, ADC_CHANNEL_7, &config_2));
    
    /* Configuración de calibracion */
    ESP_ERROR_CHECK(adc_cali_create_scheme_line_fitting(&cali_config, &cali_handle));
    ESP_ERROR_CHECK(adc_cali_create_scheme_line_fitting(&cali_config_2, &cali_handle_2));

    if (is_uart_already_configured() == 0) {
        configure_uart_with_default_options();
    }
    configured_second = 1;
}

void second_examination_loop() {
    if (configured_second == 0) {
        printf("Error. You should configure this examination first configure_second_test()\n");
        return;
    }
    while (1) {
        /* Lee y envia valor del primer potenciometro */
        ESP_ERROR_CHECK(adc_oneshot_read(handle, ADC_CHANNEL_7, &potentiometer_read));
        adc_cali_raw_to_voltage(cali_handle, potentiometer_read, &potentiometer_output);
        printf("%d\n", potentiometer_output);

        /* Lee y envia valor del segundo potenciometro */
        ESP_ERROR_CHECK(adc_oneshot_read(handle_2, ADC_CHANNEL_7, &potentiometer_read_2));
        adc_cali_raw_to_voltage(cali_handle_2, potentiometer_read_2, &potentiometer_output_2);
        printf("%d\n", potentiometer_output_2);

        /*Comprueba si host ha enviado un valor para salir */
        if (read_from_uart(MILLISECONDS_BETWEEN_CHECKS) == EXIT_VALUE) {
            break;
        }
        vTaskDelay(MILLISECONDS_BETWEEN_CHECKS/portTICK_PERIOD_MS);
    }
}