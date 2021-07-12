#include "definicoes_sistema.h"
#include "ihm.h"

/***********************************************************************
 Estaticos
 ***********************************************************************/
int codigoEvento = NENHUM_EVENTO;
int eventoInterno = NENHUM_EVENTO;
int estado = ESPERA;
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
        println("ligar");
        break;
    case A02:
        // configurar();
        println("configurar");
        break;
    case A03:
        //reinicializar();
        println("reinicializar");
        break;
    case A04:
        // desligar();
        println("desligar");
        break;
    case A05:
        tmr_iniciar(true);
        break;
    case A06:
        sne_acionar(true);
        com_notificar("Invasao");
        tmr_iniciar(false);
        break;
    case A07:
        com_notificar("Alarme desacionado");
        tmr_iniciar(false);
        sne_acionar(false);
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
 Obtem um evento, que pode ser da IHM ou do alarme
 Parametros de entrada: nenhum
 Retorno: codigo do evento
*************************************************************************/
char* teclas;

int decodificarLigar()
{
    if (teclas[2] == 'a')
    {
        if (sha_validar(teclas))
        {
            return true;
        }
    }
    return false;
}//decodificarAcionar

int decodificarDesligar()
{
    if (teclas[2] == 'd')
    {
        if (sha_validar(teclas))
        {
            return true;
        }
    }
    return false;
}//decodificarDesacionar

int decodificarConfigurar()
{
    if (teclas[0] == 'l')
    {
        return true;
    }
    return false;
}//decodificarDisparar

int decodificarReinicializar()
{
    if (teclas[0] == 'l')
    {
        return true;
    }
    return false;
}

int obterEvento()
{
  int retval = NENHUM_EVENTO;

  teclas = ihm_obterTeclas();
  if (decodificarAcionar())
    return ACIONAR;
  if (decodificarDesacionar())
    return DESACIONAR;
  if (decodificarTimeout())
    return TIMEOUT;
  if (decodificarDisparar())
    return DISPARAR;

  return retval;

} // obterEvento




byte TP = 0b10101010; //every 2nd port receives the opposite signal
void setup()
{
 DDRC = 0b11111111; //Define all analog ports as outputs
  // Initialize timer 1
  noInterrupts();           // Disable interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 200;              // Set Compare Match Register (16MHz / 200 = 80kHz square -> 40kHz full wave)
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS10);    
  TIMSK1 |= (1 << OCIE1A);  // Switch on Compare Timer Interrupt  
  interrupts();             // Activate interrupts
}
ISR(TIMER1_COMPA_vect)          
{
  PORTC = TP; // Send the value TP to the outputs
  TP = ~TP;   // Invert TP for the next run
}
void loop(){
  // there is nothing left to do here:-(
}
