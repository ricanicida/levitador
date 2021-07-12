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
int evento = NENHUM_EVENTO;
String str_evento;
int obterEvento() {
  
  Serial.println("Digite o evento:");
  str_evento = Serial.readStringUntil('\n');
  evento = str_evento.toInt() - '0';
    
  return evento;
}

/************************************************************************
 obterAcao
 Obtem uma acao
 Parametros de entrada: nenhum
 Retorno: codigo da acao
*************************************************************************/
int obterAcao(int estado, int codigoEvento) {
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




// byte TP = 0b10101010; //every 2nd port receives the opposite signal
void setup()
{
  Serial.begin(9600);
  iniciaSistema();
  Serial.println("Sistema iniciado");
  
//  DDRC = 0b11111111; //Define all analog ports as outputs
//  // Initialize timer 1
//  noInterrupts();           // Disable interrupts
//  TCCR1A = 0;
//  TCCR1B = 0;
//  TCNT1  = 0;
//  OCR1A = 200;              // Set Compare Match Register (16MHz / 200 = 80kHz square -> 40kHz full wave)
//  TCCR1B |= (1 << WGM12);   // CTC mode
//  TCCR1B |= (1 << CS10);    
//  TIMSK1 |= (1 << OCIE1A);  // Switch on Compare Timer Interrupt  
//  interrupts();             // Activate interrupts
}
//ISR(TIMER1_COMPA_vect)          
//{
//  PORTC = TP; // Send the value TP to the outputs
//  TP = ~TP;   // Invert TP for the next run
//}

void loop(){
  if (eventoInterno == NENHUM_EVENTO) {
      codigoEvento = obterEvento();
  } else {
      codigoEvento = eventoInterno;
  }
  if (codigoEvento != NENHUM_EVENTO)
  {
      codigoAcao = obterAcao(estado, codigoEvento);
      estado = obterProximoEstado(estado, codigoEvento);
      eventoInterno = executarAcao(codigoAcao);
//      Serial.print("Estado: ");
//      Serial.print(estado);
//      Serial.print(" Evento: ");
//      Serial.print(codigoEvento);
//      Serial.print(" Acao: ");
//      Serial.println(codigoAcao);
  }
}
