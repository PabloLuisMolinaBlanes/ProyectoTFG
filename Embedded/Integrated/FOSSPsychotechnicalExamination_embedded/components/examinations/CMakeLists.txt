idf_component_register(SRCS "first_examination.c" "second_examination.c"
                    PRIV_REQUIRES utils esp_driver_gpio esp_adc
                    INCLUDE_DIRS "include")