// Inclui o kernel principal do Zephyr.
// Esse header fornece funções do sistema operacional,
// como threads, delays (k_sleep), timers, etc.
#include <zephyr/kernel.h>

// Inclui o driver de GPIO do Zephyr.
// Esse driver permite controlar pinos digitais da placa,
// como ligar/desligar LEDs ou ler botões.
#include <zephyr/drivers/gpio.h>

// Define qual pino será usado para o LED.
// No ESP32 DevKit geralmente o LED onboard está no GPIO 2.
#define LED_PIN 2

// Ponteiro para a estrutura do dispositivo GPIO.
// No Zephyr, todo hardware (GPIO, UART, SPI, etc)
// é representado como um "device".
const struct device *gpio_dev;

// Função principal da aplicação.
// No Zephyr, o main() é executado como uma thread do sistema.
int main(void)
{
// Obtém o dispositivo GPIO a partir da Device Tree.
// DT_NODELABEL(gpio0) referencia o controlador principal
// de GPIO definido na descrição de hardware da placa.
gpio_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));

// Verifica se o dispositivo GPIO está pronto para uso.
// Se o driver não estiver inicializado corretamente,
// o programa simplesmente termina.
if (!device_is_ready(gpio_dev)) {
return 0;
}

// Configura o pino do LED como saída digital.
// GPIO_OUTPUT_ACTIVE significa que o pino começa em nível lógico alto.
gpio_pin_configure(gpio_dev, LED_PIN, GPIO_OUTPUT_ACTIVE);

// Loop infinito da aplicação.
// Em firmware embarcado, normalmente o programa nunca termina.
while (1) {

// Inverte o estado do pino do LED.
// Se estava ligado, desliga.
// Se estava desligado, liga.
gpio_pin_toggle(gpio_dev, LED_PIN);

// Faz o sistema esperar 1 segundo.
// K_SECONDS(1) converte 1 segundo para ticks do kernel.
k_sleep(K_SECONDS(1));

// Imprime mensagem no console serial.
// Essa mensagem aparecerá no monitor serial do Zephyr.
printk("Hello World! This is Raptor!\n");
}
}
