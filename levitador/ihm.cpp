#include <Arduino.h>

#include "definicoes_sistema.h"
#include "ihm.h"

/************************
 ihm_exibirMsg
 Exibe mensagem no display
 entradas
   texto : texto a ser validado como senha
 saidas
   nenhuma
*************************/
void ihm_exibirMsg(char* texto)
{
    Serial.print("Mensagem para display: ");
    Serial.println(texto);
}

/************************
 ihm_obterTecla
 Obtem tecla do teclado
 entradas
   nenhuma
 saidas
   teclas lidas do teclado
*************************/
char buf[10];
char* ihm_obterTeclas()
{
  // Serial.print("obter teclas:");
  int read_count = 0;
  
  // check for input
  if (Serial.available() > 0) {
    // read the incoming bytes:
    read_count = Serial.readBytesUntil('\n',buf, sizeof(buf)/sizeof(buf[0]) - 1);
  }
  
  buf[read_count] = '\0';
  if(read_count > 0) {
    Serial.println(buf);
  }
  
  return buf;
}
