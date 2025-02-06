 // **********  Versão 1.0 - Incremento do botão B ao piscar o led vermelho e verde do RGB ***********


#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definições dos pinos da BitDogLab
#define LED_R 13       // LED vermelho do RGB
#define LED_G 11       // LED verde do RGB
#define LED_B 12       // LED azul do RGB
#define BUTTON_A 5     // Botão A
#define BUTTON_B 6     // Botão B
#define BUZZER_PIN 21  // Buzzer A

int led_state = 0;  // Estado para alternar as cores do LED

// Função de inicialização do hardware
void initHardware() {
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_put(LED_R, 0);

    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_put(LED_G, 0);

    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_put(LED_B, 0);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);  // Pull-up interno

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);  // Pull-up interno

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0);
}

// Função para definir as cores do arco-íris
void setRainbowColor(int color) {
    gpio_put(LED_R, 0);
    gpio_put(LED_G, 0);
    gpio_put(LED_B, 0);

    switch (color) {
        case 0:  // Vermelho
            gpio_put(LED_R, 1);
            break;
        case 1:  // Laranja
            gpio_put(LED_R, 1);
            gpio_put(LED_G, 1);
            break;
        case 2:  // Amarelo
            gpio_put(LED_R, 1);
            gpio_put(LED_G, 1);
            break;
        case 3:  // Verde
            gpio_put(LED_G, 1);
            break;
        case 4:  // Azul
            gpio_put(LED_B, 1);
            break;
        case 5:  // Anil
            gpio_put(LED_B, 1);
            gpio_put(LED_R, 1);
            break;
        case 6:  // Violeta
            gpio_put(LED_B, 1);
            gpio_put(LED_R, 1);
            break;
        default:
            break;
    }
}

// Função para tocar som no buzzer
void playTone(int duration) {
    duration = duration > 5 ? 5 : duration;
    for (int i = 0; i < duration * 50; i++) {
        gpio_put(BUZZER_PIN, 1);
        sleep_us(500);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(500);
    }
    gpio_put(BUZZER_PIN, 0);
}

// Nova melodia de erro ao clicar no botão errado
void playErrorTone() {
    printf("Opa! Botão errado\n");

    // Frequências para a melodia: Do, Ré, Mi, Fá, Sol, Fá, Mi, Ré, Do
    int melody[] = {261, 294, 329, 349, 392, 349, 329, 294, 261};  // Frequências em Hz
    int duration = 200;  // Duração de cada nota (200ms)

    // Reproduz a melodia
    for (int i = 0; i < 9; i++) {
        gpio_put(BUZZER_PIN, 1);
        sleep_us(1000000 / melody[i]);  // Duração da nota (baseada na frequência)
        gpio_put(BUZZER_PIN, 0);
        sleep_ms(50);  // Pausa entre as notas
    }

    gpio_put(BUZZER_PIN, 0);  // Desliga o buzzer no final
}

// Função para piscar os LEDs antes de iniciar o jogo
void blinkLedsBeforeGame() {
    printf("Preparando... Piscar LEDs!\n");

    // Piscar os LEDs 5 vezes
    for (int i = 0; i < 5; i++) {
        gpio_put(LED_R, 1);  // Acende o LED vermelho
        gpio_put(LED_G, 1);  // Acende o LED verde
        gpio_put(LED_B, 1);  // Acende o LED azul
        sleep_ms(500);       // Espera por 500ms

        gpio_put(LED_R, 0);  // Apaga o LED vermelho
        gpio_put(LED_G, 0);  // Apaga o LED verde
        gpio_put(LED_B, 0);  // Apaga o LED azul
        sleep_ms(500);       // Espera por 500ms
    }

    printf("Jogo começando...\n");
}

// Função para iniciar o jogo
void startGame() {
    while (1) {
        printf("Prepare-se...\n");
        sleep_ms(rand() % 3000 + 2000);

        int current_led = led_state;
        setRainbowColor(current_led);
        absolute_time_t start = get_absolute_time();
        //printf("Aguardando botão...\n");

        int correct_button = (current_led == 0 || current_led == 3) ? BUTTON_B : BUTTON_A;  

        while (gpio_get(correct_button) == 1) {
            if (gpio_get(BUTTON_A) == 0 && correct_button != BUTTON_A) {
                playErrorTone();
                sleep_ms(500);
                continue;
            }
            if (gpio_get(BUTTON_B) == 0 && correct_button != BUTTON_B) {
                playErrorTone();
                sleep_ms(500);
                continue;
            }
        }

        gpio_put(LED_R, 0);
        gpio_put(LED_G, 0);
        gpio_put(LED_B, 0);

        absolute_time_t end = get_absolute_time();
        int reaction_time = absolute_time_diff_us(start, end) / 1000;

        printf("Tempo de reação: %d ms\n", reaction_time);
        playTone(reaction_time);

       // printf("Aguardando soltar botão...\n");
        while (gpio_get(correct_button) == 0);
        sleep_ms(500);

        led_state = (led_state + 1) % 7;  // Avança para a próxima cor do arco-íris
    }
}

// Função principal
int main() {
    stdio_init_all();
    initHardware();

    // Piscar os LEDs antes de começar o jogo
    blinkLedsBeforeGame();

    printf("Jogo Iniciado!\n");
    startGame();

    return 0;
}
