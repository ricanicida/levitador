#include "definicoes_sistema.h"

/***********************************************************************
 Estaticos
 ***********************************************************************/
int codigoEvento = NENHUM_EVENTO;
int eventoInterno = NENHUM_EVENTO;
int estado = DESLIGADO;
int codigoAcao;
int acao_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];



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
        // ligar();
        Serial.println("ligar");
        break;
    case A02:
        // configurar();
        Serial.println("configurar");
        break;
    case A03:
        //reinicializar();
        Serial.println("reinicializar");
        break;
    case A04:
        // desligar();
        Serial.println("desligar");
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




// byte TP = 0b10101010; //sinal oposto a cada pino
void setup()
{
  Serial.begin(9600);
  iniciaSistema();
  Serial.println("Sistema iniciado");
  
//  DDRC = 0b11111111; // define todas os pinos analogicos como output
//  // Inicializa timer 1
//  noInterrupts();           // desabilita interrupçoes
//  TCCR1A = 0;               // inicia Timer/Counter1 de 8 bits de controle do registrador A
//  TCCR1B = 0;               // inicia Timer/Counter1 de 8 bits de controle do registrador B
//  TCNT1  = 0;               // inicia Timer/Counter de 16 bits
//  OCR1A = 200;              // configura a frequencia a partir da frequencia interna do arduino
//                            //(16MHz / 200 = 80kHz square -> 40kHz full wave)
//  TCCR1B |= (1 << WGM12);   // CTC mode: possibilita a alternancia dos pinos mesmo sem interrupcoes
//  TCCR1B |= (1 << CS10);    // inicia o timer Fcpu/64
//  TIMSK1 |= (1 << OCIE1A);  // TIMSK1: mascara de registrador de timer interrupt 
//  interrupts();             // habilita interrupçoes
}
//ISR(TIMER1_COMPA_vect)          
//{
//  PORTC = TP; // envia o valor de TP para as saidas
//  TP = ~TP;   // inverte o TP para a proxima vez que rodar
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
