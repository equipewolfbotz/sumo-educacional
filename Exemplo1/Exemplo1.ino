#include <Arduino.h>

// Mapeamento de pinos
#define PIN_SENSOR_ESQ      13
#define PIN_SENSOR_DIR      2
#define PIN_SENSOR_FRT      14
#define PIN_LINHA_DIR       4
#define PIN_LINHA_ESQ       27
#define PIN_MICROSTART      17

#define PIN_MOTOR_A1        19
#define PIN_MOTOR_A2        18
#define PIN_MOTOR_A_PWM     5

#define PIN_MOTOR_B1        21
#define PIN_MOTOR_B2        35 
#define PIN_MOTOR_B_PWM     33

// Flags
volatile bool linha_detectada = false;
unsigned int microstart = 0;

// Funções de controle PWM
void pwm_set_motor(uint8_t pin_pwm, uint8_t duty) {
  analogWrite(pin_pwm, duty); // 0 a 255
}

// Funções de movimento
void parar_motores() {
  digitalWrite(PIN_MOTOR_A1, LOW);
  digitalWrite(PIN_MOTOR_A2, LOW);
  digitalWrite(PIN_MOTOR_B1, LOW);
  digitalWrite(PIN_MOTOR_B2, LOW);
  digitalWrite(PIN_MOTOR_A_PWM, LOW);
  digitalWrite(PIN_MOTOR_B_PWM, LOW);
}

void full_frente() {
  digitalWrite(PIN_MOTOR_A1, HIGH);
  digitalWrite(PIN_MOTOR_A2, LOW);
  digitalWrite(PIN_MOTOR_B1, HIGH);
  digitalWrite(PIN_MOTOR_B2, LOW);
  digitalWrite(PIN_MOTOR_A_PWM, HIGH);
  digitalWrite(PIN_MOTOR_B_PWM, HIGH);
  // ledcAttachPin(PIN_MOTOR_A_PWM, 0);
  // ledcSetup(0, 3000, 8);
  // ledcAttachPin(PIN_MOTOR_B_PWM, 1);
  // ledcSetup(1, 3000, 8);
  // pwm_set_motor(PIN_MOTOR_A_PWM, 200);
  // pwm_set_motor(PIN_MOTOR_B_PWM, 200);
}

void frente() {
  full_frente();
}

// void virar_direita() {
//   digitalWrite(PIN_MOTOR_A1, LOW);
//   digitalWrite(PIN_MOTOR_A2, HIGH);
//   digitalWrite(PIN_MOTOR_B1, HIGH);
//   digitalWrite(PIN_MOTOR_B2, LOW);
  // pwm_set_motor(PIN_MOTOR_A_PWM, 200);
  // pwm_set_motor(PIN_MOTOR_B_PWM, 200);
// }

// void virar_esquerda() {
//   digitalWrite(PIN_MOTOR_A1, HIGH);
//   digitalWrite(PIN_MOTOR_A2, LOW);
//   digitalWrite(PIN_MOTOR_B1, LOW);
//   digitalWrite(PIN_MOTOR_B2, HIGH);
//   pwm_set_motor(PIN_MOTOR_A_PWM, 200);
//   pwm_set_motor(PIN_MOTOR_B_PWM, 200);
// }

// void procurar_oponente() {
//   digitalWrite(PIN_MOTOR_A1, LOW);
//   digitalWrite(PIN_MOTOR_A2, HIGH);
//   digitalWrite(PIN_MOTOR_B1, HIGH);
//   digitalWrite(PIN_MOTOR_B2, LOW);
//   pwm_set_motor(PIN_MOTOR_A_PWM, 150);
//   pwm_set_motor(PIN_MOTOR_B_PWM, 150);
// }

// void recuar() {
//   digitalWrite(PIN_MOTOR_A1, LOW);
//   digitalWrite(PIN_MOTOR_A2, HIGH);
//   digitalWrite(PIN_MOTOR_B1, LOW);
//   digitalWrite(PIN_MOTOR_B2, HIGH);
//   pwm_set_motor(PIN_MOTOR_A_PWM, 220);
//   pwm_set_motor(PIN_MOTOR_B_PWM, 220);
// }

// ISR para sensores de linha
void IRAM_ATTR isr_sensor_linha() {
  linha_detectada = true;
}

// Leitura dos sensores
//typedef uint8_t u8;
uint8_t leitura_sensores() {
  return (digitalRead(PIN_SENSOR_DIR) << 0) |
         (digitalRead(PIN_SENSOR_FRT) << 1) |
         (digitalRead(PIN_SENSOR_ESQ) << 2);
}

// void decidir_movimento(uint8_t estado) {
//   switch (estado) {
//     case 0b010: full_frente(); Serial.println("Frente"); break;
//     case 0b011: frente();      Serial.println("F e D"); break;
//     case 0b001: virar_direita(); Serial.println("Direita"); break;
//     case 0b100: virar_esquerda(); Serial.println("Esquerda"); break;
//     case 0b110: frente();      Serial.println("F e E"); break;
//     case 0b101: frente();      Serial.println("E e D"); break;
//     case 0b111: full_frente(); Serial.println("Tudo"); break;
//     case 0b000: procurar_oponente(); Serial.println("Nenhum"); break;
//     default: frente(); Serial.println("Default"); break;
//   }
// }

void setup_gpio() {
  pinMode(PIN_SENSOR_ESQ, INPUT);
  pinMode(PIN_SENSOR_DIR, INPUT);
  pinMode(PIN_SENSOR_FRT, INPUT);
  pinMode(PIN_LINHA_DIR, INPUT_PULLUP);
  pinMode(PIN_LINHA_ESQ, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_LINHA_DIR), isr_sensor_linha, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_LINHA_ESQ), isr_sensor_linha, FALLING);

  pinMode(PIN_MICROSTART, INPUT);

  pinMode(PIN_MOTOR_A1, OUTPUT);
  pinMode(PIN_MOTOR_A2, OUTPUT);
  pinMode(PIN_MOTOR_B1, OUTPUT);
  pinMode(PIN_MOTOR_B2, OUTPUT);

  // ledcAttachPin(PIN_MOTOR_A_PWM, 0);
  // ledcSetup(0, 3000, 8);
  // ledcAttachPin(PIN_MOTOR_B_PWM, 1);
  // ledcSetup(1, 3000, 8);
}

// TaskHandle_t movimentoTaskHandle;
// void movimentoTask(void* parametro) {
//   while (1) {
//     if (digitalRead(PIN_MICROSTART) == HIGH) {
//       if (linha_detectada) {
//         recuar();
//         linha_detectada = false;
//         vTaskDelay(300 / portTICK_PERIOD_MS);
//       } else {
//         uint8_t estado = leitura_sensores();
//         decidir_movimento(estado);
//         vTaskDelay(400 / portTICK_PERIOD_MS);
//       }
//     } else {
//       parar_motores();
//       Serial.println("Aguardando microstart...");
//       vTaskDelay(100 / portTICK_PERIOD_MS);
//     }
//   }
// }

void setup() {
  //Serial.begin(115200);
  setup_gpio();
  //parar_motores();

 //else{parar_motores();}
  // xTaskCreatePinnedToCore(
  //   movimentoTask,
  //   "Movimento",
  //   2048,
  //   NULL,
  //   1,
  //   &movimentoTaskHandle,
  //   1
  // );
}

void loop() {
  // Nada aqui
 microstart = digitalRead(PIN_MICROSTART);
   if(PIN_SENSOR_FRT == 1){
  frente();
  delay(10);
 }
  else parar_motores();
}
