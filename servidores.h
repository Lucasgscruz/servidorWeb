#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Variaveis para estabelecer a comunicacao 
struct sockaddr_in endereco_servidor, endereco_cliente;
int socket_con = 0, num_porta, flag = 0, cliente;
socklen_t cliente_len;
char mensagem[1024];
pid_t pid;

int menu();
void resposta(int);
void iterativo(int);
void forked(int);


