#include <Arduino.h>

#include "definicoes_sistema.h"
#include "desligar.h"

void desligar_transdutores(void){
  DDRC = 0b11111111; // define todas os pinos analogicos como output
  Serial.println("Sistema desligado");
}
