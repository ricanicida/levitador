#include <Arduino.h>

#include "definicoes_sistema.h"
#include "configurar.h"

float calcula_freq(void){
  String str_n;
  int n;
  float lambda;
  float freq;
  int condicao = false;
  

  Serial.println("Digite o numero de nos: ");
  while (condicao == false){                    // loop para aguardar recebimento do número de nós
    str_n = Serial.readStringUntil('\n');
    n = (str_n[0] - '0');
    if (n != -48){
      condicao = true;
    }
  }

  lambda = 2*0.01/n;                            // calcula o lambda
  freq = 340/lambda;                            // calcula o frequencia desejada
  
  Serial.print("Sistema configurado com ");
  Serial.print(n);
  Serial.println(" nós");
  Serial.print("Frequência nos transdutores: ");
  Serial.print(freq);
  Serial.println(" Hz");
  
  return freq;
}

void configurar_nos(float freq){
    
  DDRC = 0b11111111; // define todas os pinos analogicos como output
  // Inicializa timer 1
  noInterrupts();           // desabilita interrupções
  TCCR1A = 0;               // configura timer para operação normal
  TCCR1B = 0;               // limpa registrador
  TCNT1  = 0;               // zera temporizado
  OCR1A = 16000000/(2*freq); // carrega registrador de comparação:
                            //(16MHz / 200 = 80kHz square -> 40kHz full wave)
  TCCR1B |= (1 << WGM12);   // CTC mode: possibilita a alternância dos pinos mesmo sem interrupções
  TCCR1B |= (1 << CS10);    // inicia o timer Fcpu/64
  TIMSK1 |= (1 << OCIE1A);  // habilita interrupção por igualdade de comparação
  interrupts();             // habilita interrupções
}
