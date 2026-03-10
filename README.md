# Sessão 0 — Introdução

## Objetivo

Este projeto apresenta o processo de configuração do ambiente de desenvolvimento para utilização do sistema operacional embarcado **Zephyr RTOS**, incluindo a instalação das dependências, criação de um projeto e execução em uma placa **ESP32**.

O objetivo principal é desenvolver uma aplicação simples capaz de:

- Controlar um **LED** conectado a um pino GPIO.
- Enviar mensagens para o **terminal serial**.

Para a execução prática do experimento foi utilizada uma placa **ESP32 DevKit V1**, que possui um LED embarcado conectado a um dos pinos GPIO do microcontrolador.

Dessa forma, o funcionamento do sistema pode ser demonstrado através do **piscar do LED** e da **impressão de mensagens no terminal**.

---

## Tecnologias Utilizadas

- **Zephyr RTOS**
- **ESP32 DevKit V1**
- **WSL (Windows Subsystem for Linux)**
- **Ubuntu**
- **West (gerenciador de projetos do Zephyr)**
- **C / GCC**

---

## Estrutura do Projeto

A estrutura básica do projeto é a seguinte:

# Sessão 1 — Preparar Ambiente no Windows

Nesta etapa será configurado o ambiente necessário no **Windows** para permitir o uso de ferramentas Linux através do **WSL (Windows Subsystem for Linux)**.

O WSL permite executar um sistema Linux diretamente dentro do Windows, o que facilita o desenvolvimento com ferramentas utilizadas pelo **Zephyr RTOS**.

---

# 1.1 Instalar o WSL

Abra o **Prompt de Comando** ou **PowerShell** como **Administrador** e execute:

```bash
wsl --install
```

Esse comando instala automaticamente:

- WSL
- Ubuntu
- Kernel Linux

Após a instalação, será necessário **reiniciar o computador**.

---

# 1.2 Primeiro acesso ao Ubuntu

Depois de reiniciar o computador:

1. Abra o **Ubuntu** pelo **Menu Iniciar**.
2. Aguarde a configuração inicial do sistema.

Na primeira execução será solicitado criar:

- Nome de usuário
- Senha

Exemplo:

```text
Enter new UNIX username: usuario
New password:
Retype new password:
```

Essas credenciais serão usadas sempre que for necessário executar comandos administrativos com `sudo`.

---

# 1.3 Atualizar o WSL (opcional)

Após a instalação, é recomendado atualizar o WSL.

Abra o **PowerShell** e execute:

```bash
wsl --update
```

Esse comando atualiza o **kernel do WSL**.

---

# 1.4 Verificar a instalação do WSL

Para verificar se o WSL está instalado corretamente, execute:

```bash
wsl --status
```

Exemplo de saída:

```text
Default Distribution: Ubuntu
Default Version: 2
```

Isso indica que o **Ubuntu está instalado e configurado corretamente**.

---

# 1.5 Verificar distribuições instaladas

Para listar as distribuições Linux instaladas no WSL:

```bash
wsl --list --verbose
```

Exemplo:

```text
NAME      STATE           VERSION
Ubuntu    Running         2
```

Isso confirma que o **Ubuntu está rodando com WSL 2**.

---

# Conclusão

Com o **WSL e o Ubuntu instalados**, o ambiente Linux está pronto para uso dentro do Windows.

Nas próximas sessões serão instaladas as dependências necessárias para:

- configurar o **Zephyr RTOS**
- instalar o **toolchain**
- criar e compilar o projeto para **ESP32**.

  
# Sessão 2 — Instalar Dependências no Linux

Após instalar o **WSL** e configurar o **Ubuntu**, o próximo passo é preparar o ambiente Linux com as dependências necessárias para utilizar o **Zephyr RTOS**.

Todas as etapas a seguir devem ser executadas no **terminal do Ubuntu dentro do WSL**.

---

# 2.1 Atualizar o sistema

Antes de instalar qualquer dependência, é recomendado atualizar os pacotes do sistema.

Execute:

```bash
sudo apt update
sudo apt upgrade -y
```

Esses comandos fazem o seguinte:

- `apt update` → atualiza a lista de pacotes disponíveis
- `apt upgrade` → atualiza os pacotes já instalados no sistema

---

# 2.2 Instalar dependências do Zephyr

O Zephyr RTOS necessita de diversas ferramentas de compilação e bibliotecas para funcionar corretamente.

Execute o comando abaixo para instalar todas as dependências necessárias:

```bash
sudo apt install -y \
git cmake ninja-build gperf \
ccache dfu-util device-tree-compiler \
wget python3-dev python3-pip python3-setuptools \
python3-wheel python3-venv python3-tk \
xz-utils file make gcc g++ \
libsdl2-dev libmagic1
```

Esses pacotes incluem:

- **git** — controle de versão
- **cmake** — sistema de build
- **ninja-build** — ferramenta de compilação rápida
- **gcc / g++** — compiladores C e C++
- **python3** e bibliotecas necessárias
- **device-tree-compiler** — utilizado pelo Zephyr para configuração de hardware

---

# 2.3 Verificar instalação do Python

O Zephyr utiliza diversas ferramentas baseadas em **Python**.

Verifique se o Python está instalado corretamente:

```bash
python3 --version
```

Exemplo de saída:

```text
Python 3.10.x
```

---

# 2.4 Verificar instalação do Git

O **Git** será utilizado para baixar o código do Zephyr e gerenciar repositórios.

Verifique a instalação executando:

```bash
git --version
```

Exemplo:

```text
git version 2.xx.x
```

---

# Conclusão

Com todas as dependências instaladas, o sistema Linux já possui as ferramentas necessárias para trabalhar com o **Zephyr RTOS**.

Na próxima sessão será instalado o **pipx**, que será utilizado para instalar ferramentas Python isoladas do sistema, incluindo o **West**, o gerenciador oficial de projetos do Zephyr.

# Sessão 3 — Instalar pipx

Nesta etapa será instalado o **pipx**, uma ferramenta utilizada para instalar aplicações Python em ambientes isolados.  
O **Zephyr RTOS** recomenda o uso do pipx para instalar ferramentas como o **West**, evitando conflitos com pacotes do sistema.

---

# 3.1 Instalar o pipx

No terminal do **Ubuntu (WSL)** execute o comando:

```bash
sudo apt install pipx
```

Esse comando instala o **pipx** através do gerenciador de pacotes do Ubuntu.

---

# 3.2 Configurar o PATH

Após a instalação, é necessário configurar o **PATH** para que os programas instalados com pipx possam ser executados no terminal.

Execute:

```bash
pipx ensurepath
```

Esse comando adiciona automaticamente o diretório do pipx ao PATH do sistema.

---

# 3.3 Reiniciar o terminal

Depois de executar `pipx ensurepath`, é necessário:

- fechar o terminal
- abrir o terminal novamente

Isso garante que o **PATH atualizado** seja carregado corretamente.

---

# 3.4 Verificar instalação do pipx

Para verificar se o pipx foi instalado corretamente, execute:

```bash
pipx --version
```

Exemplo de saída:

```text
1.x.x
```

Se o comando retornar uma versão, significa que o **pipx está funcionando corretamente**.

---

# Conclusão

Com o **pipx instalado e configurado**, agora é possível instalar ferramentas Python isoladas do sistema.

Na próxima sessão será instalado o **West**, que é o **gerenciador oficial de projetos do Zephyr RTOS**.

# Sessão 4 — Instalar West

O **West** é a ferramenta oficial utilizada pelo **Zephyr RTOS** para gerenciar projetos, repositórios e o processo de build.

Ele funciona como um gerenciador de workspace do Zephyr, permitindo:

- baixar os repositórios necessários
- gerenciar dependências
- compilar projetos
- executar comandos de build e flash

Nesta etapa será realizada a instalação do West utilizando o **pipx**.

---

# 4.1 Instalar o West

No terminal do **Ubuntu (WSL)** execute o comando:

```bash
pipx install west
```

Esse comando instala o **West** em um ambiente Python isolado.

---

# 4.2 Verificar instalação

Após a instalação, verifique se o West foi instalado corretamente executando:

```bash
west --version
```

Exemplo de saída:

```text
West version: 1.x.x
```

Se o comando retornar uma versão, significa que o **West está instalado e funcionando corretamente**.

---

# 4.3 O que é o West

O **West** é responsável por diversas tarefas dentro do ecossistema do Zephyr, como:

- inicializar um workspace do Zephyr
- baixar todos os repositórios necessários
- atualizar dependências
- gerenciar o processo de build

Alguns comandos comuns do West incluem:

```bash
west init
west update
west build
west flash
```

---

# Conclusão

Com o **West instalado**, agora é possível iniciar um **workspace do Zephyr** e baixar todos os componentes necessários para o desenvolvimento.

Na próxima sessão será realizado o **download do Zephyr RTOS e a criação do workspace do projeto**.

# Sessão 5 — Baixar Zephyr e Criar Workspace

Nesta etapa será feito o download do **Zephyr RTOS** e a criação do **workspace de desenvolvimento**.

O workspace é o diretório onde ficarão:

- o código do **Zephyr**
- as **dependências**
- os **projetos desenvolvidos**

---

# 5.1 Criar diretório do workspace

Primeiramente, crie o diretório onde o Zephyr será instalado.

```bash
mkdir ~/zephyrproject
cd ~/zephyrproject
```

Esse diretório será utilizado como **workspace principal do Zephyr**.

---

# 5.2 Inicializar o workspace

Agora é necessário inicializar o workspace utilizando o **West**.

```bash
west init
```

Esse comando cria a estrutura inicial do workspace.

Caso apareça a mensagem:

```text
FATAL ERROR: already initialized
```

significa que o workspace já foi inicializado anteriormente.

---

# 5.3 Baixar os repositórios do Zephyr

Após inicializar o workspace, é necessário baixar todos os repositórios utilizados pelo Zephyr.

Execute:

```bash
west update
```

Esse comando realiza o download de todos os componentes do Zephyr e suas dependências.

Esse processo pode demorar alguns minutos dependendo da velocidade da internet.

---

# 5.4 Instalar dependências Python do Zephyr

O Zephyr utiliza diversas ferramentas desenvolvidas em **Python**.

Para instalar essas dependências, execute:

```bash
west packages pip --install
```

Esse comando instala automaticamente todos os pacotes Python necessários para o funcionamento do Zephyr.

---

# 5.5 Instalar a Zephyr SDK (toolchain)

O **toolchain** é responsável por compilar os programas para diferentes arquiteturas de hardware.

Entre no diretório do Zephyr:

```bash
cd ~/zephyrproject/zephyr
```

Agora instale a **Zephyr SDK**:

```bash
west sdk install
```

Esse comando fará o download e instalação da SDK utilizada para compilar projetos do Zephyr.

---

# Estrutura do Workspace

Após a instalação, a estrutura do diretório ficará semelhante a:

```text
zephyrproject
│
├── zephyr
├── modules
├── tools
└── west.yml
```

---

# Conclusão

Com o **workspace criado** e o **Zephyr instalado**, o ambiente já está preparado para desenvolver aplicações embarcadas utilizando o **Zephyr RTOS**.

Na próxima sessão serão instaladas **dependências adicionais necessárias para suporte ao ESP32**.

# Sessão 6 — Suporte ao ESP32

Nesta etapa serão instaladas algumas **dependências adicionais necessárias para trabalhar com placas ESP32** utilizando o **Zephyr RTOS**.

Esses pacotes fornecem bibliotecas Python utilizadas por ferramentas de comunicação serial, criptografia e parsing de arquivos durante o processo de build e gravação do firmware.

---

# 6.1 Instalar dependências adicionais

No terminal do **Ubuntu (WSL)** execute o comando abaixo:

```bash
sudo apt install -y \
python3-serial python3-cryptography \
python3-future python3-pyparsing
```

Esses pacotes incluem:

- **python3-serial** — comunicação com dispositivos pela porta serial  
- **python3-cryptography** — biblioteca de criptografia utilizada por ferramentas do sistema  
- **python3-future** — compatibilidade entre versões do Python  
- **python3-pyparsing** — biblioteca utilizada para interpretar arquivos de configuração

---

# 6.2 Verificar instalação das bibliotecas

Após a instalação, é possível verificar se os pacotes foram instalados corretamente utilizando o Python.

Execute:

```bash
python3 -m pip list
```

Esse comando exibirá a lista de pacotes Python instalados no sistema.

---

# Conclusão

Com essas dependências instaladas, o ambiente passa a ter suporte às ferramentas necessárias para **compilar e interagir com placas ESP32** no Zephyr.

Na próxima sessão será criado o **projeto do aplicativo utilizando Zephyr RTOS**.

# Sessão 7 — Criar Projeto

Nesta etapa será criado o **projeto da aplicação** dentro do workspace do **Zephyr RTOS**.

O projeto conterá os arquivos básicos necessários para compilar e executar um programa utilizando o Zephyr.

---

# 7.1 Criar diretório do projeto

Primeiramente, entre no diretório do workspace do Zephyr:

```bash
cd ~/zephyrproject
```

Agora crie o diretório do projeto:

```bash
mkdir raptor_led_gui
cd raptor_led_gui
```

---

# 7.2 Criar estrutura do projeto

O projeto do Zephyr precisa de alguns arquivos básicos:

- **CMakeLists.txt** — define como o projeto será compilado
- **prj.conf** — configura opções do Zephyr
- **main.c** — código principal da aplicação

Crie a estrutura do projeto executando:

```bash
mkdir src
touch CMakeLists.txt
touch prj.conf
touch src/main.c
```

---

# 7.3 Estrutura do projeto

Após criar os arquivos, a estrutura do diretório ficará assim:

```text
raptor_led_gui
│
├── CMakeLists.txt
├── prj.conf
│
└── src
    └── main.c
```

Descrição dos arquivos:

- **CMakeLists.txt**  
  Arquivo responsável por configurar o sistema de build do projeto.

- **prj.conf**  
  Arquivo de configuração do Zephyr onde são habilitados drivers e recursos do sistema.

- **main.c**  
  Arquivo que contém o código principal da aplicação.

---

# Conclusão

Com a estrutura do projeto criada, o próximo passo será **editar os arquivos do projeto e adicionar o código da aplicação**.

Na próxima sessão serão apresentados os **arquivos utilizados no desenvolvimento do projeto**.

# Sessão 8 — Arquivos do Projeto

Nesta etapa serão apresentados os **principais arquivos utilizados no desenvolvimento da aplicação** utilizando o **Zephyr RTOS**.

Os arquivos podem ser editados diretamente no terminal utilizando o editor **nano**.

---

# 8.1 Editar arquivo CMakeLists.txt

Abra o arquivo para edição:

```bash
nano CMakeLists.txt
```

Conteúdo do arquivo:

```cmake
cmake_minimum_required(VERSION 3.20.0)

# Localiza a instalação do Zephyr no sistema
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Nome do projeto
project(raptor_led_gui)

# Define o arquivo fonte principal da aplicação
target_sources(app PRIVATE src/main.c)
```

Descrição:

- `cmake_minimum_required` define a versão mínima do CMake.
- `find_package(Zephyr ...)` localiza o Zephyr instalado no sistema.
- `project(...)` define o nome do projeto.
- `target_sources(...)` define quais arquivos serão compilados.

---

# 8.2 Editar arquivo prj.conf

Abra o arquivo:

```bash
nano prj.conf
```

Conteúdo do arquivo:

```conf
# Ativa o subsistema de GPIO do Zephyr
CONFIG_GPIO=y

# Permite imprimir mensagens no terminal
CONFIG_PRINTK=y
```

Descrição:

- `CONFIG_GPIO=y` habilita o driver de **GPIO**.
- `CONFIG_PRINTK=y` permite utilizar a função `printk()` para imprimir mensagens no terminal.

---

# 8.3 Editar arquivo main.c

Abra o arquivo principal:

```bash
nano src/main.c
```

Conteúdo do arquivo:

```c
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
```

Descrição do funcionamento do programa:

1. Inclui as bibliotecas do **kernel do Zephyr** e do **driver de GPIO**.
2. Define o pino **GPIO 2** como o pino do LED.
3. Obtém o dispositivo GPIO através da **Device Tree**.
4. Configura o pino como **saída digital**.
5. Entra em um **loop infinito** que:
   - alterna o estado do LED
   - espera 1 segundo
   - imprime uma mensagem no terminal

---

# Conclusão

Com os arquivos configurados, o projeto já possui tudo o que é necessário para ser **compilado e executado**.

Na próxima sessão será realizada a **compilação e execução do projeto utilizando o QEMU**.

# Sessão 9 — Compilar para ESP32

Após a criação e configuração dos arquivos do projeto, o próximo passo é **compilar o firmware para a placa ESP32** utilizando o sistema de build do **Zephyr RTOS**.

---

# 9.1 Acessar diretório do projeto

Primeiramente, entre no diretório do projeto:

```bash
cd ~/zephyrproject/raptor_led_gui
```

---

# 9.2 Compilar o projeto para ESP32

Execute o comando abaixo para compilar o projeto para a placa **ESP32 DevKitC**:

```bash
west build -b esp32_devkitc/esp32/procpu
```

Explicação do comando:

- `west build` → executa o processo de compilação
- `-b` → especifica a placa alvo
- `esp32_devkitc/esp32/procpu` → define a arquitetura do ESP32 utilizada

Durante o processo de compilação, o sistema irá:

- configurar o ambiente de build
- compilar o código fonte
- gerar os arquivos binários do firmware

---

# 9.3 Instalar esptool

Para gravar o firmware no ESP32, é necessário instalar a ferramenta **esptool**, utilizada para comunicação com o microcontrolador.

Execute:

```bash
pipx install esptool
```

---

# 9.4 Verificar instalação do esptool

Após a instalação, verifique se a ferramenta está funcionando:

```bash
esptool.py version
```

Exemplo de saída:

```text
esptool.py v4.x
```

Se a versão for exibida, significa que o **esptool foi instalado corretamente**.

---

# Conclusão

Com o projeto compilado e o **esptool instalado**, o ambiente já está pronto para realizar a **gravação do firmware na placa ESP32**.

Na próxima sessão será mostrado como **identificar a porta serial da placa no Windows**.

# Sessão 10 — Conectar ESP32

Para gravar o firmware na placa **ESP32**, primeiro é necessário identificar qual **porta serial (COM)** o dispositivo está utilizando no Windows.

---

# 10.1 Conectar a placa ESP32

Conecte a placa **ESP32 DevKit V1** ao computador utilizando um **cabo USB**.

O sistema operacional irá reconhecer automaticamente o dispositivo e criar uma **porta serial virtual**.

---

# 10.2 Descobrir a porta COM no Windows

Abra o **PowerShell** ou **Prompt de Comando** e execute o comando:

```powershell
mode
```

Esse comando exibirá todas as portas seriais disponíveis no sistema.

---

# 10.3 Identificar o dispositivo

Procure na lista um dispositivo semelhante a:

```text
USB-SERIAL CH340 (COM5)
```

Nesse exemplo:

- **CH340** é o chip conversor USB-Serial presente na placa
- **COM5** é a porta serial utilizada pelo dispositivo

O número da porta (**COM5**, **COM3**, **COM7**, etc.) pode variar dependendo do computador.

---

# Conclusão

Após identificar a **porta COM do ESP32**, será possível conectar essa porta ao ambiente **WSL**.

Na próxima sessão será mostrado como **compartilhar o dispositivo USB do Windows com o WSL utilizando o usbipd**.

# Sessão 11 — Conectar USB ao WSL

Para que o **Ubuntu no WSL** consiga acessar a placa **ESP32**, é necessário compartilhar o dispositivo USB do Windows com o WSL utilizando a ferramenta **usbipd**.

---

# 11.1 Listar dispositivos USB

Abra o **PowerShell como Administrador** e execute:

```powershell
usbipd list
```

Esse comando exibirá todos os dispositivos USB conectados ao computador.

Exemplo de saída:

```text
BUSID  DEVICE
4-4    USB-SERIAL CH340
```

---

# 11.2 Identificar o BUSID

O valor exibido na coluna **BUSID** identifica o dispositivo USB.

No exemplo acima:

```
BUSID = 4-4
```

Esse valor será utilizado para conectar o dispositivo ao WSL.

---

# 11.3 Associar o dispositivo ao sistema

Primeiro execute o comando:

```powershell
usbipd bind --busid X-Y
```

Substitua **X-Y** pelo valor exibido na coluna BUSID.

Exemplo:

```powershell
usbipd bind --busid 4-4
```

---

# 11.4 Conectar o dispositivo ao WSL

Agora conecte o dispositivo ao WSL executando:

```powershell
usbipd attach --wsl --busid X-Y
```

Exemplo:

```powershell
usbipd attach --wsl --busid 4-4
```

Após esse comando, o dispositivo USB ficará disponível dentro do **Ubuntu no WSL**.

---

# Conclusão

Com o dispositivo conectado ao WSL, o sistema Linux poderá acessar a **porta serial da placa ESP32**.

Na próxima sessão será mostrado como **verificar qual porta serial foi criada no Linux**.

# Sessão 12 — Verificar Porta no Linux

Após conectar o dispositivo USB ao **WSL**, é necessário verificar qual **porta serial** foi criada no ambiente Linux para a placa **ESP32**.

---

# 12.1 Listar dispositivos seriais

No terminal do **Ubuntu (WSL)** execute o comando:

```bash
ls /dev/tty*
```

Esse comando lista todos os dispositivos seriais disponíveis no sistema.

---

# 12.2 Identificar a porta do ESP32

Entre os dispositivos listados, normalmente aparecerá um dispositivo semelhante a:

```text
/dev/ttyUSB0
```

ou

```text
/dev/ttyACM0
```

Esses dispositivos representam a **porta serial associada à placa ESP32**.

Na maioria dos casos, placas com conversor **CH340** utilizam:

```
/dev/ttyUSB0
```

---

# Conclusão

Após identificar a porta serial, será necessário configurar as **permissões de acesso à porta** para que o usuário consiga utilizá-la sem restrições.

Na próxima sessão será mostrado como **configurar permissões para acesso à porta serial no Linux**.

# Sessão 13 — Permissão para Porta Serial

Para que o usuário possa acessar a **porta serial** no Linux sem utilizar permissões administrativas, é necessário adicionar o usuário ao grupo **dialout**.

Esse grupo possui permissão para acessar dispositivos seriais como:

- `/dev/ttyUSB0`
- `/dev/ttyACM0`

---

# 13.1 Adicionar usuário ao grupo dialout

No terminal do **Ubuntu (WSL)** execute o comando:

```bash
sudo usermod -a -G dialout $USER
```

Explicação do comando:

- `usermod` → modifica configurações de usuário
- `-a` → adiciona ao grupo sem remover grupos existentes
- `-G dialout` → grupo responsável por acesso a dispositivos seriais
- `$USER` → usuário atual do sistema

---

# 13.2 Reiniciar o WSL

Após adicionar o usuário ao grupo, é necessário reiniciar o **WSL** para aplicar as alterações.

No **PowerShell** execute:

```powershell
wsl --shutdown
```

Depois disso, abra novamente o **Ubuntu**.

---

# Conclusão

Com as permissões configuradas corretamente, o usuário já pode acessar a **porta serial do ESP32**.

Na próxima sessão será realizado o **processo de limpeza do build, compilação do firmware e gravação na placa ESP32**.

# Sessão 14 — Compilar e Gravar Firmware no ESP32

Nesta etapa será realizado o processo de **limpeza do build**, **compilação do projeto** e **gravação do firmware na placa ESP32**.

---

# 14.1 Acessar diretório do projeto

Primeiramente, entre no diretório do projeto:

```bash
cd ~/zephyrproject/raptor_led_gui
```

---

# 14.2 Limpar build anterior

Antes de compilar novamente o projeto, é recomendado remover a pasta de build anterior para evitar conflitos.

Execute:

```bash
rm -rf build
```

Esse comando remove completamente o diretório `build`.

---

# 14.3 Compilar o projeto para ESP32

Agora execute a compilação do projeto:

```bash
west build -b esp32_devkitc/esp32/procpu
```

Durante esse processo o sistema irá:

- configurar o ambiente de compilação
- compilar o código fonte
- gerar os arquivos binários do firmware

---

# 14.4 Gravar firmware no ESP32

Após a compilação, grave o firmware na placa executando:

```bash
west flash
```

Esse comando utiliza o **esptool** para transferir o firmware compilado para o microcontrolador.

---

# Conclusão

Após a gravação do firmware, o programa já estará armazenado na memória da placa **ESP32**.

Na próxima sessão será mostrado como **abrir o monitor serial para visualizar as mensagens enviadas pelo programa**.

# Sessão 15 — Monitor Serial

Após gravar o firmware na placa **ESP32**, é possível visualizar as mensagens enviadas pelo programa através do **monitor serial**.

Nesta etapa será utilizado o programa **minicom** para acessar a porta serial.

---

# 15.1 Instalar o minicom

No terminal do **Ubuntu (WSL)** execute:

```bash
sudo apt install minicom
```

O **minicom** é um programa utilizado para comunicação com dispositivos através da porta serial.

---

# 15.2 Conectar ao ESP32

Para abrir o monitor serial, execute:

```bash
minicom -D /dev/ttyUSB0 -b 115200
```

Explicação dos parâmetros:

- `-D /dev/ttyUSB0` → define a porta serial utilizada
- `-b 115200` → define a taxa de transmissão (baud rate)

---

# 15.3 Reiniciar a placa

Após abrir o **minicom**, pressione o botão **RESET** na placa **ESP32**.

O programa será iniciado novamente e as mensagens enviadas pelo firmware aparecerão no terminal.

Exemplo de saída:

```text
Hello World! This is Raptor!
```

A mensagem será exibida repetidamente a cada **1 segundo**, conforme definido no código da aplicação.

---

# 15.4 Sair do minicom

Para sair do monitor serial, utilize a sequência de teclas:

```
CTRL + A
X
Y
ENTER
```

Isso encerrará a conexão com a porta serial.

---

# Conclusão

Com o **monitor serial funcionando**, é possível acompanhar as mensagens enviadas pelo firmware e verificar se o programa está executando corretamente na placa **ESP32**.

Além disso, o LED conectado ao pino **GPIO 2** da placa estará piscando a cada **1 segundo**, demonstrando o funcionamento da aplicação desenvolvida com **Zephyr RTOS**.

# Sessão 16 — Conclusão

Este projeto apresentou o processo completo de configuração do ambiente para desenvolvimento utilizando o **Zephyr RTOS** com a placa **ESP32**.

Durante as etapas anteriores foram realizadas as seguintes atividades:

- Instalação do **WSL** e configuração do **Ubuntu** no Windows
- Instalação das **dependências necessárias para o Zephyr**
- Instalação das ferramentas **pipx** e **West**
- Download e configuração do **workspace do Zephyr**
- Instalação do **toolchain (Zephyr SDK)**
- Configuração do ambiente para suporte ao **ESP32**
- Criação da estrutura de um **projeto Zephyr**
- Implementação do código da aplicação em **C**
- Compilação do projeto utilizando o sistema de build do Zephyr
- Conexão da placa ESP32 ao **WSL**
- Gravação do firmware no microcontrolador
- Monitoramento da saída do programa através do **terminal serial**

A aplicação desenvolvida demonstrou o funcionamento básico do sistema embarcado ao:

- **Controlar um LED** conectado ao pino GPIO da placa
- **Enviar mensagens ao terminal serial**

Esse tipo de aplicação é frequentemente utilizado como **primeiro experimento em sistemas embarcados**, pois permite verificar rapidamente se todo o ambiente de desenvolvimento está configurado corretamente.

Com o ambiente preparado, torna-se possível desenvolver aplicações mais complexas utilizando os recursos oferecidos pelo **Zephyr RTOS**, como:

- gerenciamento de **threads**
- controle de **periféricos de hardware**
- comunicação com **sensores e dispositivos externos**
- desenvolvimento de sistemas embarcados **multitarefa**.

Dessa forma, o projeto serve como base para estudos e desenvolvimento de aplicações embarcadas utilizando **Zephyr RTOS e ESP32**.
```
