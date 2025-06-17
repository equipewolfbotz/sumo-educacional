#ifndef EDUCACIONAL_H
#define EDUCACIONAL_H

#include <Arduino.h>

class EDUCACIONAL {
  public:
    // Construtor: trig, echo, motor A (in1, in2), motor B (in3, in4)
    EDUCACIONAL();

    void iniciar();                 // Configura os pinos
    long lerDistancia();           // Retorna a distância em cm

    void frente();                 // Move para frente
    void tras();                   // Move para trás
    void esquerda();               // Vira à esquerda
    void direita();                // Vira à direita
    void parar();                  // Para os motores
    void velocidade(int pwm1, int pwm2);
  private:
    int _trig, _echo;              // Pinos do sensor ultrassônico
    int _in1, _in2, _in3, _in4;    // Pinos da ponte H (motores)
    int _SL1, _SL2;  //Pinos sensores led laterais
    int _pwm1, _pwm2;    //Pinos PWM 
    int _pwmValor1 = 255;
    int _pwmValor2 = 255;
};

#endif
