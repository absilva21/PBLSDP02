# PBLSDP02
Problema 2 da disciplina TEC499

Estação de medição de sensores 

Feito com Raspberry e NodeMcu

Por enquanto somente a parte do NodeMcu está funcionando

Para testar o NodeMcu basta usar a o arquivo PBLSD.ino na IDE arduino descarregar na placa e inserir os comandos no monitor serial
 
 |Código | Descrição do comando                        |
 |       |                                             |
 |0x03   |Solicita a situação atual do NodeMCU         |
 |0x04   |Solicita o valor da entrada analógica        |
 |0x05   |Solicita o valor de uma das entradas digitais|
 |0x06   |Acendimento do led da NodeMCU                |

 
 Os comando como será adicionado endereço de sensores é necessário enviar dois bytes o primero o comando, o segundo
 pode ser quaquer um.
