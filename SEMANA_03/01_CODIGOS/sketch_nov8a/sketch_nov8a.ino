#include <Arduino.h>

// Definir constantes para os pinos de LED e botão.
const int LED1 = 15;
const int LED2 = 2;
const int LED3 = 4;
const int LED4 = 16;
const int BUTTON1 = 25;
const int BUTTON2 = 26;
const int BUTTON3 = 27;
const int BUTTON4 = 14;
const int BUTTONRESET = 12;
const int MAX_LEVEL = 4;

// Declarar arrays para armazenar os pinos de LED e botão, sequência do jogo e sequência do jogador.
int leds[4] = {LED1, LED2, LED3, LED4};
int buttons[4] = {BUTTON1, BUTTON2, BUTTON3, BUTTON4};
int sequence[MAX_LEVEL];
int player_sequence[MAX_LEVEL];

// Declarar variáveis para o nível atual e a velocidade da sequência.
int level = 0;
int speed = 1000;

// Configurar pinos como entradas ou saídas.
void setupPins() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT_PULLUP);
  }
  pinMode(BUTTONRESET, INPUT_PULLUP);
}

// Iniciar o jogo gerando uma sequência aleatória.
void startGame() {
  level = 1;
  randomSeed(analogRead(0));
  for (int i = 0; i < MAX_LEVEL; i++) {
    sequence[i] = random(0, 4);
  }
  delay(1000);
}

// Mostrar a sequência de LEDs para o jogador.
void showSequence() {
  for (int i = 0; i < level; i++) {
    int led_to_light = sequence[i];
    digitalWrite(leds[led_to_light], HIGH);
    delay(speed);
    digitalWrite(leds[led_to_light], LOW);
    delay(200);
  }
  delay(500);
}

// Obter a sequência de botões pressionada pelo jogador.
void getPlayerSequence() {
  int player_index = 0;
  while (player_index < level) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(buttons[i]) == LOW) {
        player_sequence[player_index] = i;
        digitalWrite(leds[i], HIGH);
        delay(200);
        digitalWrite(leds[i], LOW);
        player_index++;
        delay(200);
      }
    }
  }
  checkPlayerSequence();
}

// Verificar se a sequência do jogador corresponde à sequência gerada pelo jogo.
void checkPlayerSequence() {
  for (int i = 0; i < level; i++) {
    if (player_sequence[i] != sequence[i]) {
      level = 0;
      return;
    }
  }
  level++;
  delay(500);
}

// Resetar o jogo se o jogador falhar ou completar todos os níveis.
void resetGame() {
  level = 0;
}

// Configurar o jogo.
void setup() {
  setupPins();
}

// Executar o loop principal do jogo.
void loop() {
  if (level == 0) {
    if (digitalRead(BUTTONRESET) == LOW) {
      startGame();
    }
  } else if (level <= MAX_LEVEL) {
    showSequence();
    getPlayerSequence();
  } else {
    resetGame();
  }
}