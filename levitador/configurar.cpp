#include <Arduino.h>

#include "definicoes_sistema.h"
#include "configurar.h"

void configurar_nos(int n){
  float lambda;
  float freq;

  lambda = 2*0.015/n;
  freq = 340/lambda;
  OCR1A = (int) 16000000/(2*freq);
}
