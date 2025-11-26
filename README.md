# 🚗 Simulador Automotivo: Sensor de Ré e Câmbio Sequencial

Este projeto é um sistema embarcado desenvolvido em **C++ para Arduino** que simula funcionalidades essenciais de um painel automotivo. O sistema integra um **sensor de estacionamento** com alertas audiovisuais e um **câmbio sequencial** controlado via joystick, exibindo a marcha atual em formato digital.

## 📋 Funcionalidades

### 1. Sensor de Estacionamento (Ré)
Utiliza um sensor ultrassônico para monitorar a distância traseira:
- **Seguro (> 30cm):** LED Verde ativo.
- **Atenção (20cm - 30cm):** LED Amarelo ativo + Alerta sonoro lento (Buzzer).
- **Perigo (< 20cm):** LED Vermelho ativo + Alerta sonoro rápido (Buzzer).

### 2. Câmbio Sequencial
Simula a troca de marchas (0 a 9) utilizando o eixo Y de um Joystick:
- **Mover para Frente:** Aumenta a marcha.
- **Mover para Trás:** Diminui a marcha.
- **Sistema Anti-Bouncing:** Implementado via software (`millis`) para evitar trocas acidentais múltiplas.
- **Saída Visual:** O sistema converte o número da marcha para **BCD (Binário Codificado em Decimal)**, permitindo conexão direta com decodificadores (como CD4511) e displays de 7 segmentos.

---

## 🛠️ Hardware Necessário

* 1x Arduino (Uno, Nano ou Mega)
* 1x Sensor Ultrassônico HC-SR04
* 1x Módulo Joystick Analógico (XY)
* 1x Buzzer (5V)
* 3x LEDs (Vermelho, Amarelo, Verde)
* 1x Display de 7 Segmentos + Decodificador CD4511 (Opcional, mas recomendado para visualizar as marchas)
* Resistores diversos

---

## 🔌 Esquema de Conexão (Pinagem)

### Entradas e Sensores
| Componente | Pino Arduino | Variável no Código |
| :--- | :---: | :--- |
| **Ultrassônico (Echo)** | 12 | `ECHO` |
| **Ultrassônico (Trig)** | 13 | `TRIG` |
| **Joystick (Eixo Y)** | A1 | `VRY` |

### Saídas de Alerta
| Componente | Pino Arduino | Variável no Código |
| :--- | :---: | :--- |
| **Buzzer** | 7 | `BUZZER` |
| **LED Verde** | 3 | `LED_VERDE` |
| **LED Amarelo** | 2 | `LED_AMARELO` |
| **LED Vermelho** | 1* | `LED_VERMELHO` |

*> **Atenção:** O pino 1 também é usado para transmissão Serial (TX). Desconecte o LED Vermelho ao carregar o código.*

### Saída BCD (Para Display de Marchas)
Conecte estes pinos às entradas A, B, C, D do seu decodificador de display.

| Bit BCD | Pino Arduino | Função |
| :--- | :---: | :--- |
| **Bit 0 (A)** | 4 | LSB ($2^0$) |
| **Bit 1 (B)** | 11 | ($2^1$) |
| **Bit 2 (C)** | 6 | ($2^2$) |
| **Bit 3 (D)** | 5 | MSB ($2^3$) |

---

## ⚙️ Detalhes da Implementação

### Lógica do Câmbio
O código lê a entrada analógica `A1`.
- **Limite Frente:** Leitura < 100 (Incrementa marcha).
- **Limite Trás:** Leitura > 900 (Decrementa marcha).
- **Debounce:** Existe um delay lógico de `250ms` (`DEBOUNCE_DELAY`) para garantir estabilidade na troca.

### Função `escrever_bcd`
Esta função auxiliar converte o número inteiro da marcha (ex: `5`) em sinais digitais nos 4 pinos de saída, permitindo o uso de apenas 4 fios para controlar um display numérico através de um decodificador.

## Video: https://youtube.com/shorts/ACfVjNOQFtE?si=X2YZzra2Ih4ip_8b
