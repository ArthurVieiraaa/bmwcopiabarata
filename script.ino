int ldr_pin = A3;

const int pino_a = 4;
const int pino_b = 11;
const int pino_c = 6;
const int pino_d = 5;

const int SW = 0;
const int VRY = A1;
const int VRX = A0;

const int TRIG = 13;
const int ECHO = 12;

const int BUZZER = 7;

const int LED_VERMELHO = 1;
const int LED_AMARELO = 2;
const int LED_VERDE = 3;

const int RGB_VERMELHO = 10;
const int RGB_AZUL = 9;
const int RGB_VERDE = 8;

const int DISTANCIA_PERTO = 20;      
const int DISTANCIA_APROXIMANDO = 30; 
const int TOM_RAPIDO = 400; 
const int TOM_LENTO = 200;  
const int TEMPO_DE_ESPERA = 200;

int contador_joystick = 0;
const int LIMITE_FRENTE = 100;
const int LIMITE_TRAS = 900;
long ultimo_incremento = 0;
const long DEBOUNCE_DELAY = 250;

void escrever_bcd(int numero) {
  if (numero < 0 || numero > 9) {
    numero = 0;
  }
  // A (2^0) -> pino_a (D4)
  digitalWrite(pino_a, (numero & 1) ? HIGH : LOW); 
  // B (2^1) -> pino_b (D11)
  digitalWrite(pino_b, (numero & 2) ? HIGH : LOW);
  // C (2^2) -> pino_c (D6)
  digitalWrite(pino_c, (numero & 4) ? HIGH : LOW);
  // D (2^3) -> pino_d (D5)
  digitalWrite(pino_d, (numero & 8) ? HIGH : LOW);
}

int sensor_morcego(int pinotrig, int pinoecho) {
    digitalWrite(pinotrig, LOW);
    delayMicroseconds(2);
    digitalWrite(pinotrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinotrig, LOW);
    return pulseIn(pinoecho, HIGH) / 58;
}

void setup() {
    Serial.begin(9600);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(LED_VERMELHO, OUTPUT);
    pinMode(LED_AMARELO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(pino_a, OUTPUT); 
    pinMode(pino_b, OUTPUT);
    pinMode(pino_c, OUTPUT);
    pinMode(pino_d, OUTPUT); 
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, LOW);
    noTone(BUZZER);
    escrever_bcd(contador_joystick);
}
void loop() {
    int distancia = sensor_morcego(TRIG, ECHO);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, LOW);
    noTone(BUZZER);
    if (distancia <= DISTANCIA_PERTO) {
        digitalWrite(LED_VERMELHO, HIGH);
        tone(BUZZER, TOM_RAPIDO); 
        delay(30);
        noTone(BUZZER); 
        delay(30);
    } else if (distancia <= DISTANCIA_APROXIMANDO) {
        digitalWrite(LED_AMARELO, HIGH);
        tone(BUZZER, TOM_LENTO); 
        delay(150);
        noTone(BUZZER); 
        delay(150);
    } else {
        digitalWrite(LED_VERDE, HIGH);
    }
 
  int leitura_y = analogRead(VRY);
  if ((millis() - ultimo_incremento) > DEBOUNCE_DELAY) {
    if (leitura_y < LIMITE_FRENTE) {
      if (contador_joystick < 9) {
        contador_joystick++;
        ultimo_incremento = millis(); 
      }
    } 
    else if (leitura_y > LIMITE_TRAS) {
      if (contador_joystick > 0) {
        contador_joystick--;
        ultimo_incremento = millis(); 
      }
    }
  }
  escrever_bcd(contador_joystick);
  delay(TEMPO_DE_ESPERA);
}
