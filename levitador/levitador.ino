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
int estado = INICIAL;
int codigoAcao;
int acao_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];

byte TP = 0b10101010; //sinal dos pinos do PORTC
int numero_nos;


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
    float freq;

    retval = NENHUM_EVENTO;
    if (codigoAcao == NENHUMA_ACAO)
        return retval;

    switch(codigoAcao)
    {
    case A01:
        // ligar();
        ligar_init();
        break;
    case A02:
        // configurar();
        freq = calcula_freq();
//        desligar_transdutores();
        configurar_nos(freq);
        break;
    case A03:
        //reinicializar();
//        desligar_transdutores();
        reinicializar_sistema();
        break;
    case A04:
        // desligar();
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
  if (estado == INICIAL){                       // setup inicial que roda uma vez
    Serial.begin(9600);
    iniciaSistema();
    Serial.println("Sistema iniciado");
    estado = DESLIGADO;
  } else {                                      // executar ação deve ser chamada no void setup()
    if (codigoEvento != NENHUM_EVENTO)
    {
      eventoInterno = executarAcao(codigoAcao);
    }
  }
}

ISR(TIMER1_COMPA_vect)    // interrupção por igualdade de comparação no TIMER1        
{
  PORTC = TP; // envia o valor de TP para as saídas
  TP = ~TP;   // inverte o TP para a próxima vez que rodar
}

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
      setup();
      Serial.print("Estado: ");
      Serial.print(estado);
      Serial.print(" Evento: ");
      Serial.print(codigoEvento);
      Serial.print(" Acao: ");
      Serial.println(codigoAcao);
  }
}
