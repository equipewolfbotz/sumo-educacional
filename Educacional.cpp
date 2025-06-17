  #include "Educacional.h"

EDUCACIONAL::EDUCACIONAL() {
  _trig = A5;
  _echo = A0;
  _in1 = 7;
  _in2 = 8;
  _in3 = 9;
  _in4 = 10;
  _pwm1 = 5;
  _pwm2 = 6;
  _SL1 = A1;
  _SL2 = A2;
}

void EDUCACIONAL::iniciar() {
  pinMode(_trig, OUTPUT);
  pinMode(_echo, INPUT);

  pinMode(_in1, OUTPUT);
  pinMode(_in2, OUTPUT);
  pinMode(_in3, OUTPUT);
  pinMode(_in4, OUTPUT);
  pinMode(_pwm1, OUTPUT);
  pinMode(_pwm2, OUTPUT);
  pinMode(_SL1,INPUT);
  pinMode(_SL2,INPUT);
}

long EDUCACIONAL::lerDistancia() {
  digitalWrite(_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trig, LOW);

  long duracao = pulseIn(_echo, HIGH);
  long distancia = duracao * 0.034 / 2;
  return distancia;
}

void EDUCACIONAL::direita() {
  digitalWrite(_in1, HIGH);
  digitalWrite(_in2, LOW);
  digitalWrite(_in3, HIGH);
  digitalWrite(_in4, LOW);
  analogWrite(_pwm1, _pwmValor1);
  analogWrite(_pwm2, _pwmValor2);
}

void EDUCACIONAL::esquerda() {
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, HIGH);
  digitalWrite(_in3, LOW);
  digitalWrite(_in4, HIGH);
  analogWrite(_pwm1, _pwmValor1);
  analogWrite(_pwm2, _pwmValor2);
}

void EDUCACIONAL::tras() {
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, HIGH);
  digitalWrite(_in3, HIGH);
  digitalWrite(_in4, LOW);
  analogWrite(_pwm1, _pwmValor1);
  analogWrite(_pwm2, _pwmValor2);
}

void EDUCACIONAL::frente() {
  digitalWrite(_in1, HIGH);
  digitalWrite(_in2, LOW);
  digitalWrite(_in3, LOW);
  digitalWrite(_in4, HIGH);
  analogWrite(_pwm1, _pwmValor1);
  analogWrite(_pwm2, _pwmValor2);
}

void EDUCACIONAL::parar() {
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, LOW);
  digitalWrite(_in3, LOW);
  digitalWrite(_in4, LOW);
  analogWrite(_pwm1, _pwmValor1);
  analogWrite(_pwm2, _pwmValor2);
}


void EDUCACIONAL::velocidade(int pwm1, int pwm2) {
  _pwmValor1 = pwm1;
  _pwmValor2 = pwm2;
}
