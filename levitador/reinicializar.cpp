#include <Arduino.h>

#include "definicoes_sistema.h"
#include "reinicializar.h"

void reinicializar_sistema(void){

  noInterrupts();           // desabilita interrupções
  OCR1A = 200;              // carrega registrador de comparação:
                            //(16MHz / 200 = 80kHz square -> 40kHz full wave)
  interrupts();             // habilita interrupções

  Serial.println("Sistema reinicializado");
  
}
