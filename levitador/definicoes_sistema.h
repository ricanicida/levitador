#ifndef DEFINICOES_SISTEMA_H_INCLUDED
#define DEFINICOES_SISTEMA_H_INCLUDED

#define true  1
#define false 0


#define NUM_ESTADOS 3
#define NUM_EVENTOS 4


// ESTADOS
#define INICIAL  -1
#define DESLIGADO  0
#define LIGADO     1
#define LEVITACAO  2

// EVENTOS
#define NENHUM_EVENTO -1
#define LIGAR          0
#define CONFIGURAR     1
#define REINICIALIZAR  2
#define DESLIGAR       3

// ACOES
#define NENHUMA_ACAO -1
#define A01  0
#define A02  1
#define A03  2
#define A04  3


#endif // DEFINICOES_SISTEMA_H_INCLUDED
