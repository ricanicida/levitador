#include <Arduino.h>

#include "definicoes_sistema.h"
#include "desligar.h"

void desligar_transdutores(void){
  
  TP = 0b00000000; //sinal oposto a cada pino
  
  ISR(TIMER1_COMPA_vect)    // interrupção por igualdade de comparação no TIMER1        
  {
    PORTC = TP; // envia o valor de TP para as saídas
  }
}
