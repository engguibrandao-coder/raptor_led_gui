Projeto Zephyr RTOS com ESP32
Preparação do Ambiente e Execução do Projeto
Objetivo

Este relatório apresenta o processo de configuração do ambiente de desenvolvimento para utilização do sistema operacional embarcado Zephyr RTOS, incluindo instalação de dependências, criação de projeto e execução em uma placa ESP32.

O objetivo do projeto é desenvolver uma aplicação simples capaz de controlar um LED e imprimir mensagens no terminal utilizando o Zephyr.

Para a execução prática do experimento, é utilizada uma placa de desenvolvimento ESP32 DevKit V1, que possui um LED embarcado conectado a um dos pinos GPIO do microcontrolador, permitindo demonstrar o funcionamento do sistema através do acionamento intermitente (piscar) do LED.

Parte 1 — Preparar ambiente no Windows
Passo 1 — Instalar WSL

Abra o Prompt de Comando como Administrador e execute:

wsl --install

Este comando instala automaticamente:

WSL

Ubuntu

Kernel Linux

Após a instalação, é necessário reiniciar o computador.

Parte 2 — Instalar dependências no Linux

Abra o terminal do Ubuntu no WSL.

Atualizar sistema
sudo apt update
sudo apt upgrade -y
Instalar dependências do Zephyr
sudo apt install -y \
git cmake ninja-build gperf \
ccache dfu-util device-tree-compiler \
wget python3-dev python3-pip python3-setuptools \
python3-wheel python3-venv python3-tk \
xz-utils file make gcc g++ \
libsdl2-dev libmagic1
Parte 3 — Instalar pipx
sudo apt install pipx

Configurar PATH:

pipx ensurepath

Depois feche e abra o terminal novamente.

Parte 4 — Instalar West

Instalar o gerenciador de projetos do Zephyr:

pipx install west

Testar instalação:

west --version

Exemplo esperado:

West version: 1.x.x
Parte 5 — Baixar Zephyr

Criar workspace:

mkdir ~/zephyrproject
cd ~/zephyrproject

Inicializar Zephyr:

west init

Caso apareça o erro:

FATAL ERROR: already initialized

significa que o workspace já foi inicializado.

Baixar repositórios:

west update

Instalar dependências Python:

west packages pip --install

Instalar toolchain:

cd ~/zephyrproject/zephyr
west sdk install
Parte 6 — Suporte ao ESP32

Instalar dependências adicionais:

sudo apt install -y \
python3-serial python3-cryptography \
python3-future python3-pyparsing
Parte 7 — Criar projeto

Criar diretório do projeto:

cd ~/zephyrproject
mkdir raptor_led_gui
cd raptor_led_gui

Criar estrutura do projeto:

mkdir src
touch CMakeLists.txt
touch prj.conf
touch src/main.c
Parte 8 — Arquivos do projeto

Os arquivos foram editados diretamente no terminal utilizando nano.

Arquivo CMakeLists.txt

Editar:

nano CMakeLists.txt

Conteúdo:

cmake_minimum_required(VERSION 3.20.0)

# Localiza a instalação do Zephyr no sistema
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Nome do projeto
project(raptor_led_gui)

# Define o arquivo fonte principal da aplicação
target_sources(app PRIVATE src/main.c)
Arquivo prj.conf

Editar:

nano prj.conf

Conteúdo:

# Ativa o subsistema de GPIO do Zephyr.
CONFIG_GPIO=y

# Permite imprimir mensagens no terminal
CONFIG_PRINTK=y
Arquivo main.c

Editar:

nano src/main.c

Conteúdo:

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED_PIN 2

const struct device *gpio_dev;

int main(void)
{
    gpio_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));

    if (!device_is_ready(gpio_dev)) {
        return 0;
    }

    gpio_pin_configure(gpio_dev, LED_PIN, GPIO_OUTPUT_ACTIVE);

    while (1) {

        gpio_pin_toggle(gpio_dev, LED_PIN);

        k_sleep(K_SECONDS(1));

        printk("Hello World! This is Raptor!\n");
    }
}
Execução do projeto
west build -b qemu_x86
west build -t run

Saída esperada:

Hello World! This is Raptor!
Parte 9 — Compilar para ESP32
cd ~/zephyrproject/raptor_led_gui
west build -b esp32_devkitc/esp32/procpu

Instalar esptool:

pipx install esptool

Verificar:

esptool.py version
Parte 10 — Conectar ESP32

Descobrir porta COM no Windows (PowerShell):

mode

Exemplo:

USB-SERIAL CH340 (COM5)
Parte 11 — Conectar USB ao WSL
usbipd list

Exemplo:

BUSID  DEVICE
4-4    USB-SERIAL CH340

Conectar ao WSL:

usbipd bind --busid X-Y
usbipd attach --wsl --busid X-Y

Substituir X-Y pelo valor do BUSID.

Parte 12 — Verificar porta no Linux
ls /dev/tty*

Normalmente:

/dev/ttyUSB0
Parte 13 — Permissão serial
sudo usermod -a -G dialout $USER

Reiniciar WSL:

wsl --shutdown
Limpar build e gravar firmware
cd ~/zephyrproject/raptor_led_gui
rm -rf build
west build -b esp32_devkitc/esp32/procpu
west flash
Parte 15 — Monitor serial

Instalar minicom:

sudo apt install minicom

Conectar:

minicom -D /dev/ttyUSB0 -b 115200

Pressione o botão RESET no ESP32.

Para sair do minicom:

CTRL + A
X
Y
ENTER
Conclusão

Este projeto apresentou o processo completo de preparação do ambiente para desenvolvimento utilizando o Zephyr RTOS com ESP32.

Foram descritos os passos para:

instalação do sistema

configuração das dependências

criação do projeto

compilação

gravação na placa

Com o ambiente configurado corretamente, é possível desenvolver aplicações embarcadas utilizando o Zephyr, aproveitando seus recursos de gerenciamento de hardware e multitarefa.
