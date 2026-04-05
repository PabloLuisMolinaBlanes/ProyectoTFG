/*
Esta función configura la funcionalidad ADC (Analog-Digital-Conversion) del examen psicotécnico con valores predeterminados.

Por defecto, se asumen los siguientes valores.

- Se asume se utilizarán los puertos GPIO35 y GPIO27 para dos potenciómetros, según el pinlist en https://gzhls.at/blob/ldb/1/b/3/9/ce458f9742b549ee683216c160d28abea52e.pdf
- Se asume como bitwidth el bitwidth por defecto que asigne el compilador.
- Se asume una atenuación de 12dB.
- Se realiza también una calibración para ambos puertos ADC.
*/
void configure_second_test();

/*
Esta función se repite de forma indefinida, e implementa la funcionalidad del examen psicotécnico relativo al dispositivo empotrado
*/
void second_examination_loop();