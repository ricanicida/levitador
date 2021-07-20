#include <Arduino.h>

#include "definicoes_sistema.h"
#include "desligar.h"

void desligar_transdutores(void){
  DDRC = 0b00000000; // define todas os pinos analogicos como input
  Serial.println("Transdutores desligados");
}
