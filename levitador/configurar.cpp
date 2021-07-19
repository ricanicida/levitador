#include <Arduino.h>

#include "definicoes_sistema.h"
#include "configurar.h"

void configurar_nos(void){
  String str_n;
  int n;
  float lambda;
  float freq;
  int condicao = false;

  Serial.println("Digite o numero de nos: ");
  while (condicao == false){
    str_n = Serial.readStringUntil('\n');
    n = (str_n[0] - '0');
    if (n != -48){
      condicao = true;
    }
  }

  lambda = 2*0.01/n;
  freq = 340/lambda;
  OCR1A = (int) 16000000/(2*freq);
  
  Serial.print("Sistema configurado com ");
  Serial.print(n);
  Serial.println(" nós");
  Serial.print("Frequência nos transdutores: ");
  Serial.print(freq);
  Serial.println(" Hz");
}
