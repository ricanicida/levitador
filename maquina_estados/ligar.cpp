#include <Arduino.h>

#include "definicoes_sistema.h"
#include "ligar.h"

void ligar_init(void){      // configura e liga os transdutores a uma frequência de 40kHz
  
    Serial.println("Sistema ligado");
  
//  DDRC = 0b11111111; // define todas os pinos analogicos como output
//  // Inicializa timer 1
//  noInterrupts();           // desabilita interrupções
//  TCCR1A = 0;               // configura timer para operação normal
//  TCCR1B = 0;               // limpa registrador
//  TCNT1  = 0;               // zera temporizado
//  OCR1A = 200;              // carrega registrador de comparação:
//                            //(16MHz / 200 = 80kHz square -> 40kHz full wave)
//  TCCR1B |= (1 << WGM12);   // CTC mode: possibilita a alternância dos pinos mesmo sem interrupções
//  TCCR1B |= (1 << CS10);    // inicia o timer Fcpu/64
//  TIMSK1 |= (1 << OCIE1A);  // habilita interrupção por igualdade de comparação
//  interrupts();             // habilita interrupções
//  
//  ISR(TIMER1_COMPA_vect)    // interrupção por igualdade de comparação no TIMER1        
//  {
//    PORTC = TP; // envia o valor de TP para as saídas
//    TP = ~TP;   // inverte o TP para a próxima vez que rodar
//  }
}
