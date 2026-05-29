# Sistema Inteligente de Iluminação Pública com IoT

Projeto acadêmico desenvolvido para a disciplina de **Objetos Inteligentes Conectados**, com o objetivo de simular um sistema inteligente de iluminação pública utilizando **ESP32**, **sensor LDR**, **LED como atuador**, **protocolo MQTT** e a plataforma de simulação **Wokwi**.

O projeto está alinhado ao **Objetivo de Desenvolvimento Sustentável 11 (ODS 11) – Cidades e Comunidades Sustentáveis**, pois propõe uma solução voltada à automação da iluminação pública e ao uso mais eficiente da energia elétrica.

## Descrição do projeto

O sistema simula uma luminária pública inteligente capaz de ajustar automaticamente a intensidade da iluminação conforme a luminosidade do ambiente.

O sensor LDR realiza a leitura da luz ambiente. O ESP32 processa esse valor e calcula a intensidade do LED, que representa a luminária pública. Quanto menor a luminosidade detectada, maior será a intensidade do LED. Quando o ambiente está claro, o LED reduz sua intensidade até desligar.

Além disso, os dados são publicados em um broker MQTT, permitindo o monitoramento remoto das informações do sistema.

## Funcionamento

O fluxo geral do sistema é:

1. O ESP32 conecta-se à rede Wi-Fi simulada do Wokwi.
2. O ESP32 conecta-se ao broker MQTT público `broker.hivemq.com`.
3. O sensor LDR realiza a leitura da luminosidade ambiente.
4. O ESP32 converte a leitura do LDR em uma intensidade de LED entre 0 e 255.
5. O LED ajusta seu brilho de forma gradual.
6. Os dados são publicados via MQTT.
7. Um cliente MQTT, como o MQTTX Web, pode receber e visualizar os dados publicados.

## Componentes utilizados

| Função | Componente |
|---|---|
| Plataforma de prototipagem | ESP32 DevKit |
| Sensor | LDR / Photoresistor |
| Atuador | LED branco |
| Proteção elétrica | Resistor 220Ω |
| Comunicação | MQTT |
| Broker MQTT | HiveMQ Public Broker |
| Simulação | Wokwi |

## Hardware

O circuito foi montado no simulador Wokwi com os seguintes componentes:

- ESP32 DevKit;
- Sensor LDR conectado ao pino analógico GPIO34;
- LED conectado ao GPIO2;
- Resistor de 220Ω para proteção do LED.

A leitura do sensor LDR é feita por meio de uma entrada analógica do ESP32. O LED é controlado pelo ESP32, variando sua intensidade de acordo com a luminosidade detectada.

## Software

O código foi desenvolvido em linguagem C/C++ no ambiente do Wokwi, utilizando as bibliotecas:

- `WiFi.h`
- `PubSubClient.h`

A biblioteca `WiFi.h` é utilizada para conectar o ESP32 à rede simulada do Wokwi, enquanto a biblioteca `PubSubClient.h` permite a comunicação com o broker MQTT.

## Comunicação MQTT

O projeto utiliza o broker público:

```txt
broker.hivemq.com
