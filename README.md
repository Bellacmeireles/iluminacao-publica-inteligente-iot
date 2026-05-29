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
```

Porta utilizada pelo ESP32:

```txt
1883
```

Os tópicos MQTT utilizados são:

```txt
iluminacao/luminosidade
iluminacao/led
iluminacao/intensidade
```

### Tópicos publicados

| Tópico | Descrição |
|---|---|
| `iluminacao/luminosidade` | Publica o valor lido pelo sensor LDR |
| `iluminacao/led` | Publica o estado do LED: OFF, BAIXA, MEDIA ou ALTA |
| `iluminacao/intensidade` | Publica o valor da intensidade do LED entre 0 e 255 |

Para visualizar todas as mensagens do projeto em um cliente MQTT, pode-se assinar o tópico:

```txt
iluminacao/#
```

## Como executar o projeto no Wokwi

1. Acesse o projeto no Wokwi:

```txt
https://wokwi.com/projects/465130387961799681
```

2. Clique em **Start Simulation**.

3. Aguarde a conexão com o Wi-Fi e com o broker MQTT.

4. Altere a luminosidade no controle do sensor LDR.

5. Observe o LED mudando de intensidade conforme a luminosidade.

6. Abra um cliente MQTT, como o MQTTX Web, para visualizar as mensagens publicadas.

## Como testar no MQTTX Web

1. Acesse o MQTTX Web:

```txt
https://mqttx.app/web-client
```

2. Configure a conexão:

```txt
Name: Projeto IoT Isabella
Protocol: wss://
Host: broker.hivemq.com
Port: 8884
Path: /mqtt
Client ID: Notebook_Isabella_2026_01
Username: vazio
Password: vazio
SSL/TLS: ligado
```

3. Clique em **Connect**.

4. Crie uma nova assinatura com o tópico:

```txt
iluminacao/#
```

5. Rode o projeto no Wokwi e acompanhe as mensagens recebidas.

## Estrutura do repositório

```txt
.
├── sketch.ino
├── diagram.json
├── libraries.txt
└── README.md
```

## Arquivos

- `sketch.ino`: código-fonte principal do ESP32.
- `diagram.json`: estrutura do circuito montado no Wokwi.
- `libraries.txt`: bibliotecas utilizadas no projeto.
- `README.md`: documentação do projeto.

## Resultados esperados

Ao executar o projeto, espera-se que:

- o ESP32 conecte-se ao Wi-Fi simulado;
- o ESP32 conecte-se ao broker MQTT;
- o sensor LDR leia a luminosidade ambiente;
- o LED varie sua intensidade automaticamente;
- os dados sejam publicados nos tópicos MQTT;
- as mensagens sejam visualizadas em um cliente MQTT externo.

Exemplo de mensagens publicadas:

```txt
iluminacao/luminosidade → 610
iluminacao/led → ALTA
iluminacao/intensidade → 226
```

## Repositório do projeto

```txt
https://github.com/Bellacmeireles/iluminacao-publica-inteligente-iot/tree/main
```

## Link do projeto no Wokwi

```txt
https://wokwi.com/projects/465130387961799681
```

## Autora

**Isabella Cabral Meireles**  
Universidade Presbiteriana Mackenzie  
Disciplina: Objetos Inteligentes Conectados

## Licença

Projeto desenvolvido para fins acadêmicos.
