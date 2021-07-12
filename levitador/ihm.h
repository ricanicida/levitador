#ifndef IHM_H_INCLUDED
#define IHM_H_INCLUDED

#define NENHUMA_TECLA -1

/************************
 ihm_exibirMsg
 Exibe mensagem no display
 entradas
   texto : texto a ser validado como senha
 saidas
   nenhuma
*************************/
extern void ihm_exibirMsg(char* texto);

/************************
 ihm_obterTecla
 Obtem tecla do teclado
 entradas
   nenhuma
 saidas
   tecla lida do teclado ou NENHUMA_TECLA
*************************/
extern char* ihm_obterTeclas();

#endif // IHM_H_INCLUDED
