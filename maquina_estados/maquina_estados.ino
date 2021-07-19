#include "definicoes_sistema.h"
#include "ligar.h"
#include "configurar.h"
#include "desligar.h"
#include "reinicializar.h"

/***********************************************************************
 Globais
 ***********************************************************************/
int codigoEvento = NENHUM_EVENTO;
int eventoInterno = NENHUM_EVENTO;
int estado = DESLIGADO;
int codigoAcao;
int acao_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];

//byte TP = 0b10101010; //sinal oposto a cada pino


/************************************************************************
 executarAcao
 Executa uma acao
 Parametros de entrada:
      (int) codigo da acao a ser executada        
 Retorno: (int) codigo do evento interno ou NENHUM_EVENTO
*************************************************************************/
int executarAcao(int codigoAcao)
{
    int retval;

    retval = NENHUM_EVENTO;
    if (codigoAcao == NENHUMA_ACAO)
        return retval;

    switch(codigoAcao)
    {
    case A01:
        ligar_init();
        break;
    case A02:
        configurar_nos();
        break;
    case A03:
        reinicializar_sistema();
        break;
    case A04:
        desligar_transdutores();
        break;
    } // switch

    return retval;
} // executarAcao


/************************************************************************
 iniciaMaquina de Estados
 Carrega a maquina de estados
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void iniciaMaquinaEstados()
{
  int i;
  int j;

  for (i=0; i < NUM_ESTADOS; i++) {
    for (j=0; j < NUM_EVENTOS; j++) {
       acao_matrizTransicaoEstados[i][j] = NENHUMA_ACAO;
       proximo_estado_matrizTransicaoEstados[i][j] = i;
    }
  }
  proximo_estado_matrizTransicaoEstados[DESLIGADO][LIGAR] = LIGADO;
  acao_matrizTransicaoEstados[DESLIGADO][LIGAR] = A01;

  proximo_estado_matrizTransicaoEstados[LIGADO][CONFIGURAR] = LEVITACAO;
  acao_matrizTransicaoEstados[LIGADO][CONFIGURAR] = A02;

  proximo_estado_matrizTransicaoEstados[LEVITACAO][REINICIALIZAR] = LIGADO;
  acao_matrizTransicaoEstados[LEVITACAO][REINICIALIZAR] = A03;

  proximo_estado_matrizTransicaoEstados[LIGADO][DESLIGAR] = DESLIGADO;
  acao_matrizTransicaoEstados[LIGADO][DESLIGAR] = A04;

  proximo_estado_matrizTransicaoEstados[LEVITACAO][DESLIGAR] = DESLIGADO;
  acao_matrizTransicaoEstados[LEVITACAO][DESLIGAR] = A04;

} // initStateMachine

/************************************************************************
 iniciaSistema
 Inicia o sistema ...
 Parametros de entrada: nenhum
 Retorno: nenhum
*************************************************************************/
void iniciaSistema()
{
   iniciaMaquinaEstados();
} // initSystem


/************************************************************************
 obterEvento
 Obtem um evento
 Parametros de entrada: nenhum
 Retorno: codigo do evento
*************************************************************************/
void types(String a) { Serial.println("it's a String"); }
void types(int a) { Serial.println("it's an int"); }
void types(char *a) { Serial.println("it's a char*"); }
void types(float a) { Serial.println("it's a float"); }
void types(bool a) { Serial.println("it's a bool"); }

int evento = NENHUM_EVENTO;
String str_evento;
int obterEvento() {
  bool condicao = false;
  
  Serial.print("Digite o evento:");
  while (condicao == false){
    str_evento = Serial.readStringUntil('\n');
    evento = (str_evento[0] - '0');
    if (evento != -48){
      condicao = true;
    }
  }
  
  return evento;
}

/************************************************************************
 obterAcao
 Obtem uma acao
 Parametros de entrada: nenhum
 Retorno: codigo da acao
*************************************************************************/
int obterAcao(int estado, int codigoEvento) {
  Serial.println(acao_matrizTransicaoEstados[estado][codigoEvento]);
  return acao_matrizTransicaoEstados[estado][codigoEvento];
}

/************************************************************************
 obterProximoEstado
 Obtem o proximo estado da Matriz de transicao de estados
 Parametros de entrada: estado (int)
                        evento (int)
 Retorno: codigo do estado
*************************************************************************/
int obterProximoEstado(int estado, int codigoEvento) {
  return proximo_estado_matrizTransicaoEstados[estado][codigoEvento];
} // obterProximoEstado





void setup()
{
  Serial.begin(9600);
  iniciaSistema();
  
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
  
  Serial.println("Sistema iniciado");
}

//ISR(TIMER1_COMPA_vect)    // interrupção por igualdade de comparação no TIMER1        
//{
//  PORTC = TP; // envia o valor de TP para as saídas
//  TP = ~TP;   // inverte o TP para a próxima vez que rodar
//}

void loop(){
  if (eventoInterno == NENHUM_EVENTO) {
      codigoEvento = obterEvento();
  } else {
      codigoEvento = eventoInterno;
  }
  if (codigoEvento < 0 || codigoEvento > 3){
      codigoEvento = NENHUM_EVENTO;
  }
  if (codigoEvento != NENHUM_EVENTO)
  {
      codigoAcao = obterAcao(estado, codigoEvento);
      estado = obterProximoEstado(estado, codigoEvento);
      eventoInterno = executarAcao(codigoAcao);
      Serial.print("Estado: ");
      Serial.print(estado);
      Serial.print(" Evento: ");
      Serial.print(codigoEvento);
      Serial.print(" Acao: ");
      Serial.println(codigoAcao);
  }
}
